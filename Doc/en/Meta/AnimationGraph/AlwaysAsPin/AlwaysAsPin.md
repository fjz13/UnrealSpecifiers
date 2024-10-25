# AlwaysAsPin

- **Function Description:** Ensures that a specific attribute of an animation node is always exposed as a pin in the animation blueprint
- **Usage Location:** UPROPERTY
- **Engine Module:** Pin
- **Metadata Type:** bool
- **Restriction Type:** FAnimNode_Base
- **Associated Items:** [PinShownByDefault](../PinShownByDefault/PinShownByDefault.md)
- **Commonality:** ★★★

The difference from PinShownByDefault is that AlwaysAsPin will always display the attribute as a pin, whereas PinShownByDefault displays the pin by default but can be changed subsequently.

## Test Code:

```cpp
USTRUCT(BlueprintInternalUseOnly)
struct INSIDEREDITOR_API FAnimNode_MyTestPinShown : public FAnimNode_Base
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PinShownByDefaultTest)
	int32 MyInt_NotShown = 123;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PinShownByDefaultTest, meta = (PinShownByDefault))
	int32 MyInt_PinShownByDefault = 123;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PinShownByDefaultTest, meta = (AlwaysAsPin))
	int32 MyInt_AlwaysAsPin = 123;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PinShownByDefaultTest, meta = (NeverAsPin))
	int32 MyInt_NeverAsPin = 123;
};
```

## Test Results:

![PinShown](PinShown.gif)

## Principle:

As evident from the logic in the source code, bAlwaysShow will result in bShowPin being true, differing from PinShownByDefault in that AlwaysAsPin will always display the attribute as a pin. PinShownByDefault shows the pin by default and can be modified later.

```cpp
void FAnimBlueprintNodeOptionalPinManager::GetRecordDefaults(FProperty* TestProperty, FOptionalPinFromProperty& Record) const
{
	const UAnimationGraphSchema* Schema = GetDefault<UAnimationGraphSchema>();

	// Determine if this is a pose or array of poses
	FArrayProperty* ArrayProp = CastField<FArrayProperty>(TestProperty);
	FStructProperty* StructProp = CastField<FStructProperty>(ArrayProp ? ArrayProp->Inner : TestProperty);
	const bool bIsPoseInput = (StructProp  && StructProp->Struct->IsChildOf(FPoseLinkBase::StaticStruct()));

	//@TODO: Error if they specified two or more of these flags
	const bool bAlwaysShow = TestProperty->HasMetaData(Schema->NAME_AlwaysAsPin) || bIsPoseInput;
	const bool bOptional_ShowByDefault = TestProperty->HasMetaData(Schema->NAME_PinShownByDefault);
	const bool bOptional_HideByDefault = TestProperty->HasMetaData(Schema->NAME_PinHiddenByDefault);
	const bool bNeverShow = TestProperty->HasMetaData(Schema->NAME_NeverAsPin);
	const bool bPropertyIsCustomized = TestProperty->HasMetaData(Schema->NAME_CustomizeProperty);
	const bool bCanTreatPropertyAsOptional = CanTreatPropertyAsOptional(TestProperty);

	Record.bCanToggleVisibility = bCanTreatPropertyAsOptional && (bOptional_ShowByDefault || bOptional_HideByDefault);
	Record.bShowPin = bAlwaysShow || bOptional_ShowByDefault;
	Record.bPropertyIsCustomized = bPropertyIsCustomized;
}
```