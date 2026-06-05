---
title: "DontCollapseCategories"
id: "UCLASS.DontCollapseCategories"
kind: "specifier"
symbol: "DontCollapseCategories"
scope: "UCLASS"
category: "Category"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "使继承自基类的CollapseCatogories说明符无效"
usage: "UCLASS / Category"
---

# DontCollapseCategories

## Decision Summary

- **Use when:** `DontCollapseCategories` specifier 的 `UCLASS / Category` 场景需要：使继承自基类的CollapseCatogories说明符无效。
- **Do not use when:** 声明宏、目标类型或代码契约不属于 `UCLASS / Category`。
- **Requires:** specifier 必须放在 UE5.8 UHT 支持的宏和声明位置，并满足正文 caveat。
- **Conflicts:** 不要和同类互斥 specifier 或语义相反的暴露/持久化/网络规则混用。
- **Prefer instead:** 能用更窄暴露范围或更明确 metadata 表达时，优先选择更窄方案。

- **功能描述：**  使继承自基类的CollapseCatogories说明符无效。
- **引擎模块：** Category
- **元数据类型：** bool
- **作用机制：** 在ClassFlags中去除CLASS_CollapseCategories
- **关联项：** [CollapseCategories](CollapseCategories.md)
- **常用程度：★★**

理论上是去除类标志上的CLASS_CollapseCategories标志。可以重新打开所有的属性显示。

## 行为

UE5.8 UHT 移除 `CLASS_CollapseCategories`，用于恢复分类显示。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtClassSpecifiers.cs` class specifier branch
  - UE5.8 `UhtClass.cs` class flag/metadata resolution and validation

## 常见误用

把 class specifier 的 metadata/flag 结果和 property/function specifier 混淆；或忽略继承/撤销类 specifier 的相互作用。
