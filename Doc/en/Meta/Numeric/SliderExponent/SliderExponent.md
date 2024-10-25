# SliderExponent

- **Function Description:** Specifies the exponential distribution for the scroll bar's drag behavior on numeric input fields
- **Usage Location:** UPROPERTY
- **Engine Module:** Numeric Property
- **Metadata Type:** float/int
- **Restriction Type:** float, int32
- **Commonliness:** ★★★★★

Specifies the exponential distribution for the scroll bar's drag behavior on numeric input fields. The default value is 1.

This value must be used in conjunction with Min and Max

The term "exponential distribution" refers to how the percentage of the scroll bar changes as the text value being scrolled changes within the range of UIMin and Max. By default, the midpoint value is at 50%. However, we can also specify an exponent to create an exponential distribution curve. On the left side of the number axis, the curve starts off more gradual, allowing for finer adjustments. On the right side, as the curve steepens, the changes become more dramatic, and precision is lost.

## Test Code:

```cpp
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SliderTest, meta = (UIMin = "0", UIMax = "1000"))
	float MyFloat_DefaultSliderExponent = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SliderTest, meta = (UIMin = "0", UIMax = "1000", SliderExponent = 5))
	float MyFloat_HasSliderExponent = 100;
```

## Test Results:

It is evident that with SliderExponent=5, a text value of 100 falls within the UI range of 1000, starting close to the 0.3 position, with a fine range of adjustment before 500 and a rapid change thereafter, contrasting with the former scenario.

![SliderExponent](SliderExponent.gif)

## Principle:

The default value is 1. If not, the new percentage is calculated using SpinBoxComputeExponentSliderFraction. Readers can refer to the SpinBoxComputeExponentSliderFraction function to understand the details of the exponential distribution.

```cpp
const float CachedSliderExponent = SliderExponent.Get();
if (!FMath::IsNearlyEqual(CachedSliderExponent, 1.f))
{
	if (SliderExponentNeutralValue.IsSet() && SliderExponentNeutralValue.Get() > GetMinSliderValue() && SliderExponentNeutralValue.Get() < GetMaxSliderValue())
	{
		//Compute a log curve on both side of the neutral value
		float StartFractionFilled = Fraction((double)SliderExponentNeutralValue.Get(), (double)GetMinSliderValue(), (double)GetMaxSliderValue());
		FractionFilled = SpinBoxComputeExponentSliderFraction(FractionFilled, StartFractionFilled, CachedSliderExponent);
	}
	else
	{
		FractionFilled = 1.0f - FMath::Pow(1.0f - FractionFilled, CachedSliderExponent);
	}
}
```