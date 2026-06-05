---
title: "NotBlueprintable"
id: "UCLASS.NotBlueprintable"
kind: "specifier"
symbol: "NotBlueprintable"
scope: "UCLASS"
category: "Blueprint"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "不可在蓝图里继承，隐含作用也不可当作变量"
usage: "UCLASS / Blueprint"
---

# NotBlueprintable

## Decision Summary

- **Use when:** 类不应被 Blueprint 派生，即使继承链上可能允许 Blueprintable。
- **Do not use when:** 设计目标是允许 Blueprint 扩展该类。
- **Requires:** 确认下游工作流不依赖 Blueprint 子类。
- **Conflicts:** 与 `Blueprintable` 语义相反。
- **Prefer instead:** 只想禁止作为变量类型时考虑 `NotBlueprintType`。

- **功能描述：** 不可在蓝图里继承，隐含作用也不可当作变量
- **引擎模块：** Blueprint
- **元数据类型：** bool
- **作用机制：** 在Meta去除[IsBlueprintBase](../../../Meta/Blueprint/IsBlueprintBase.md)和[BlueprintType](../../../Meta/Blueprint/BlueprintType.md)
- **关联项：** [Blueprintable](Blueprintable.md)
- **常用程度：★★★★**

## 行为

UE5.8 UHT 默认 specifier 写入 `IsBlueprintBase=false`，并移除当前 metadata index 的 `BlueprintType`。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtClassSpecifiers.cs` class specifier branch
  - UE5.8 `UhtClass.cs` class flag/metadata resolution and validation

## 常见误用

把 class specifier 的 metadata/flag 结果和 property/function specifier 混淆；或忽略继承/撤销类 specifier 的相互作用。
