# UIMin

功能描述: 指定数字输入框上滚动条拖动的最小范围值
使用位置: UPROPERTY
Feature: Editor
引擎模块: Numeric Property
元数据类型: float/int
限制类型: float,int32
Status: Done
Sub-item: UIMax (UIMax.md), ClampMin (ClampMin.md), ClampMax (ClampMax.md)
常用程度: 5

UIMin-UIMax和ClampMin-ClampMax的区别是，UI系列阻止用户在拖动鼠标的时候把值超过某个范围，但是用户依然可以手动输入超过这个范围的值。而Clamp系列是实际的值的范围限制，用户拖动或者手动输入值都不允许超过这个范围。

这两个限制都无法限制蓝图下直接修改值。

测试代码：

```cpp
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MinMaxTest)
	float MyFloat_NoMinMax = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MinMaxTest, meta = (UIMin = "0", UIMax = "100"))
	float MyFloat_HasMinMax_UI = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MinMaxTest, meta = (ClampMin = "0", ClampMax = "100"))
	float MyFloat_HasMinMax_Clamp = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MinMaxTest, meta = (ClampMin = "0", ClampMax = "100",UIMin = "20", UIMax = "50"))
	float MyFloat_HasMinMax_ClampAndUI = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MinMaxTest, meta = (ClampMin = "20", ClampMax = "50",UIMin = "0", UIMax = "100"))
	float MyFloat_HasMinMax_ClampAndUI2= 100;
```

测试效果：

- 从MyFloat_HasMinMax_UI发现，UIMin, UIMax限制数字输入框滚动条的范围，但依然可以手动输入超过的值999
- 从MyFloat_HasMinMax_Clamp 发现，ClampMin，ClampMax 会同时限制UI和手动输入的范围。
- 从MyFloat_HasMinMax_ClampAndUI和MyFloat_HasMinMax_ClampAndUI2发现，UI的滚动条会取UI的限制和Clamp限制的更窄范围，而实际输入值也是会被限制在更窄的范围内。

![MinMax2.gif](UIMin/MinMax2.gif)

## 原理：

TNumericPropertyParams在构造的时候就会取得一些meta来初始化这些变量。否则就会成为默认值。

数值类型有实际的最小最大值（MinValue-MaxValue），是由ClampMin和ClampMax提供的。也有UI上的最小最大值（MinSliderValue-MaxSliderValue），是由Max(UImin,ClampMin)和Min(UIMax,ClampMax)提供的，即取最小的范围来保障合法输入。

