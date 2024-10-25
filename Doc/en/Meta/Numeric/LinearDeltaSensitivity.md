# LinearDeltaSensitivity

- **Function description:** After setting the Delta, further configure the numeric input box to change linearly along with its sensitivity to changes (the higher the value, the less sensitive it is)
- **Usage location:** UPROPERTY
- **Engine module:** Numeric Property
- **Metadata type:** float/int
- **Restriction type:** float, int32
- **Associated items:** [Delta](Delta/Delta.md)
- **Commonly used:** ★★★

Conditions for effectiveness:

1. First, set Delta > 0
2. Do not set UIMin, UIMax
3. Set LinearDeltaSensitivity > 0

## Test code:

```cpp
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DeltaTest, meta = (UIMin = "0", UIMax = "1000", Delta = 10))
	float MyFloat_Delta10_UIMinMax = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DeltaTest, meta = (Delta = 10, LinearDeltaSensitivity = 50))
	float MyFloat_Delta10_LinearDeltaSensitivity50 = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DeltaTest, meta = (UIMin = "0", UIMax = "1000", Delta = 10, LinearDeltaSensitivity = 50))
	float MyFloat_Delta10_LinearDeltaSensitivity50_UIMinMax = 100;
```

## Test results:

For an analysis of the effects, please refer to: Analysis of Delta

![Delta](Delta/Delta.gif)

## Principle:

It is evident that the code branch for linear change can only be entered only when there are no UIMinMax constraints and after Delta has been set.

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

```