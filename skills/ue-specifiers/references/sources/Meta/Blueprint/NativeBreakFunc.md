---
title: "NativeBreakFunc"
id: "meta.NativeBreakFunc"
kind: "meta"
symbol: "NativeBreakFunc"
category: "Blueprint"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定一个函数采用BreakStruct的图标"
usage: "UFUNCTION"
---

# NativeBreakFunc

## Decision Summary

- **Use when:** `NativeBreakFunc` metadata 的 `UFUNCTION` 场景需要：指定一个函数采用BreakStruct的图标。
- **Do not use when:** 目标声明不属于 `UFUNCTION`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** 函数签名和行为应符合 Break 节点语义；该 metadata 主要改变 Blueprint Break-style 节点展示，不自动验证拆分正确性。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 指定一个函数采用BreakStruct的图标。
- **使用位置：** UFUNCTION
- **元数据类型：** bool
- **关联项：** [NativeMakeFunc](NativeMakeFunc.md)
- **常用程度：** ★

其功能在NativeMakeFunc里已经说明

## 行为

UE5.8 function metadata；BlueprintGraph/K2Node_CallFunction 读取 `NativeBreakFunc`，使函数表现为 native break struct。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `ObjectMacros.h` metadata declaration/comment
  - UE5.8 `BlueprintGraph` metadata constants or node usage

## 常见误用

和 struct metadata `HasNativeMake/HasNativeBreak` 混淆；函数侧 NativeMakeFunc/NativeBreakFunc 是 K2 函数表现形式标记。
