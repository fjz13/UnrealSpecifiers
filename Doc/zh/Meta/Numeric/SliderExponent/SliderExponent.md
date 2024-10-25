# SliderExponent

- **功能描述：** 指定数字输入框上滚动条拖动的变化指数分布
- **使用位置：** UPROPERTY
- **引擎模块：** Numeric Property
- **元数据类型：** float/int
- **限制类型：** float,int32
- **常用程度：** ★★★★★

指定数字输入框上滚动条拖动的变化指数分布。默认值是1。

该值必须配合Min，Max使用

所谓指数分布指的是在UIMin和Max的范围内，当滚动的文本值变化的时候，滚动条的百分比值如何变化。默认情况下，中间点的值就是在50%。但我们也可以指定一个指数，形成一条指数分布曲线，在数轴左侧一开始的时候比较平缓变动比较缓慢拥有更高的调整精度，在数轴的右侧结束的部分曲线变得陡峭变动剧烈就失去了精度。

## 测试代码：

```cpp
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SliderTest, meta = (UIMin = "0", UIMax = "1000"))
	float MyFloat_DefaultSliderExponent = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SliderTest, meta = (UIMin = "0", UIMax = "1000", SliderExponent = 5))
	float MyFloat_HasSliderExponent = 100;
```

## 测试效果：

可见SliderExponent=5的效果导致100的文本值落在UI 1000的范围内一开始就处于快0.3的位置，且变动的范围在500前比较精细，500后比较迅速。跟前者形成对比。

![SliderExponent](SliderExponent.gif)

## 原理：

默认的值是1，如果不是，则采用SpinBoxComputeExponentSliderFraction来计算新的百分比，读者可自行观察SpinBoxComputeExponentSliderFraction函数来了解指数分布的情况。

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