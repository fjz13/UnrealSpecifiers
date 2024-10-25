# Delta

- **Function description:** Set the change amplitude of the numeric input box to a multiple of Delta
- **Usage location:** UPROPERTY
- **Engine module:** Numeric Property
- **Metadata type:** float/int
- **Restricted types:** float, int32
- **Associated items:** [LinearDeltaSensitivity](../LinearDeltaSensitivity.md)
- **Commonly used:** ★★★

Set the change amplitude of the numeric input box to a multiple of Delta.

## Notes:

1. Make the change value a multiple of Delta globally
2. The default value for Delta is 0, indicating no setting is applied; the number will change exponentially.
3. Note the difference from WheelStep: Delta is effective when the mouse is dragged left or right or when the arrow keys on the keyboard are pressed. WheelStep is only effective when the mouse wheel is used. Although both control the change amplitude, their scopes of application differ.

## Test code:

```cpp
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DeltaTest)
	float MyFloat_DefaultDelta = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DeltaTest, meta = (Delta = 10))
	float MyFloat_Delta10 = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DeltaTest, meta = (UIMin = "0", UIMax = "1000", Delta = 10))
	float MyFloat_Delta10_UIMinMax = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DeltaTest, meta = (Delta = 10, LinearDeltaSensitivity = 50))
	float MyFloat_Delta10_LinearDeltaSensitivity50 = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DeltaTest, meta = (UIMin = "0", UIMax = "1000", Delta = 10, LinearDeltaSensitivity = 50))
	float MyFloat_Delta10_LinearDeltaSensitivity50_UIMinMax = 100;
```

## Test effects:

- MyFloat_DefaultDelta: By default, dragging the mouse to the right causes drastic changes, with values increasing exponentially.
- MyFloat_Delta10: Dragging the mouse to the right also causes drastic changes (with the final value reaching a very large number), but the changes are always in steps of Delta.
- MyFloat_Delta10_UIMinMax: With UIMinMax set, the maximum value is restricted, but the change is actually linear according to the proportional value (SliderExponent defaults to 1 and remains unchanged).
- MyFloat_Delta10_LinearDeltaSensitivity50: Without UIMinMax and with LinearDeltaSensitivity set, the change value remains linear throughout the entire process of dragging the mouse to the right. The higher the LinearDeltaSensitivity, the less sensitive it is, resulting in a slow change of 10 each time
- MyFloat_Delta10_LinearDeltaSensitivity50_UIMinMax: If UIMinMax is added to the previous case, the effect of LinearDeltaSensitivity is lost. This is because LinearDeltaSensitivity cannot take effect when a scrollbar is present.

![Delta](Delta.gif)

## Principle:

- When the up, down, left, or right arrow keys are pressed, the value changes by a positive or negative Delta each time. However, OnKeyDown is not directly bound, so by default, pressing these keys will only shift the focus.
- The base step is 0.1 or 1, unless affected by CtrlMultiplier or ShiftMultiplier.
- By default, the exponential part of the change in value when moving the mouse left or right is calculated as FMath::Pow((double)CurrentValue, (double)SliderExponent.Get()). The default value for SliderExponent is 1, meaning the change in amplitude is greater toward the left and right ends.
- When both LinearDeltaSensitivity and Delta are set, the exponential part of the change in value when moving the mouse left or right is calculated as FMath::Pow((double)Delta.Get(), (double)SliderExponent.Get()), making the change in value linearly consistent across the entire range of the number line from left to right.
- When the final value is submitted, the changed delta value is normalized to a multiple of Delta.

```cpp
, _Delta(0)
virtual FReply SSpinBox<NumericType>::OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override
{
		if (bUnlimitedSpinRange)
		{
				// If this control has a specified delta and sensitivity then we use that instead of the current value for determining how much to change.
				const double Sign = (MouseEvent.GetCursorDelta().X > 0) ? 1.0 : -1.0;

				if (LinearDeltaSensitivity.IsSet() && LinearDeltaSensitivity.Get() != 0 && Delta.IsSet() && Delta.Get() > 0)
				{
								const double MouseDelta = FMath::Abs(MouseEvent.GetCursorDelta().X / (float)LinearDeltaSensitivity.Get());
								NewValue = InternalValue + (Sign * MouseDelta * FMath::Pow((double)Delta.Get(), (double)SliderExponent.Get())) * Step;
				}
				else
				{
								const double MouseDelta = FMath::Abs(MouseEvent.GetCursorDelta().X / SliderWidthInSlateUnits);
								const double CurrentValue = FMath::Clamp<double>(FMath::Abs(InternalValue), 1.0, (double)std::numeric_limits<NumericType>::max());
								NewValue = InternalValue + (Sign * MouseDelta * FMath::Pow((double)CurrentValue, (double)SliderExponent.Get())) * Step;
				}
		}
}

virtual FReply SSpinBox<NumericType>::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override
{
		else if (Key == EKeys::Up || Key == EKeys::Right)
		{
			const NumericType LocalValueAttribute = ValueAttribute.Get();
			const NumericType LocalDelta = Delta.Get();
			InternalValue = (double)LocalValueAttribute;
			CommitValue(LocalValueAttribute + LocalDelta, InternalValue + (double)LocalDelta, CommittedViaArrowKey, ETextCommit::OnEnter);
			ExitTextMode();
			return FReply::Handled();
		}
		else if (Key == EKeys::Down || Key == EKeys::Left)
		{
			const NumericType LocalValueAttribute = ValueAttribute.Get();
			const NumericType LocalDelta = Delta.Get();
			InternalValue = (double)LocalValueAttribute;
			CommitValue(LocalValueAttribute - LocalDelta, InternalValue + (double)LocalDelta, CommittedViaArrowKey, ETextCommit::OnEnter);
			ExitTextMode();
			return FReply::Handled();
		}
}

void SSpinBox<NumericType>::CommitValue(NumericType NewValue, double NewSpinValue, ECommitMethod CommitMethod, ETextCommit::Type OriginalCommitInfo)
{
	// If needed, round this value to the delta. Internally the value is not held to the Delta but externally it appears to be.
	if (CommitMethod == CommittedViaSpin || CommitMethod == CommittedViaArrowKey || bAlwaysUsesDeltaSnap)
	{
		NumericType CurrentDelta = Delta.Get();
		if (CurrentDelta != NumericType())
		{
			NewValue = FMath::GridSnap<NumericType>(NewValue, CurrentDelta); // snap numeric point value to nearest Delta
		}
	}

}

```