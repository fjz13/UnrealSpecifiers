# ExposeFunctionCategories

- **功能描述：** 指定该Object属性所属于的类里的某些目录下的函数可以直接在本类上暴露出来。
- **使用位置：** UPROPERTY
- **引擎模块：** Object Property
- **元数据类型：** strings="a，b，c"
- **限制类型：** UObject*
- **常用程度：** ★★★

指定该Object属性所属于的类里的某些目录下的函数可以直接在本类上暴露出来。

一开始直接还挺难理解的其含义和作用的，但这其实是一个便利性的功能而已。比如有类A里面定义一些函数，然后类B里有个A的对象。这个时候如果想在B对象身上去调用A的函数，就得手动先拖拉出B.ObjA然后再拖拉出其内部的函数。我们希望把当前B的应用上下文场景下，可以把A里的某些函数直接比较方便的暴露到B里来调用。

其实就是引擎帮我们自动的拖拉出B.ObjA这一步操作而已。你如果想要调用A里的更多的函数，也可以自己手动在B.ObjA身上拖拉右键出更多的函数。

源码里这种应用也比较多，比较方便的例子是以下源码例子，这样当前在ASkeletalMeshActor 身上就可以直接拖拉出USkeletalMeshComponent里ExposeFunctionCategories 所定义的目录的函数。

```cpp
UCLASS(ClassGroup=ISkeletalMeshes, Blueprintable, ComponentWrapperClass, ConversionRoot, meta=(ChildCanTick), MinimalAPI)
class ASkeletalMeshActor : public AActor
{
private:
	UPROPERTY(Category = SkeletalMeshActor, VisibleAnywhere, BlueprintReadOnly, meta = (ExposeFunctionCategories = "Mesh,Components|SkeletalMesh,Animation,Physics", AllowPrivateAccess = "true"))
	TObjectPtr<class USkeletalMeshComponent> SkeletalMeshComponent;
}
```

## 测试代码：

```cpp
UCLASS(BlueprintType)
class INSIDER_API UMyProperty_ExposeFunctionCategories :public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "FirstFunc")
	void MyExposeFunc1() {}
	UFUNCTION(BlueprintCallable, Category = "SecondFunc")
	void MyExposeFunc2() {}
	UFUNCTION(BlueprintCallable, Category = "ThirdFunc")
	void MyExposeFunc3() {}
};

UCLASS(BlueprintType)
class INSIDER_API UMyProperty_ExposeFunctionCategories_Test :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, meta = (ExposeFunctionCategories = "FirstFunc,ThirdFunc"))
	UMyProperty_ExposeFunctionCategories* MyObject_Expose;
};

```

## 测试效果：

可以见到在UMyProperty_ExposeFunctionCategories_Test 类型的Object身上，我直接输入MyExposeFunc就可以弹出“FirstFunc，ThirdFunc”这两个目录里的这两个函数，而不会直接弹出MyExposeFunc2，因为其没有直接被暴露出来。

而如果在MyObject_Expose这种内部对象上直接拖拉右键，则可以见到所有内部定义的函数。注意这里虽然有两个条目的MyExposeFunc1，但其实调用出来的是同一个函数，实际并没有影响。

![Untitled](Untitled.png)

## 原理：

在蓝图右键菜单的构建过程中，会判断某个操作是否要过滤掉。这里的IsUnexposedMemberAction就是判断这个函数是否应该被过滤掉。大致的逻辑是取得其函数对应的属性，比如在UMyProperty_ExposeFunctionCategories_Test 这个Object身上，递归到子对象，其实有3个函数会进来参加测试。这3个函数（MyExposeFunc 1 2 3）各自有自己的Category，但都对应MyObject_Expose这个Property，因此其AllExposedCategories的值是我们定义的“FirstFunc,ThirdFunc”数组，最终只有两个函数通过测试，因此最后显示1，3两个函数。

```cpp
static bool BlueprintActionMenuUtilsImpl::IsUnexposedMemberAction(FBlueprintActionFilter const& Filter, FBlueprintActionInfo& BlueprintAction)
{
	bool bIsFilteredOut = false;

	if (UFunction const* Function = BlueprintAction.GetAssociatedFunction())
	{
		TArray<FString> AllExposedCategories;
		for (FBindingObject Binding : BlueprintAction.GetBindings())
		{
			if (FProperty* Property = Binding.Get<FProperty>())
			{
				const FString& ExposedCategoryMetadata = Property->GetMetaData(FBlueprintMetadata::MD_ExposeFunctionCategories);
				if (ExposedCategoryMetadata.IsEmpty())
				{
					continue;
				}

				TArray<FString> PropertyExposedCategories;
				ExposedCategoryMetadata.ParseIntoArray(PropertyExposedCategories, TEXT(","), true);
				AllExposedCategories.Append(PropertyExposedCategories);
			}
		}

		const FString& FunctionCategory = Function->GetMetaData(FBlueprintMetadata::MD_FunctionCategory);
		bIsFilteredOut = !AllExposedCategories.Contains(FunctionCategory);
	}
	return bIsFilteredOut;
}
```
