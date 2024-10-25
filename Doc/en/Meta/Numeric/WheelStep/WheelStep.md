# WheelStep

- **Function description:** Specifies the value change induced by mouse wheel scrolling on a numeric input field
- **Usage location:** UPROPERTY
- **Engine module:** Numeric Property
- **Metadata type:** float/int
- **Commonality:** ★★★

Specifies the value change induced by mouse wheel scrolling up or down on a numeric input field.

## Default value rules:

If the property is a floating-point number and the UI scrollbar range is less than 10, then WheelStep=0.1; otherwise, it is 1

If the property is an integer, then WheelStep=1

## Test code:

```cpp
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WheelStepTest)
	float MyFloat_DefaultWheelStep = 50;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WheelStepTest, meta = (UIMin = "0", UIMax = "10"))
	float MyFloat_SmallWheelStep = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WheelStepTest, meta = (WheelStep = 10))
	float MyFloat_HasWheelStep = 50;
```

## Screenshot:

The default value does not specify UIMin or UIMax, and the value can also be changed by mouse wheel scrolling. The default is 1

The UI range for MyFloat_SmallWheelStep is only 10, so the default change increment is 0.1

If WheelStep is specified as 10, the value will change by 10 in one go

![WheelStep2](WheelStep2.gif)

## Principle:

As indicated by the code, if WheelStep is set, that value is used.

Otherwise, if it is a floating-point number and the UI scrollbar range is less than 10, then WheelStep=0.1; otherwise, it is 1

Otherwise, if it is an integer, then WheelStep=1

```cpp
	virtual FReply SSpinBox<NumericType>::OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override
	{
		if (bEnableWheel && PointerDraggingSliderIndex == INDEX_NONE && HasKeyboardFocus())
		{
			// If there is no WheelStep defined, we use 1.0 (Or 0.1 if slider range is <= 10)
			constexpr bool bIsIntegral = TIsIntegral<NumericType>::Value;
			const bool bIsSmallStep = !bIsIntegral && (GetMaxSliderValue() - GetMinSliderValue()) <= 10.0;
			double Step = WheelStep.IsSet() && WheelStep.Get().IsSet() ? WheelStep.Get().GetValue() : (bIsSmallStep ? 0.1 : 1.0);

			if (MouseEvent.IsControlDown())
			{
				// If no value is set for WheelSmallStep, we use the DefaultStep multiplied by the CtrlMultiplier
				Step *= CtrlMultiplier.Get();
			}
			else if (MouseEvent.IsShiftDown())
			{
				// If no value is set for WheelBigStep, we use the DefaultStep multiplied by the ShiftMultiplier
				Step *= ShiftMultiplier.Get();
			}

			const double Sign = (MouseEvent.GetWheelDelta() > 0) ? 1.0 : -1.0;
			const double NewValue = InternalValue + (Sign * Step);
			const NumericType RoundedNewValue = RoundIfIntegerValue(NewValue);

			return FReply::Handled();
		}

		return FReply::Unhandled();
	}
```