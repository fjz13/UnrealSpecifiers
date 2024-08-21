# WheelStep

- **功能描述：** 指定数字输入框上鼠标轮上下滚动产生的变化值
- **使用位置：** UPROPERTY
- **引擎模块：** Numeric Property
- **元数据类型：** float/int
- **常用程度：** ★★★

指定数字输入框上鼠标轮上下滚动产生的变化值。

## 默认值的规则：

如果属性是浮点数且UI滚动条范围小于10，则WheelStep=0.1，否则为1

如果属性是整数，则WheelStep=1

## 测试代码：

```cpp
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WheelStepTest)
	float MyFloat_DefaultWheelStep = 50;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WheelStepTest, meta = (UIMin = "0", UIMax = "10"))
	float MyFloat_SmallWheelStep = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WheelStepTest, meta = (WheelStep = 10))
	float MyFloat_HasWheelStep = 50;
```

## 效果图：

默认值不指定UIMin，UIMax也可以鼠标轮滚动变化值。默认为1

MyFloat_SmallWheelStep的UI范围只有10，则默认改变幅度0.1

指定WheelStep =10，则一下子变化10

![WheelStep2.gif](WheelStep2.gif)

## 原理：

通过代码可知，如果设置了WheelStep则用该值。

否则如果是浮点数且UI滚动条范围小于10，则WheelStep=0.1，否则为1

否则如果是整数，则WheelStep=1

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
