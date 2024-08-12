# HideFunctions

Description: 在属性查看器中不显示指定类别中的所有函数。
Feature: DetailsPanel
Type: strings=(abc，"d|e"，"x|y|z")
Example: HideFunctions=(FuncName1, FuncName1, ...)
MetaOperation: +=
Meta: HideFunctions (../../Meta/Meta/HideFunctions.md)
Status: Done
Sub-item: ShowFunctions (ShowFunctions.md)

在蓝图中鼠标右键依然可以查看该BlueprintCallable的函数。

源码中只有一个地方用到，一个很好的示例是UCameraComponent中定义的SetFieldOfView和SetAspectRatio，对UCineCameraComponent 来说是无意义的，因此隐藏掉会更好。

```cpp
class ENGINE_API UCameraComponent : public USceneComponent
{
UFUNCTION(BlueprintCallable, Category = Camera)
	virtual void SetFieldOfView(float InFieldOfView) { FieldOfView = InFieldOfView; }
UFUNCTION(BlueprintCallable, Category = Camera)
	void SetAspectRatio(float InAspectRatio) { AspectRatio = InAspectRatio; }
}

UCLASS(HideCategories = (CameraSettings), HideFunctions = (SetFieldOfView, SetAspectRatio), Blueprintable, ClassGroup = Camera, meta = (BlueprintSpawnableComponent), Config = Engine)
class CINEMATICCAMERA_API UCineCameraComponent : public UCameraComponent
```

原理显示，HideFunctions其实只能填函数名字，想要隐藏一个目录下的函数，是需要HideCategories再额外定义的。

```cpp
bool IsFunctionHiddenFromClass( const UFunction* InFunction,const UClass* Class )
	{
		bool bResult = false;
		if( InFunction )
		{
			bResult = Class->IsFunctionHidden( *InFunction->GetName() );

			static const FName FunctionCategory(TEXT("Category")); // FBlueprintMetadata::MD_FunctionCategory
			if( !bResult && InFunction->HasMetaData( FunctionCategory ) )
			{
				FString const& FuncCategory = InFunction->GetMetaData(FunctionCategory);
				bResult = FEditorCategoryUtils::IsCategoryHiddenFromClass(Class, FuncCategory);
			}
		}
		return bResult;
	}
```

发现Callable的函数是依然可以调用的，隐藏失效

![Untitled](HideFunctions/Untitled.png)

在Sequence里也依然可以绑定：隐藏失效

![Untitled](HideFunctions/Untitled%201.png)

在HideFunction子类里，函数重载会发现少两个

![Untitled](HideFunctions/Untitled%202.png)

在ShowFunction的子类里可以重新打开Event2和EventCategory2

![Untitled](HideFunctions/Untitled%203.png)