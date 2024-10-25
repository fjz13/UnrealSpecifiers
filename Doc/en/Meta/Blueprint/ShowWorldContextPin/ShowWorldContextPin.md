# ShowWorldContextPin

- **Function Description:** Placed on UCLASS, this attribute ensures that function calls within this class must display the WorldContext pin, irrespective of its default hidden state
- **Usage Location:** UCLASS
- **Metadata Type:** bool
- **Associated Item:** [WorldContext](../WorldContext/WorldContext.md)

Placed on UCLASS, this attribute specifies that function calls within this class must display the WorldContext pin, regardless of whether it is normally hidden by default. This is because this Object class cannot be used as a WorldContextObject, even if the GetWorld() method is implemented; it must be treated as if it cannot automatically obtain the WorldContext, thus requiring the user to manually specify a WorldContextObject.

Generally placed on UObject, but it has been found in the source code on AGameplayCueNotify_Actor and AEditorUtilityActor as well. AEditorUtilityActor does not operate at runtime and therefore lacks a World. AGameplayCueNotify_Actor might be used and recycled on a CDO, so it cannot be assumed that a WorldContext is always present.

## Test Code:

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyFunctionLibrary_WorldContextTest :public UBlueprintFunctionLibrary
{
public:
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	static FString MyFunc_NoWorldContextMeta(const UObject* WorldContextObject, FString name, FString value);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static FString MyFunc_HasWorldContextMeta(const UObject* WorldContextObject, FString name, FString value);
};

UCLASS(Blueprintable, BlueprintType, meta = (ShowWorldContextPin = "true"))
class INSIDER_API UMyObject_ShowWorldContextPin :public UObject
{
	GENERATED_BODY()
	UWorld* WorldPrivate = nullptr;
public:
	UFUNCTION(BlueprintCallable)
	void RegisterWithOuter()
	{
		if (UObject* outer = GetOuter())
		{
			WorldPrivate = outer->GetWorld();
		}
	}

	virtual UWorld* GetWorld() const override final { return WorldPrivate; }
};
```

## Blueprint Test Effect:

It can be observed that although the UMyObject_ShowWorldContextPin class implements the GetWorld() method, the WorldContextObject, which should normally be automatically assigned and remain hidden in MyFunc_HasWorldContextMeta, is explicitly displayed in this class. Additionally, note that the WorldContextObject is also output in the PrintString.

![Untitled](Untitled.png)

## Principle:

In the CallFunction blueprint node, if bShowWorldContextPin is set, the function parameters specified by WorldContextMetaValue or DefaultToSelfMetaValue will not be hidden.

```cpp
bool UK2Node_CallFunction::CreatePinsForFunctionCall(const UFunction* Function)
{
	const bool bShowWorldContextPin = ((PinsToHide.Num() > 0) && BP && BP->ParentClass && BP->ParentClass->HasMetaDataHierarchical(FBlueprintMetadata::MD_ShowWorldContextPin));
	//...
	if (PinsToHide.Contains(Pin->PinName))
	{
		const FString PinNameStr = Pin->PinName.ToString();
		const FString& DefaultToSelfMetaValue = Function->GetMetaData(FBlueprintMetadata::MD_DefaultToSelf);
		const FString& WorldContextMetaValue  = Function->GetMetaData(FBlueprintMetadata::MD_WorldContext);
		bool bIsSelfPin = ((PinNameStr == DefaultToSelfMetaValue) || (PinNameStr == WorldContextMetaValue));

		if (!bShowWorldContextPin || !bIsSelfPin)
		{
			Pin->bHidden = true;
			Pin->bNotConnectable = InternalPins.Contains(Pin->PinName);
		}
	}

}
```