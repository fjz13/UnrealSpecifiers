---
title: "Grouping"
id: "meta.Grouping"
kind: "meta"
symbol: "Grouping"
scope: "UMETA"
category: "Enum"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "Enum /Script/Engine.EAlphaBlendOption"
usage: "UENUM::UMETA"
---

# Grouping

## Decision Summary

- **Use when:** `Grouping` metadata 的 `UENUM::UMETA` 场景需要：Enum /Script/Engine.EAlphaBlendOption。
- **Do not use when:** 目标声明不属于 `UENUM::UMETA`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** Enum /Script/Engine.EAlphaBlendOption
- **使用位置：** UENUM::UMETA
- **引擎模块：** Enum Property
- **元数据类型：** bool
- **常用程度：** 0

感觉是用在Sequencer里面的，只用在SEasingFunctionGridWidget里面。
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。

## 源码例子：

```cpp
UENUM()
enum class EAlphaBlendOption : uint8
{
	Linear = 0 UMETA(Grouping = Linear, DisplayName = "Linear", ToolTip = "Linear interpolation"),
	Cubic UMETA(Grouping = Cubic, DisplayName = "Cubic In", ToolTip = "Cubic-in interpolation"),
	HermiteCubic UMETA(Grouping = Cubic, DisplayName = "Hermite-Cubic InOut", ToolTip = "Hermite-Cubic"),
	Sinusoidal UMETA(Grouping = Sinusoidal, DisplayName = "Sinusoidal", ToolTip = "Sinusoidal interpolation"),
	QuadraticInOut UMETA(Grouping = Quadratic, DisplayName = "Quadratic InOut", ToolTip = "Quadratic in-out interpolation"),
	CubicInOut UMETA(Grouping = Cubic, DisplayName = "Cubic InOut", ToolTip = "Cubic in-out interpolation"),
	QuarticInOut UMETA(Grouping = Quartic, DisplayName = "Quartic InOut", ToolTip = "Quartic in-out interpolation"),
	QuinticInOut UMETA(Grouping = Quintic, DisplayName = "Quintic InOut", ToolTip = "Quintic in-out interpolation"),
	CircularIn UMETA(Grouping = Circular, DisplayName = "Circular In", ToolTip = "Circular-in interpolation"),
	CircularOut UMETA(Grouping = Circular, DisplayName = "Circular Out", ToolTip = "Circular-out interpolation"),
	CircularInOut UMETA(Grouping = Circular, DisplayName = "Circular InOut", ToolTip = "Circular in-out interpolation"),
	ExpIn UMETA(Grouping = Exponential, DisplayName = "Exponential In", ToolTip = "Exponential-in interpolation"),
	ExpOut UMETA(Grouping = Exponential, DisplayName = "Exponential Out", ToolTip = "Exponential-Out interpolation"),
	ExpInOut UMETA(Grouping = Exponential, DisplayName = "Exponential InOut", ToolTip = "Exponential in-out interpolation"),
	Custom UMETA(Grouping = Custom, DisplayName = "Custom", ToolTip = "Custom interpolation, will use custom curve inside an FAlphaBlend or linear if none has been set"),
};

UENUM()
enum class EMovieSceneBuiltInEasing : uint8
{
	// Linear easing
	Linear UMETA(Grouping=Linear,DisplayName="Linear"),
	// Sinusoidal easing
	SinIn UMETA(Grouping=Sinusoidal,DisplayName="Sinusoidal In"), SinOut UMETA(Grouping=Sinusoidal,DisplayName="Sinusoidal Out"), SinInOut UMETA(Grouping=Sinusoidal,DisplayName="Sinusoidal InOut"),
	// Quadratic easing
	QuadIn UMETA(Grouping=Quadratic,DisplayName="Quadratic In"), QuadOut UMETA(Grouping=Quadratic,DisplayName="Quadratic Out"), QuadInOut UMETA(Grouping=Quadratic,DisplayName="Quadratic InOut"),
	// Cubic easing
	Cubic UMETA(Grouping = Cubic, DisplayName = "Cubic"), CubicIn UMETA(Grouping=Cubic,DisplayName="Cubic In"), CubicOut UMETA(Grouping=Cubic,DisplayName="Cubic Out"), CubicInOut UMETA(Grouping=Cubic,DisplayName="Cubic InOut"), HermiteCubicInOut UMETA(Grouping = Cubic, DisplayName = "Hermite-Cubic InOut"),
	// Quartic easing
	QuartIn UMETA(Grouping=Quartic,DisplayName="Quartic In"), QuartOut UMETA(Grouping=Quartic,DisplayName="Quartic Out"), QuartInOut UMETA(Grouping=Quartic,DisplayName="Quartic InOut"),
	// Quintic easing
	QuintIn UMETA(Grouping=Quintic,DisplayName="Quintic In"), QuintOut UMETA(Grouping=Quintic,DisplayName="Quintic Out"), QuintInOut UMETA(Grouping=Quintic,DisplayName="Quintic InOut"),
	// Exponential easing
	ExpoIn UMETA(Grouping=Exponential,DisplayName="Exponential In"), ExpoOut UMETA(Grouping=Exponential,DisplayName="Exponential Out"), ExpoInOut UMETA(Grouping=Exponential,DisplayName="Exponential InOut"),
	// Circular easing
	CircIn UMETA(Grouping=Circular,DisplayName="Circular In"), CircOut UMETA(Grouping=Circular,DisplayName="Circular Out"), CircInOut UMETA(Grouping=Circular,DisplayName="Circular InOut"),
	// Custom
	Custom UMETA(Grouping = Custom, DisplayName = "Custom"),
};

```

## 原理：

```cpp
TArray<SEasingFunctionGridWidget::FGroup> SEasingFunctionGridWidget::ConstructGroups(const TSet<EMovieSceneBuiltInEasing>& FilterExclude)
{
	const UEnum* EasingEnum = StaticEnum<EMovieSceneBuiltInEasing>();
	check(EasingEnum)

	TArray<FGroup> Groups;

	for (int32 NameIndex = 0; NameIndex < EasingEnum->NumEnums() - 1; ++NameIndex)
	{
		const FString& Grouping = EasingEnum->GetMetaData(TEXT("Grouping"), NameIndex);
		EMovieSceneBuiltInEasing Value = (EMovieSceneBuiltInEasing)EasingEnum->GetValueByIndex(NameIndex);

		if (FilterExclude.IsEmpty() || FilterExclude.Find(Value) == nullptr)
		{
			FindOrAddGroup(Groups, Grouping).Values.Add(Value);
		}
	}

	return Groups;
}
```
