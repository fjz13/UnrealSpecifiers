---
title: "ExpandBoolAsExecs"
id: "meta.ExpandBoolAsExecs"
kind: "meta"
symbol: "ExpandBoolAsExecs"
category: "Blueprint"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "是ExpandEnumAsExecs的别名，完全等价其功能"
usage: "UFUNCTION"
---

# ExpandBoolAsExecs

- **功能描述：** 是ExpandEnumAsExecs的别名，完全等价其功能。
- **使用位置：** UFUNCTION
- **元数据类型：** string="abc"
- **关联项：** [ExpandEnumAsExecs](ExpandEnumAsExecs.md)
- **常用程度：** ★★★★★

## 行为

UE5.8 function metadata；UHT validator 与 `ExpandEnumAsExecs` 共用校验，BlueprintGraph 视作 bool exec 展开。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `ObjectMacros.h` metadata declaration/comment
  - UE5.8 `BlueprintGraph` metadata constants or node usage

## 常见误用

参数名、属性名或目标宏写错导致 metadata 被保留但没有对应编辑器/Blueprint 行为。
