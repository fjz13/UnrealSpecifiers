# SupportDynamicSliderMinValue

- **功能描述：** 支持数字输入框上滚动条的最小范围值在Alt按下时被动态改变
- **使用位置：** UPROPERTY
- **引擎模块：** Numeric Property
- **元数据类型：** bool
- **限制类型：** FVector4
- **关联项：** [SupportDynamicSliderMaxValue](../SupportDynamicSliderMaxValue.md)
- **常用程度：** ★

支持数字输入框上滚动条的最小范围值在Alt按下时被动态改变。

- 必须配合UIMin，UIMax使用，因为这样才有滚动条UI
- 一般情况下滚动条范围是初始设置好的，但该设置支持动态改变。方法是按下Alt拖动鼠标。
- 普通的float属性等是不支持该meta的，因为普通自动生成的的SPropertyEditorNumeric，没有从property meta中提取SupportDynamicSliderMinValue，因此即使设置了也不会生效。
- 目前源码中只有继承了FMathStructCustomization的FColorGradingVectorCustomizationBase（对应FVector4）才提取SupportDynamicSliderMinValue，然后自己创建SNumericEntryBox，从而正确的设置SupportDynamicSliderMinValue的值。
- 因此如果你也想使得自己的结构里的数字属性支持该功能，也需要手动创建Customization，然后在里面手动创建SNumericEntryBox，从而自己设置SupportDynamicSliderMinValue的值。

## 测试代码：

```cpp
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DynamicSliderTest, meta = (UIMin = "0", UIMax = "1"))
	FVector4 MyVector4_NoDynamicSlider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DynamicSliderTest, meta = (UIMin = "0", UIMax = "1", SupportDynamicSliderMinValue = "true", SupportDynamicSliderMaxValue = "true"))
	FVector4 MyVector4_SupportDynamicSlider;
```

## 测试结果：

可以看见MyVector4_NoDynamicSlider并无法更改0-1的滚动条范围。而MyVector4_SupportDynamicSlider在按下Alt同时拖动鼠标后可以改变最小和最大的UI范围。

![DynamicSlider](DynamicSlider.gif)

## 原理：

在SPropertyEditorNumeric里并不会去提取SupportDynamicSliderMinValue该属性，因此默认情况下该值是不生效的。

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