```cpp
template<typename NumericType>
struct TNumericPropertyParams
{
	if (MetaDataGetter.IsBound())
	{
		UIMinString = MetaDataGetter.Execute("UIMin");
		UIMaxString = MetaDataGetter.Execute("UIMax");
		SliderExponentString = MetaDataGetter.Execute("SliderExponent");
		LinearDeltaSensitivityString = MetaDataGetter.Execute("LinearDeltaSensitivity");
		DeltaString = MetaDataGetter.Execute("Delta");
		ClampMinString = MetaDataGetter.Execute("ClampMin");
		ClampMaxString = MetaDataGetter.Execute("ClampMax");
		ForcedUnits = MetaDataGetter.Execute("ForceUnits");
		WheelStepString = MetaDataGetter.Execute("WheelStep");
	}
	
	TOptional<NumericType> MinValue;
	TOptional<NumericType> MaxValue;
	TOptional<NumericType> MinSliderValue;
	TOptional<NumericType> MaxSliderValue;
	NumericType SliderExponent;
	NumericType Delta;
	int32 LinearDeltaSensitivity;
	TOptional<NumericType> WheelStep;
}
//最终这些值会传输给
SAssignNew(SpinBox, SSpinBox<NumericType>)
	.Style(InArgs._SpinBoxStyle)
	.Font(InArgs._Font.IsSet() ? InArgs._Font : InArgs._EditableTextBoxStyle->TextStyle.Font)
	.Value(this, &SNumericEntryBox<NumericType>::OnGetValueForSpinBox)
	.Delta(InArgs._Delta)
	.ShiftMultiplier(InArgs._ShiftMultiplier)
	.CtrlMultiplier(InArgs._CtrlMultiplier)
	.LinearDeltaSensitivity(InArgs._LinearDeltaSensitivity)
	.SupportDynamicSliderMaxValue(InArgs._SupportDynamicSliderMaxValue)
	.SupportDynamicSliderMinValue(InArgs._SupportDynamicSliderMinValue)
	.OnDynamicSliderMaxValueChanged(InArgs._OnDynamicSliderMaxValueChanged)
	.OnDynamicSliderMinValueChanged(InArgs._OnDynamicSliderMinValueChanged)
	.OnValueChanged(OnValueChanged)
	.OnValueCommitted(OnValueCommitted)
	.MinFractionalDigits(MinFractionalDigits)
	.MaxFractionalDigits(MaxFractionalDigits)
	.MinSliderValue(InArgs._MinSliderValue)
	.MaxSliderValue(InArgs._MaxSliderValue)
	.MaxValue(InArgs._MaxValue)
	.MinValue(InArgs._MinValue)
	.SliderExponent(InArgs._SliderExponent)
	.SliderExponentNeutralValue(InArgs._SliderExponentNeutralValue)
	.EnableWheel(InArgs._AllowWheel)
	.BroadcastValueChangesPerKey(InArgs._BroadcastValueChangesPerKey)
	.WheelStep(InArgs._WheelStep)
	.OnBeginSliderMovement(InArgs._OnBeginSliderMovement)
	.OnEndSliderMovement(InArgs._OnEndSliderMovement)
	.MinDesiredWidth(InArgs._MinDesiredValueWidth)
	.TypeInterface(Interface)
	.ToolTipText(this, &SNumericEntryBox<NumericType>::GetValueAsText);
	
	
//最后
void SSpinBox<NumericType>::CommitValue(NumericType NewValue, double NewSpinValue, ECommitMethod CommitMethod, ETextCommit::Type OriginalCommitInfo)
{
	if (CommitMethod == CommittedViaSpin || CommitMethod == CommittedViaArrowKey)
	{
		const NumericType LocalMinSliderValue = GetMinSliderValue();
		const NumericType LocalMaxSliderValue = GetMaxSliderValue();
		NewValue = FMath::Clamp<NumericType>(NewValue, LocalMinSliderValue, LocalMaxSliderValue);
		NewSpinValue = FMath::Clamp<double>(NewSpinValue, (double)LocalMinSliderValue, (double)LocalMaxSliderValue);
	}
	
	{
		const NumericType LocalMinValue = GetMinValue();
		const NumericType LocalMaxValue = GetMaxValue();
		NewValue = FMath::Clamp<NumericType>(NewValue, LocalMinValue, LocalMaxValue);
		NewSpinValue = FMath::Clamp<double>(NewSpinValue, (double)LocalMinValue, (double)LocalMaxValue);
	}
	
	// Update the internal value, this needs to be done before rounding.
	InternalValue = NewSpinValue;
	
	const bool bAlwaysUsesDeltaSnap = GetAlwaysUsesDeltaSnap();
	// If needed, round this value to the delta. Internally the value is not held to the Delta but externally it appears to be.
	if (CommitMethod == CommittedViaSpin || CommitMethod == CommittedViaArrowKey || bAlwaysUsesDeltaSnap)
	{
		NumericType CurrentDelta = Delta.Get();
		if (CurrentDelta != NumericType())
		{
			NewValue = FMath::GridSnap<NumericType>(NewValue, CurrentDelta); // snap numeric point value to nearest Delta
		}
	}
	
	// Update the max slider value based on the current value if we're in dynamic mode
	if (SupportDynamicSliderMaxValue.Get() && ValueAttribute.Get() > GetMaxSliderValue())
	{
		ApplySliderMaxValueChanged(float(ValueAttribute.Get() - GetMaxSliderValue()), true);
	}
	else if (SupportDynamicSliderMinValue.Get() && ValueAttribute.Get() < GetMinSliderValue())
	{
		ApplySliderMinValueChanged(float(ValueAttribute.Get() - GetMinSliderValue()), true);
	}
}

```