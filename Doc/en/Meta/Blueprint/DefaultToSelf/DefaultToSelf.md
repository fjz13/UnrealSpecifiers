# DefaultToSelf

- **Function Description:** Used on functions to specify a default value of Self for a parameter
- **Usage Location:** UFUNCTION
- **Engine Module:** Blueprint
- **Metadata Type:** bool
- **Commonly Used:** ★★★★★

Enables more convenient calls within blueprints, depending on the function's requirements.

## Test Code:

```cpp
UCLASS()
class INSIDER_API UMyFunctionLibrary_SelfPinTest :public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static FString PrintProperty_Default(UObject* myOwner,FName propertyName);

	UFUNCTION(BlueprintCallable,meta=(DefaultToSelf="myOwner"))
	static FString PrintProperty_HasDefaultToSelf(UObject* myOwner,FName propertyName);

	UFUNCTION(BlueprintCallable,meta=(DefaultToSelf="myOwner",hidePin="myOwner"))
	static FString PrintProperty_HasDefaultToSelf_ButHide(UObject* myOwner,FName propertyName);
};
```

In blueprint nodes, it can be observed that the blueprint compiler automatically assigns the function parameter designated by DefaultToSelf to Self. This is fundamentally the same as manually linking to Self. Additionally, using HidePin can hide this function parameter, making the blueprint object (Self) where the node is located the default first function parameter, thus appearing more streamlined.

![Untitled](Untitled.png)

Also applicable if it is a BlueprintPure:

![Untitled](Untitled%201.png)

## Principle:

When the function call in the blueprint is compiled, SelfPin (named Target) will be automatically created. If the function is a static function or the mark of HideSelfPin, SelfPin will be hidden. The value of its SelfPin is the value of the current blueprint runtime object. Therefore, the effect of DefaultToSelf is that the blueprint system will automatically assign the value of this parameter to the blueprint runtime object where it is called, which is equivalent to the effect of the C++ this pointer

```cpp
bool UK2Node_CallFunction::CreatePinsForFunctionCall(const UFunction* Function)
{
	UEdGraphPin* SelfPin = CreateSelfPin(Function);
	// Renamed self pin to target
	SelfPin->PinFriendlyName = LOCTEXT("Target", "Target");
}

UEdGraphPin* FBlueprintNodeStatics::CreateSelfPin(UK2Node* Node, const UFunction* Function)
{
	// Chase up the function's Super chain, the function can be called on any object that is at least that specific
	const UFunction* FirstDeclaredFunction = Function;
	while (FirstDeclaredFunction->GetSuperFunction() != nullptr)
	{
		FirstDeclaredFunction = FirstDeclaredFunction->GetSuperFunction();
	}

	// Create the self pin
	UClass* FunctionClass = CastChecked<UClass>(FirstDeclaredFunction->GetOuter());
	// we don't want blueprint-function target pins to be formed from the
	// skeleton class (otherwise, they could be incompatible with other pins
	// that represent the same type)... this here could lead to a compiler
	// warning (the GeneratedClass could not have the function yet), but in
	// that, the user would be reminded to compile the other blueprint
	if (FunctionClass->ClassGeneratedBy)
	{
		FunctionClass = FunctionClass->GetAuthoritativeClass();
	}

	UEdGraphPin* SelfPin = NULL;
	if (FunctionClass == Node->GetBlueprint()->GeneratedClass)
	{
		// This means the function is defined within the blueprint, so the pin should be a true "self" pin
		SelfPin = Node->CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Object, UEdGraphSchema_K2::PSC_Self, nullptr, UEdGraphSchema_K2::PN_Self);
	}
	else if (FunctionClass->IsChildOf(UInterface::StaticClass()))
	{
		SelfPin = Node->CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Interface, FunctionClass, UEdGraphSchema_K2::PN_Self);
	}
	else
	{
		// This means that the function is declared in an external class, and should reference that class
		SelfPin = Node->CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Object, FunctionClass, UEdGraphSchema_K2::PN_Self);
	}
	check(SelfPin != nullptr);

	return SelfPin;
}
```