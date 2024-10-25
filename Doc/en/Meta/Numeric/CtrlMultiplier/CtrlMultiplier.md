# CtrlMultiplier

- **Function description:** Specifies the multiplier for value changes in a numeric input box when scrolling with the mouse wheel or dragging with the mouse while the Ctrl key is pressed.
- **Usage location:** UPROPERTY
- **Engine module:** Numeric Property
- **Metadata type:** float/int
- **Restricted types:** Data structures: FVector, FRotator, FColor
- **Associated items:** [ShiftMultiplier](../ShiftMultiplier.md)
- **Commonly used:** ★★

Specifies the multiplier for value changes in a numeric input box when scrolling with the mouse wheel or dragging with the mouse while the Ctrl key is pressed.

- The default value for CtrlMultiplier is 0.1f, typically used as a fine-tuning mode.
- Directly setting it to a float attribute has no effect. By default, the CtrlMultiplier on a property is not applied to SNumericEntryBox and SSpinBox, as these do not directly derive meta from the property to set their own Multiplier values.
- In the source code, FMathStructCustomization is found to extract the values of CtrlMultiplier and ShiftMultiplier, allowing settings on mathematical structures such as FVector, FRotator, FColor
- If you define your own Customization and create an SSpinBox, you can manually extract the Multiplier value and apply it to the control.

## Test Code:

```cpp
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MultiplierTest, meta = (CtrlMultiplier = "5"))
	float MyFloat_HasCtrlMultiplier = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MultiplierTest, meta = (ShiftMultiplier = "100"))
	float MyFloat_HasShiftMultiplier = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MultiplierTest)
	FVector MyVector_NoMultiplier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MultiplierTest, meta = (CtrlMultiplier = "5"))
	FVector MyVector_HasCtrlMultiplier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MultiplierTest, meta = (ShiftMultiplier = "100"))
	FVector MyVector_HasShiftMultiplier;
```

## Test Results:

- It is observed that the test on a regular float attribute has no effect; pressing Ctrl and Shift still changes the values to the defaults of 0.1 and 10.f, respectively
- For the standard default FVector, pressing Ctrl and Shift also changes the values to the defaults of 0.1 and 10.f, respectively
- MyVector_HasCtrlMultiplier: It is noticed that pressing Ctrl results in an immediate change of 5 in the range
- MyVector_HasShiftMultiplier: It is noticed that pressing Shift results in an immediate change of 100 in the range
- Of course, the same effect occurs when dragging with the mouse, but the change is too abrupt, making the demonstration effect not very clear

![Multipiler](Multipiler.gif)

## Principle:

```cpp
SNumericEntryBox的构造函数里：
		, _ShiftMultiplier(10.f)
		, _CtrlMultiplier(0.1f)

void FMathStructCustomization::MakeHeaderRow(TSharedRef<class IPropertyHandle>& StructPropertyHandle, FDetailWidgetRow& Row)
{
	for (int32 ChildIndex = 0; ChildIndex < SortedChildHandles.Num(); ++ChildIndex)
	{
		TSharedRef<IPropertyHandle> ChildHandle = SortedChildHandles[ChildIndex];

		// Propagate metadata to child properties so that it's reflected in the nested, individual spin boxes
		ChildHandle->SetInstanceMetaData(TEXT("UIMin"), StructPropertyHandle->GetMetaData(TEXT("UIMin")));
		ChildHandle->SetInstanceMetaData(TEXT("UIMax"), StructPropertyHandle->GetMetaData(TEXT("UIMax")));
		ChildHandle->SetInstanceMetaData(TEXT("SliderExponent"), StructPropertyHandle->GetMetaData(TEXT("SliderExponent")));
		ChildHandle->SetInstanceMetaData(TEXT("Delta"), StructPropertyHandle->GetMetaData(TEXT("Delta")));
		ChildHandle->SetInstanceMetaData(TEXT("LinearDeltaSensitivity"), StructPropertyHandle->GetMetaData(TEXT("LinearDeltaSensitivity")));
		ChildHandle->SetInstanceMetaData(TEXT("ShiftMultiplier"), StructPropertyHandle->GetMetaData(TEXT("ShiftMultiplier")));
		ChildHandle->SetInstanceMetaData(TEXT("CtrlMultiplier"), StructPropertyHandle->GetMetaData(TEXT("CtrlMultiplier")));
		ChildHandle->SetInstanceMetaData(TEXT("SupportDynamicSliderMaxValue"), StructPropertyHandle->GetMetaData(TEXT("SupportDynamicSliderMaxValue")));
		ChildHandle->SetInstanceMetaData(TEXT("SupportDynamicSliderMinValue"), StructPropertyHandle->GetMetaData(TEXT("SupportDynamicSliderMinValue")));
		ChildHandle->SetInstanceMetaData(TEXT("ClampMin"), StructPropertyHandle->GetMetaData(TEXT("ClampMin")));
		ChildHandle->SetInstanceMetaData(TEXT("ClampMax"), StructPropertyHandle->GetMetaData(TEXT("ClampMax")));
		}
}
```