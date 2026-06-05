---
title: "CannotImplementInterfaceInBlueprint"
id: "meta.CannotImplementInterfaceInBlueprint"
kind: "meta"
symbol: "CannotImplementInterfaceInBlueprint"
category: "Blueprint"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定该接口不能在蓝图中实现"
usage: "Blueprint"
---

# CannotImplementInterfaceInBlueprint

## Decision Summary

- **Use when:** `CannotImplementInterfaceInBlueprint` metadata 的 `Blueprint` 场景需要：指定该接口不能在蓝图中实现。
- **Do not use when:** 目标声明不属于 `Blueprint`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 指定该接口不能在蓝图中实现

- **引擎模块：** Blueprint

- **元数据类型：** bool

- **关联项：**

  UINTERFACE：[NotBlueprintable](../../Specifier/UINTERFACE/Blueprint/NotBlueprintable.md)

- **常用程度：** ★★★

和UINTERFACE(NotBlueprintable)的效果一样，指定不能在蓝图中继承

## 行为

UE5.8 interface metadata；ObjectMacros 标注等价于 NotBlueprintable，用于接口不能由 Blueprint 实现。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `ObjectMacros.h` metadata declaration/comment
  - UE5.8 `BlueprintGraph` metadata constants or node usage

## 常见误用

参数名、属性名或目标宏写错导致 metadata 被保留但没有对应编辑器/Blueprint 行为。
