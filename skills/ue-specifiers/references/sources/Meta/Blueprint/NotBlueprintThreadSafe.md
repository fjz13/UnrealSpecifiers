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

## Decision Summary

- **Use when:** `NotBlueprintThreadSafe` metadata 的 `UFUNCTION` 场景需要：用在函数上，标记这个函数是不线程安全的。
- **Do not use when:** 目标声明不属于 `UFUNCTION`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** 用于从 class-level `BlueprintThreadSafe` 默认值中排除特定函数；该函数仍应避免被误路由到线程安全调用路径。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

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

## 常见误用

参数名、属性名或目标宏写错导致 metadata 被保留但没有对应编辑器/Blueprint 行为。
