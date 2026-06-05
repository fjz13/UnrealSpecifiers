---
title: "WheelStep"
id: "meta.WheelStep"
kind: "meta"
symbol: "WheelStep"
category: "Numeric"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定数字输入框上鼠标轮上下滚动产生的变化值"
usage: "UPROPERTY"
---

# WheelStep

## Decision Summary

- **Use when:** `WheelStep` metadata 的 `UPROPERTY` 场景需要：指定数字输入框上鼠标轮上下滚动产生的变化值。
- **Do not use when:** 目标声明不属于 `UPROPERTY`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

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

## 行为

UE5.8 numeric metadata；numeric entry 鼠标滚轮步长。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `ObjectMacros.h` numeric property metadata declaration/comment
  - UE5.8 Details numeric/color customization metadata usage

## 常见误用

参数名、属性名或目标宏写错导致 metadata 被保留但没有对应编辑器/Blueprint 行为。
