---
title: "DontCollapseCategories"
id: "UCLASS.DontCollapseCategories"
kind: "specifier"
symbol: "DontCollapseCategories"
scope: "UCLASS"
category: "Category"
source_status: "imported_from_unreal_specifiers"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "使继承自基类的CollapseCatogories说明符无效"
usage: "UCLASS / Category"
---

# DontCollapseCategories

- **功能描述：**  使继承自基类的CollapseCatogories说明符无效。
- **引擎模块：** Category
- **元数据类型：** bool
- **作用机制：** 在ClassFlags中去除[CLASS_CollapseCategories](../../../Flags/EClassFlags/CLASS_CollapseCategories.md)
- **关联项：** [CollapseCategories](CollapseCategories/CollapseCategories.md)
- **常用程度：★★**

理论上是去除类标志上的CLASS_CollapseCategories标志。可以重新打开所有的属性显示。