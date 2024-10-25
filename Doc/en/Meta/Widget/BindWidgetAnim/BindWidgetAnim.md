# BindWidgetAnim

- **Function description:** Specifies that the UWidgetAnimation attribute in the C++ class must be bound to a specific animation within UMG
- **Use location:** UPROPERTY
- **Engine module:** Widget Property
- **Metadata type:** bool
- **Restriction type:** UWidgetAnimation attribute within a UWidget subclass
- **Related items:** [BindWidgetAnimOptional](../BindWidgetAnimOptional/BindWidgetAnimOptional.md)
- **Commonly used:** ★★★★★

Specifies that the UWidgetAnimation attribute in the C++ class must be bound to a specific animation within UMG.

Functions similarly to BindWidget, both used to bind C++ properties to controls or animations in BP, but with distinct differences:

- UWidgetAnimation is different from Widget. Widget's properties and controls can be automatically bound as long as they have the same name. However, UWidgetAnimation does not allow the same name without adding BindWidgetAnim, otherwise a name conflict error will be reported. This is because the Widget created in UMG does not create BP variables by default. The sub-control is just an object under WidgetTree, but the animation will create BP variables by default. Therefore, even if the animation is defined first in UMG, and then the property of the same name is defined in C++, it will not pass compilation.
- The UWidgetAnimation attribute must be Transient, or an error will occur. This is likely because UWidgetAnimation is naturally serialized as a sub-object in BP and does not need to be accessed during C++ serialization, hence the enforced Transient to prevent accidental serialization. Additionally, since UWidgetAnimation is solely for presentation, it is also automatically marked with CPF_RepSkip to skip network replication.

## Test Code:

```cpp
UCLASS(BlueprintType)
class INSIDER_API UMyProperty_BindWidget :public UUserWidget
{
	GENERATED_BODY()
	UMyProperty_BindWidget(const FObjectInitializer& ObjectInitializer);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetAnimation* MyAnimation_NotFound;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//class UWidgetAnimation* MyAnimation_SameName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* MyAnimation_Bind;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient, meta = (BindWidgetAnimOptional))
	class UWidgetAnimation* MyAnimation_BindOptional;
};
```

## Test Results:

The testing process is similar to that of BindWidget, involving the definition of different property types and animation objects in both C++ and UMG. It can be observed in the actual object values in VS that:

- MyAnimation_Bind and MyAnimation_BindOptional are both automatically bound to the correct animation objects.
- MyAnimation_SameName, without BindWidgetAnim, must be commented out to prevent a name conflict with the MyAnimation_SameName in UMG.
- Moreover, it should be noted that one cannot define an animation in UMG first, as one might with a Widget, and then define a property with the same name in C++. This is because WidgetAnimation inherently creates BP variables, which is a crucial distinction.

![Untitled](Untitled.png)

## Principle:

The logic is roughly similar to that of BindWidget, involving checks for whether a property has BindWidgetAnim set. Subsequent actions are taken during compilation and renaming accordingly.

The logic for setting PropertyFlags for animation variables can be found in CreateClassVariablesFromBlueprint, where four properties are added, explicitly indicating that the property should not be serialized.

The logic for automatically binding and assigning values to UWidgetAnimation* attributes is located in BindAnimationsStatic, and it is straightforward to understand.

```cpp
bool FWidgetBlueprintEditorUtils::IsBindWidgetAnimProperty(const FProperty* InProperty, bool& bIsOptional)
{
	if (InProperty)
	{
		bool bIsBindWidgetAnim = InProperty->HasMetaData("BindWidgetAnim") || InProperty->HasMetaData("BindWidgetAnimOptional");
		bIsOptional = InProperty->HasMetaData("BindWidgetAnimOptional");

		return bIsBindWidgetAnim;
	}

	return false;
}

void FWidgetBlueprintCompilerContext::CreateClassVariablesFromBlueprint()
{
	for (UWidgetAnimation* Animation : WidgetBP->Animations)
	{
		FEdGraphPinType WidgetPinType(UEdGraphSchema_K2::PC_Object, NAME_None, Animation->GetClass(), EPinContainerType::None, true, FEdGraphTerminalType());
		FProperty* AnimationProperty = CreateVariable(Animation->GetFName(), WidgetPinType);

		if ( AnimationProperty != nullptr )
		{
			const FString DisplayName = Animation->GetDisplayName().ToString();
			AnimationProperty->SetMetaData(TEXT("DisplayName"), *DisplayName);

			AnimationProperty->SetMetaData(TEXT("Category"), TEXT("Animations"));

			AnimationProperty->SetPropertyFlags(CPF_Transient);
			AnimationProperty->SetPropertyFlags(CPF_BlueprintVisible);
			AnimationProperty->SetPropertyFlags(CPF_BlueprintReadOnly);
			AnimationProperty->SetPropertyFlags(CPF_RepSkip);

			WidgetAnimToMemberVariableMap.Add(Animation, AnimationProperty);
		}
	}
}

void FWidgetBlueprintCompilerContext::FinishCompilingClass(UClass* Class)
{
	if (!WidgetAnimProperty->HasAnyPropertyFlags(CPF_Transient))
	{
			const FText BindWidgetAnimTransientError = LOCTEXT("BindWidgetAnimTransient", "The property @@ uses BindWidgetAnim, but isn't Transient!");
			MessageLog.Error(*BindWidgetAnimTransientError.ToString(), WidgetAnimProperty);
	}
}

void UWidgetBlueprintGeneratedClass::BindAnimationsStatic(UUserWidget* Instance, const TArrayView<UWidgetAnimation*> InAnimations, const TMap<FName, FObjectPropertyBase*>& InPropertyMap)
{
	// Note: It's not safe to assume here that the UserWidget class type is a UWidgetBlueprintGeneratedClass!
	// - @see InitializeWidgetStatic()

	for (UWidgetAnimation* Animation : InAnimations)
	{
		if (Animation->GetMovieScene())
		{
			// Find property with the same name as the animation and assign the animation to it.
			if (FObjectPropertyBase*const* PropPtr = InPropertyMap.Find(Animation->GetMovieScene()->GetFName()))
			{
				check(*PropPtr);
				(*PropPtr)->SetObjectPropertyValue_InContainer(Instance, Animation);
			}
		}
	}
}
```