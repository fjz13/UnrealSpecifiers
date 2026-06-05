---
title: "Category"
id: "meta.Category"
kind: "meta"
symbol: "Category"
category: "DetailsPanel"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定属性在细节面板中的分类"
usage: "UFUNCTION, UPROPERTY"
---

# Category

## Decision Summary

- **Use when:** 暴露到 Details Panel 或 Blueprint 的成员需要清晰分组。
- **Do not use when:** 成员没有 editor/Blueprint 暴露，或分类只是在 C++ 中自我说明。
- **Requires:** 分类字符串应稳定、短且符合项目命名约定。
- **Conflicts:** 不提供访问、编辑、保存或复制语义。
- **Prefer instead:** 不暴露的 C++ 成员用代码结构和注释表达分组。

- **功能描述：** 指定属性在细节面板中的分类

- **使用位置：** UFUNCTION, UPROPERTY

- **引擎模块：** DetailsPanel

- **元数据类型：** string="A | B | C"

- **关联项：**

  UFUNCTION：[Category](../../Specifier/UFUNCTION/Category.md)
  UPROPERTY：[Category](../../Specifier/UPROPERTY/DetailsPanel/Category.md)

- **常用程度：** ★★★★★

## 行为

UE5.8 class/property/function metadata；UHT 默认 `Category` specifier 写入该 metadata，Blueprint exposed 成员通常需要它。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `ObjectMacros.h` property/class metadata declaration/comment
  - UE5.8 `PropertyEditor` Details metadata usage

## 常见误用

参数名、属性名或目标宏写错导致 metadata 被保留但没有对应编辑器/Blueprint 行为。
