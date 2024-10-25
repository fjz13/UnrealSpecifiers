1	# SupportDynamicSliderMinValue

- **Function description:** Supports dynamically changing the minimum range value of the scrollbar on the numeric input field when the Alt key is pressed
- **Usage location:** UPROPERTY
- **Engine module:** Numeric Property
- **Metadata type:** bool
- **Restriction type:** FVector4
- **Related items:** [SupportDynamicSliderMaxValue](../SupportDynamicSliderMaxValue.md)
- **Commonly used:** ★

Enables the dynamic adjustment of the minimum range value of the scrollbar on the numeric input field when the Alt key is pressed.

- Must be used in conjunction with UIMin and UIMax, as the scrollbar UI is only available with these
- Usually, the scrollbar range is pre-set, but this setting allows for dynamic changes. The method is to press and hold the Alt key while dragging the mouse.
- Standard float properties do not support this meta, because the default SPropertyEditorNumeric does not extract SupportDynamicSliderMinValue from the property meta, rendering any settings ineffective.
- Currently, only FColorGradingVectorCustomizationBase (which corresponds to FVector4) and inherits from FMathStructCustomization extracts SupportDynamicSliderMinValue, and then creates SNumericEntryBox to correctly set the value of SupportDynamicSliderMinValue.
- Therefore, if you wish to enable this feature for numeric properties in your own structure, you will need to manually create a Customization and within it, manually create a SNumericEntryBox to set the value of SupportDynamicSliderMinValue.

## Test Code:

```cpp
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DynamicSliderTest, meta = (UIMin = "0", UIMax = "1"))
	FVector4 MyVector4_NoDynamicSlider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DynamicSliderTest, meta = (UIMin = "0", UIMax = "1", SupportDynamicSliderMinValue = "true", SupportDynamicSliderMaxValue = "true"))
	FVector4 MyVector4_SupportDynamicSlider;
```

## Test Results:

It can be observed that MyVector4_NoDynamicSlider is unable to change the scrollbar range of 0-1. In contrast, MyVector4_SupportDynamicSlider can adjust the minimum and maximum UI range after pressing and holding the Alt key while dragging the mouse.

![DynamicSlider](DynamicSlider.gif)

## Principle:

The property SupportDynamicSliderMinValue is not retrieved in SPropertyEditorNumeric, hence it is not effective by default.

```cpp
void SPropertyEditorNumeric<NumericType>::Construct( const FArguments& InArgs, const TSharedRef<FPropertyEditor>& InPropertyEditor )
{
	TNumericPropertyParams<NumericType> NumericPropertyParams(Property, MetaDataGetter);
	ChildSlot
	[
		SAssignNew(PrimaryWidget, SNumericEntryBox<NumericType>)
		// Only allow spinning if we have a single value
		.AllowSpin(bAllowSpin)
		.Value(this, &SPropertyEditorNumeric<NumericType>::OnGetValue)
		.Font(InArgs._Font)
		.MinValue(NumericPropertyParams.MinValue)
		.MaxValue(NumericPropertyParams.MaxValue)
		.MinSliderValue(NumericPropertyParams.MinSliderValue)
		.MaxSliderValue(NumericPropertyParams.MaxSliderValue)
		.SliderExponent(NumericPropertyParams.SliderExponent)
		.Delta(NumericPropertyParams.Delta)
		// LinearDeltaSensitivity needs to be left unset if not provided, rather than being set to some default
		.LinearDeltaSensitivity(NumericPropertyParams.GetLinearDeltaSensitivityAttribute())
		.AllowWheel(bAllowSpin)
		.WheelStep(NumericPropertyParams.WheelStep)
		.UndeterminedString(PropertyEditorConstants::DefaultUndeterminedText)
		.OnValueChanged(this, &SPropertyEditorNumeric<NumericType>::OnValueChanged)
		.OnValueCommitted(this, &SPropertyEditorNumeric<NumericType>::OnValueCommitted)
		.OnUndeterminedValueCommitted(this, &SPropertyEditorNumeric<NumericType>::OnUndeterminedValueCommitted)
		.OnBeginSliderMovement(this, &SPropertyEditorNumeric<NumericType>::OnBeginSliderMovement)
		.OnEndSliderMovement(this, &SPropertyEditorNumeric<NumericType>::OnEndSliderMovement)
		.TypeInterface(TypeInterface)
	];
	}

	virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override
	{
			if (MouseEvent.IsAltDown())
			{
							float DeltaToAdd = (float)MouseEvent.GetCursorDelta().X / SliderWidthInSlateUnits;

							if (SupportDynamicSliderMaxValue.Get() && (NumericType)InternalValue == GetMaxSliderValue())
							{
								ApplySliderMaxValueChanged(DeltaToAdd, false);
							}
							else if (SupportDynamicSliderMinValue.Get() && (NumericType)InternalValue == GetMinSliderValue())
							{
								ApplySliderMinValueChanged(DeltaToAdd, false);
							}
			}
	}
```