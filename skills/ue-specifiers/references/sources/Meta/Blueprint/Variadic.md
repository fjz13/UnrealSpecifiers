---
title: "Variadic"
id: "meta.Variadic"
kind: "meta"
symbol: "Variadic"
category: "Blueprint"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定该函数接受多个参数"
usage: "UFUNCTION"
---

# Variadic

- **功能描述：** 指定该函数接受多个参数

- **使用位置：** UFUNCTION

- **引擎模块：** Blueprint

- **元数据类型：** bool

- **关联项：**

  UFUNCTION：[Variadic](../../Specifier/UFUNCTION/UHT/Variadic/Variadic.md)

- **常用程度：** ★★★

## 行为

UE5.8 function metadata；BlueprintGraph custom thunk/variadic 标记。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `ObjectMacros.h` metadata declaration/comment
  - UE5.8 `BlueprintGraph` metadata constants or node usage

## 常见误用

参数名、属性名或目标宏写错导致 metadata 被保留但没有对应编辑器/Blueprint 行为。
