# NeverAsPin

- **Function Description:** Ensures that a specific attribute of an animation node is never exposed as a pin in the animation blueprint
- **Usage Location:** UPROPERTY
- **Engine Module:** Pin
- **Metadata Type:** bool
- **Restriction Type:** FAnimNode_Base
- **Associated Items:** [PinShownByDefault](../PinShownByDefault/PinShownByDefault.md)
- **Commonly Used:** ★★★

The NeverAsPin feature is not utilized in the source code because, by default, it is not supported as a pin, making its inclusion optional.

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

## Testing Code:

The attribute MyInt_NeverAsPin can only be displayed like the default attribute on the right and cannot be shown as a pin.

![PinShown](PinShown.gif)

## 测试效果:

It has been observed that bNeverShow is not in use, as the attribute is inherently not supported as a pin by default.

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