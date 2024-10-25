# PinShownByDefault

- **Function description:** Exposes a specific attribute of an animation node as a pin by default within an animation blueprint, though this can be modified.
- **Use location:** UPROPERTY
- **Engine module:** AnimationGraph
- **Metadata type:** bool
- **Restriction type:** FAnimNode_Base
- **Associated items:** [AlwaysAsPin](../AlwaysAsPin/AlwaysAsPin.md), [NeverAsPin](../NeverAsPin/NeverAsPin.md)
- **Commonality:** ★★★

In the animation blueprint, a specific attribute of an animation node is made visible as a pin from the start.

Unlike conventional blueprints, attributes within FAnimNode_Base are not displayed on the node by default, hence the need for this meta to explicitly indicate which attributes should be made explicit.

PinShownByDefault is currently applicable only to animation blueprint nodes.

Conversely, PinHiddenByDefault can be used to hide attributes as pins.

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

UCLASS()
class INSIDEREDITOR_API UAnimGraphNode_MyTestPinShown : public UAnimGraphNode_Base
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, Category = Settings)
	FAnimNode_MyTestPinShown Node;
};
```

## Test Results:

It is evident that the two properties, MyInt_NotShown does not appear as a node by default and can only be edited in the details panel, whereas MyInt_PinShownByDefault is shown as a pin by default. PinShownByDefault can also be altered to remove the pin functionality.

![PinShown](PinShown.gif)

## Principle:

The sole usage in the source code is within FAnimBlueprintNodeOptionalPinManager, which is responsible for handling the display of pins on animation blueprint nodes.

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