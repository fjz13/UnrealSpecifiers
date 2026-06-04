---
title: "ShiftMultiplier"
id: "meta.ShiftMultiplier"
kind: "meta"
symbol: "ShiftMultiplier"
category: "Numeric"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定数字输入框在Shift按下时鼠标轮滚动和鼠标拖动改变值的倍率"
usage: "UPROPERTY"
---

# ShiftMultiplier

- **功能描述：** 指定数字输入框在Shift按下时鼠标轮滚动和鼠标拖动改变值的倍率。
- **使用位置：** UPROPERTY
- **引擎模块：** Numeric Property
- **元数据类型：** float/int
- **限制类型：** 数据结构：FVector，FRotator，FColor
- **关联项：** [CtrlMultiplier](CtrlMultiplier/CtrlMultiplier.md)
- **常用程度：** ★★

默认值是10.f

Shift的模式可以认为是一种快调模式，可以快速的改变值。

## 行为

UE5.8 numeric metadata；numeric entry/spinbox 交互使用 Shift 修饰倍率。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `ObjectMacros.h` numeric property metadata declaration/comment
  - UE5.8 Details numeric/color customization metadata usage

## 常见误用

参数名、属性名或目标宏写错导致 metadata 被保留但没有对应编辑器/Blueprint 行为。
