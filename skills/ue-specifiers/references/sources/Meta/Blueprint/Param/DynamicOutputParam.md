---
title: "DynamicOutputParam"
id: "meta.DynamicOutputParam"
kind: "meta"
symbol: "DynamicOutputParam"
category: "Blueprint"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "配合DeterminesOutputType，指定多个支持动态类型的输出参数"
usage: "UFUNCTION"
---

# DynamicOutputParam

## Decision Summary

- **Use when:** `DynamicOutputParam` metadata 的 `UFUNCTION` 场景需要：配合DeterminesOutputType，指定多个支持动态类型的输出参数。
- **Do not use when:** 目标声明不属于 `UFUNCTION`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** 与 `DeterminesOutputType` 配合使用，值必须指向实际输出参数；只动态调整返回值时通常可省略。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 配合DeterminesOutputType，指定多个支持动态类型的输出参数。
- **使用位置：** UFUNCTION
- **元数据类型：** strings="a，b，c"
- **限制类型：** Class或Object指针类型，或容器类型
- **关联项：** [DeterminesOutputType](DeterminesOutputType.md)

常常和DeterminesOutputType一起配合。动态参数的数量可以为多个。

## 行为

UE5.8 function/interface metadata；BlueprintGraph `MD_DynamicOutputParam`，指定受动态类型控制的输出参数。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `ObjectMacros.h` metadata declaration/comment
  - UE5.8 `BlueprintGraph` metadata constants or node usage

## 常见误用

参数名、属性名或目标宏写错导致 metadata 被保留但没有对应编辑器/Blueprint 行为。
