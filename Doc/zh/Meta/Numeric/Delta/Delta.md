# Delta

- **功能描述：** 设定数字输入框值改变的幅度为Delta的倍数
- **使用位置：** UPROPERTY
- **引擎模块：** Numeric Property
- **元数据类型：** float/int
- **限制类型：** float,int32
- **关联项：** [LinearDeltaSensitivity](../LinearDeltaSensitivity.md)
- **常用程度：** ★★★

设定数字输入框值改变的幅度为Delta的倍数。

## 注意的事项是：

1. 在全局使得变化值成为Delta的倍数
2. Delta默认值是0，这个时候代表没有设置，数字会指数改变。
3. 注意和WheelStep的区别是，Delta在鼠标左右拖动和按下键盘方向键的时候生效，WheelStep是只在鼠标滚轮变化的时候生效。二者虽然都是用来控制变化幅度，但作用范围不同。

## 测试代码：

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

## 测试效果：

- MyFloat_DefaultDelta ，默认情况下鼠标往右拖动变化很剧烈，变化呈指数上升。
- MyFloat_Delta10，鼠标往右拖动变化也很剧烈（最终到达的值也很巨大），但是变化始终以Delta为步幅。
- MyFloat_Delta10_UIMinMax ，限定了UIMinMax，导致最大值受限，但是变化其实是按照比例值线性（SliderExponent默认是1没有改变）。
- MyFloat_Delta10_LinearDeltaSensitivity50 ，在没有UIMinMax的情况下，且同时设置了LinearDeltaSensitivity，会导致鼠标往右拖动的整个过程中变化值始终是线性。LinearDeltaSensitivity越大越不敏感。因此一次一次缓慢的改变10
- MyFloat_Delta10_LinearDeltaSensitivity50_UIMinMax ，如果上面一个再加上UIMinMax，则发现又失去了LinearDeltaSensitivity的效果。因为LinearDeltaSensitivity不能在有滚动条的情况下生效。

![Delta](Delta.gif)

## 原理：

- 在方向键上下左右按键的时候每次变化正负Delta，但是OnKeyDown没有直接绑定，所以默认情况下按键只会触发焦点的转移。
- 基础step是0.1或1，如果没受到CtrlMultiplier和ShiftMultiplier的影响。
- 默认情况下，鼠标左右移动改变的差量中的指数部分是FMath::Pow((double)CurrentValue, (double)SliderExponent.Get())，SliderExponent默认是1，也就是越往左右两端改变的幅度越大。
- 在同时设置LinearDeltaSensitivity和Delta的情况下，鼠标左右移动改变的差量中的指数部分是FMath::Pow((double)Delta.Get(), (double)SliderExponent.Get())，即改变的差量在左右整个数轴上是线性一致的。
- 在最后提交值的时候，改变的差量值会被规范到Delta的倍数上来。

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