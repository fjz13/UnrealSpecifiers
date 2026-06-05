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

## Decision Summary

- **Use when:** bool 结果/参数应在 Blueprint 节点上展开为执行引脚分支。
- **Do not use when:** bool 只是普通数据输出或调用方应自行分支。
- **Requires:** 指向实际 bool 参数/返回语义，并确认节点形态清晰。
- **Conflicts:** 不改变函数执行逻辑，只改变 Blueprint 节点呈现。
- **Prefer instead:** 简单结果用普通 bool 返回并让调用方 Branch。

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
