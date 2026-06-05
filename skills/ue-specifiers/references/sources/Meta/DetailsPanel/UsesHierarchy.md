---
title: "UsesHierarchy"
id: "meta.UsesHierarchy"
kind: "meta"
symbol: "UsesHierarchy"
category: "DetailsPanel"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "说明类使用层级数据。用于实例化“细节”面板中的层级编辑功能"
usage: "UCLASS"
---

# UsesHierarchy

## Decision Summary

- **Use when:** `UsesHierarchy` metadata 的 `UCLASS` 场景需要：说明类使用层级数据。用于实例化“细节”面板中的层级编辑功能。
- **Do not use when:** 目标声明不属于 `UCLASS`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 说明类使用层级数据。用于实例化“细节”面板中的层级编辑功能。
- **使用位置：** UCLASS
- **引擎模块：** DetailsPanel
- **元数据类型：** bool
- **常用程度：** 0

## 行为

UE5.8 class metadata；ObjectMacros 标为 class metadata，用于 Details 层级编辑功能。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `ObjectMacros.h` property/class metadata declaration/comment
  - UE5.8 `PropertyEditor` Details metadata usage

## 常见误用

参数名、属性名或目标宏写错导致 metadata 被保留但没有对应编辑器/Blueprint 行为。
