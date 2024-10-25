# ExposeFunctionCategories

- **Function description:** Specifies that certain functions within directories of the class to which this Object attribute belongs can be directly exposed on this class.
- **Use location:** UPROPERTY
- **Engine module:** Object Property
- **Metadata type:** strings = "a, b, c"
- **Restriction type:** UObject*
- **Commonly used:** ★★★

Functions within certain directories of the class to which the Object attribute belongs can be directly exposed on this class.

Initially, it may be difficult to grasp the meaning and function, but this is actually a feature for convenience. For instance, if class A defines some functions and class B has an instance of A, if you want to call A's functions on the B object, you would normally have to manually drag out B.ObjA and then drag out the functions within it. We aim to allow, within the current context of B, certain functions from A to be exposed more conveniently for calling within B.

Effectively, the engine automates the step of dragging out B.ObjA for you. If you wish to call additional functions from A, you can still manually drag and right-click on B.ObjA to expose more functions.

This kind of application is also common in the source code. A convenient example is the following source code snippet, which allows functions defined in the directories specified by ExposeFunctionCategories in USkeletalMeshComponent to be directly exposed on ASkeletalMeshActor.

```cpp
UCLASS(ClassGroup=ISkeletalMeshes, Blueprintable, ComponentWrapperClass, ConversionRoot, meta=(ChildCanTick), MinimalAPI)
class ASkeletalMeshActor : public AActor
{
private:
	UPROPERTY(Category = SkeletalMeshActor, VisibleAnywhere, BlueprintReadOnly, meta = (ExposeFunctionCategories = "Mesh,Components|SkeletalMesh,Animation,Physics", AllowPrivateAccess = "true"))
	TObjectPtr<class USkeletalMeshComponent> SkeletalMeshComponent;
}
```

## Test Code:

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

## Test Results:

You can see that on an Object of type UMyProperty_ExposeFunctionCategories_Test, typing "MyExposeFunc" directly will pop up the functions in the "FirstFunc" and "ThirdFunc" directories, but "MyExposeFunc2" will not appear directly because it has not been exposed.

If you right-click and drag on an internal object like MyObject_Expose, you will see all the functions defined internally. Note that although there are two entries for MyExposeFunc1, the function called is actually the same, with no practical difference.

![Untitled](Untitled.png)

## Principle:

During the construction of the right-click menu in the blueprint, it is determined whether an action should be filtered out. The IsUnexposedMemberAction function is used to decide if a function should be filtered. The general logic involves retrieving the attributes corresponding to the function, such as in the UMyProperty_ExposeFunctionCategories_Test object, where recursively, three functions will be considered for testing. These three functions (MyExposeFunc 1, 2, 3) each have their own Category but correspond to the same MyObject_Expose property, so their AllExposedCategories value is the array we defined, "FirstFunc, ThirdFunc". In the end, only two functions pass the test, and thus only the functions 1 and 3 are displayed.

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