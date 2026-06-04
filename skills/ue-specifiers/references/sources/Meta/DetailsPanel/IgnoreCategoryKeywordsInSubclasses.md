---
title: "IgnoreCategoryKeywordsInSubclasses"
id: "meta.IgnoreCategoryKeywordsInSubclasses"
kind: "meta"
symbol: "IgnoreCategoryKeywordsInSubclasses"
category: "DetailsPanel"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "用于让一个类的首个子类忽略所有继承的 ShowCategories 和 HideCategories 说明符"
usage: "UCLASS"
---

# IgnoreCategoryKeywordsInSubclasses

- **功能描述：** 用于让一个类的首个子类忽略所有继承的 ShowCategories 和 HideCategories 说明符。
- **使用位置：** UCLASS
- **引擎模块：** DetailsPanel
- **元数据类型：** bool
Related To UCLASS: ComponentWrapperClass (../../Specifier/UCLASS/ComponentWrapperClass.md)
- **常用程度：** ★

和ComponentWrapperClass相互关联

## 行为

UE5.8 class metadata；组件 wrapper 等路径会用它阻止分类关键字继续影响子类。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `ObjectMacros.h` property/class metadata declaration/comment
  - UE5.8 `PropertyEditor` Details metadata usage
- 批次记录：`references/audits/ue5.8-p1-complete-pass.md`。

## 常见误用

参数名、属性名或目标宏写错导致 metadata 被保留但没有对应编辑器/Blueprint 行为。
