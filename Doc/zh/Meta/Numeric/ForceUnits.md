---
title: "ForceUnits"
id: "meta.ForceUnits"
kind: "meta"
symbol: "ForceUnits"
category: "Numeric"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "固定设定属性值的单位保持不变，不根据数值动态调整显示单位"
usage: "UPROPERTY"
---

# ForceUnits

- **功能描述：** 固定设定属性值的单位保持不变，不根据数值动态调整显示单位。
- **使用位置：** UPROPERTY
- **引擎模块：** Numeric Property
- **元数据类型：** string="abc"
- **限制类型：** float,int32
- **关联项：** [Units](Units/Units.md)
- **常用程度：** ★★★

## 行为

UE5.8 numeric metadata；ObjectMacros 标注为固定单位显示，区别于 `Units` 的本地化/自动换算。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `ObjectMacros.h` numeric property metadata declaration/comment
  - UE5.8 Details numeric/color customization metadata usage

## 常见误用

参数名、属性名或目标宏写错导致 metadata 被保留但没有对应编辑器/Blueprint 行为。
