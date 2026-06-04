---
title: "AutoExpandCategories"
id: "meta.AutoExpandCategories"
kind: "meta"
symbol: "AutoExpandCategories"
category: "DetailsPanel"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定类内部的属性目录自动展开起来"
usage: "UCLASS"
---

# AutoExpandCategories

- **功能描述：** 指定类内部的属性目录自动展开起来

- **使用位置：** UCLASS

- **引擎模块：** DetailsPanel

- **元数据类型：** strings="a，b，c"

- **关联项：**

  UCLASS：[AutoExpandCategories](../../Specifier/UCLASS/Category/AutoExpandCategories/AutoExpandCategories.md), [AutoCollapseCategories](../../Specifier/UCLASS/Category/AutoCollapseCategories/AutoCollapseCategories.md)

- **常用程度：** ★★★

## 行为

UE5.8 class metadata/list；与 UCLASS `AutoExpandCategories` 对应，指定默认展开分类。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `ObjectMacros.h` property/class metadata declaration/comment
  - UE5.8 `PropertyEditor` Details metadata usage

## 常见误用

参数名、属性名或目标宏写错导致 metadata 被保留但没有对应编辑器/Blueprint 行为。
