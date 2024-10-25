# HideFunctions

- **Function description:** Hide certain functions in the subclass function override list.
- **Engine module:** Blueprint
- **Metadata type:** strings = (abc, "d|e", "x|y|z")
- **Mechanism:** Add [HideFunctions](../../../../Meta/Blueprint/HideFunctions.md) in the Meta class
- **Associated items:** [ShowFunctions](../ShowFunctions.md)
- **Commonly used:** ★★

Hide certain functions in the subclass function override list.

- In the Blueprint, you can still view the functions marked as BlueprintCallable by right-clicking on the class; they remain callable. This marking is only applied to the function override list of the class.
- HideFunctions only accepts function names. To hide functions within a directory, you'll need to use HideCategories for additional specification.

It is utilized only at a single location within the source code. A prime example is the SetFieldOfView and SetAspectRatio functions defined in UCameraComponent. These are irrelevant to UCineCameraComponent and would be better hidden.

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

## Sample code:

```cpp
UCLASS(Blueprintable, HideFunctions = (MyFunc1, MyEvent2),hideCategories= EventCategory2)
class INSIDER_API AMyClass_HideFunctions :public AActor
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
		void MyFunc1() {}

	UFUNCTION(BlueprintCallable)
		void MyFunc2() {}

	UFUNCTION(BlueprintCallable, Category = "FuncCategory1")
		void MyFuncInCategory1() {}

	UFUNCTION(BlueprintCallable, Category = "FuncCategory2")
		void MyFuncInCategory2() {}

public:
UFUNCTION(BlueprintImplementableEvent)
		void MyEvent1();

	UFUNCTION(BlueprintImplementableEvent)
		void MyEvent2();

	UFUNCTION(BlueprintImplementableEvent, Category = "EventCategory1")
		void MyEventInCategory1();

	UFUNCTION(BlueprintImplementableEvent, Category = "EventCategory2")
		void MyEventInCategory2();
};

UCLASS(Blueprintable, ShowFunctions = (MyEvent2),showCategories= EventCategory2)
class INSIDER_API AMyClass_ShowFunctions :public AMyClass_HideFunctions
{
	GENERATED_BODY()
public:

};
```

## Example effect:

It is observed that Callable functions are still callable.

![Untitled](Untitled.png)

In subclasses using HideFunctions, two functions will be missing from the function overload list

![Untitled](Untitled%201.png)

Event2 and EventCategory2 can be re-enabled in the subclass of ShowFunction

![Untitled](Untitled%202.png)

## Principle:

As demonstrated by the principle, HideFunctions should only include function names. To conceal functions within a directory, one must define HideCategories as an additional step.

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