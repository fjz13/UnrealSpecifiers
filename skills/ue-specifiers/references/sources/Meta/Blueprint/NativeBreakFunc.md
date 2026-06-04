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

- **功能描述：** 指定一个函数采用BreakStruct的图标。
- **使用位置：** UFUNCTION
- **元数据类型：** bool
- **关联项：** [NativeMakeFunc](NativeMakeFunc/NativeMakeFunc.md)
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
- 批次记录：`references/audits/ue5.8-p1-complete-pass.md`。

## 常见误用

和 struct metadata `HasNativeMake/HasNativeBreak` 混淆；函数侧 NativeMakeFunc/NativeBreakFunc 是 K2 函数表现形式标记。
