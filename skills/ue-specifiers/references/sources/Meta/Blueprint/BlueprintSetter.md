---
title: "BlueprintSetter"
id: "meta.BlueprintSetter"
kind: "meta"
symbol: "BlueprintSetter"
category: "Blueprint"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "采用一个自定义的set函数来读取"
usage: "UFUNCTION, UPROPERTY"
---

# BlueprintSetter

- **功能描述：** 采用一个自定义的set函数来读取。
  会默认设置BlueprintReadWrite.

- **使用位置：** UFUNCTION, UPROPERTY

- **引擎模块：** Blueprint

- **元数据类型：** string="abc"

- **关联项：**

  UFUNCTION：[BlueprintSetter](../../Specifier/UFUNCTION/Blueprint/BlueprintSetter.md)

  UPROPERTY：[BlueprintSetter](../../Specifier/UPROPERTY/Blueprint/BlueprintSetter.md)

- **常用程度：** ★★★

## 行为

UE5.8 property metadata；BlueprintGraph/UHT property accessor metadata，指定 setter function。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `ObjectMacros.h` metadata declaration/comment
  - UE5.8 `BlueprintGraph` metadata constants or node usage

## 常见误用

参数名、属性名或目标宏写错导致 metadata 被保留但没有对应编辑器/Blueprint 行为。
