# CtrlMultiplier

功能描述: 指定数字输入框在Ctrl按下时鼠标轮滚动和鼠标拖动改变值的倍率。
使用位置: UPROPERTY
Feature: Editor
引擎模块: Numeric Property
元数据类型: float/int
限制类型: 数据结构：FVector，FRotator，FColor
Status: Done
Sub-item: ShiftMultiplier (ShiftMultiplier.md)
常用程度: 2

指定数字输入框在Ctrl按下时鼠标轮滚动和鼠标拖动改变值的倍率。

- CtrlMultiplier的默认值是0.1f，一般作为一种精调模式。
- 直接设置到float属性上并无效果。默认情况下，属性上的CtrlMultiplier并不会设置到SNumericEntryBox和SSpinBox上，因为这二者并不会直接从property上提取meta来设置到其本身的Multiplier值上。
- 在源码里发现FMathStructCustomization里会提取CtrlMultiplier和ShiftMultiplier的值，因此我们可以在一些数学结构上设置，如FVector，FRotator，FColor
- 如果自己定义Customization和创建SSpinBox，则可以自己提取Multiplier的值自己设置到控件里去。

测试代码：

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

测试效果：

- 发现普通float属性测试并无效果，按下Ctrl和Shift依然是默认的改变值0.1和10.f
- 普通的默认FVector，按下Ctrl和Shift也是默认的改变值0.1和10.f
- MyVector_HasCtrlMultiplier，发现按下Ctrl，一下子改变幅度是5
- MyVector_HasShiftMultiplier，发现按下Shift，一下子改变幅度是100
- 当然用鼠标拖动也是一样的效果，只是那样改变太过剧烈，演示效果不明显

![Multipiler.gif](CtrlMultiplier/Multipiler.gif)

原理：

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