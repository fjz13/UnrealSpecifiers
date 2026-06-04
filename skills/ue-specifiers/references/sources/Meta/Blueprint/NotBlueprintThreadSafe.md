---
title: "NotBlueprintThreadSafe"
id: "meta.NotBlueprintThreadSafe"
kind: "meta"
symbol: "NotBlueprintThreadSafe"
category: "Blueprint"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "用在函数上，标记这个函数是不线程安全的"
usage: "UFUNCTION"
---

# NotBlueprintThreadSafe

- **功能描述：** 用在函数上，标记这个函数是不线程安全的
- **使用位置：** UFUNCTION
- **元数据类型：** bool
- **关联项：** [BlueprintThreadSafe](BlueprintThreadSafe.md)
- **常用程度：** ★

## 行为

UE5.8 function metadata；BlueprintGraph `MD_NotThreadSafe`，作为 BlueprintThreadSafe 类级规则的函数例外。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `ObjectMacros.h` metadata declaration/comment
  - UE5.8 `BlueprintGraph` metadata constants or node usage
- 批次记录：`references/audits/ue5.8-p1-complete-pass.md`。

## 常见误用

参数名、属性名或目标宏写错导致 metadata 被保留但没有对应编辑器/Blueprint 行为。
