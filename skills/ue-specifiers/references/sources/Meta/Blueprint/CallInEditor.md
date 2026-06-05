---
title: "CallInEditor"
id: "meta.CallInEditor"
kind: "meta"
symbol: "CallInEditor"
category: "Blueprint"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "可以在Actor的细节面板上作为一个按钮来调用该函数"
usage: "UFUNCTION"
---

# CallInEditor

## Decision Summary

- **Use when:** UFUNCTION 需要在 editor Details Panel 中以按钮形式调用。
- **Do not use when:** 函数是运行时 gameplay 调用点或需要复杂参数输入。
- **Requires:** 函数副作用必须适合编辑器环境。
- **Conflicts:** 与普通运行时 `BlueprintCallable` 语义不同。
- **Prefer instead:** 复杂编辑器工作流用 Editor Utility 或专门编辑器工具。

- **功能描述：** 可以在Actor的细节面板上作为一个按钮来调用该函数。

- **使用位置：** UFUNCTION

- **引擎模块：** Blueprint

- **元数据类型：** bool

- **关联项：**

  UFUNCTION：[CallInEditor](../../Specifier/UFUNCTION/Blueprint/CallInEditor.md)

- **常用程度：** ★★★★★

## 行为

UE5.8 function metadata；UHT 默认 specifier 写入 `CallInEditor`，Details/Blueprint 路径用于编辑器按钮/调用。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `ObjectMacros.h` metadata declaration/comment
  - UE5.8 `BlueprintGraph` metadata constants or node usage

## 常见误用

参数名、属性名或目标宏写错导致 metadata 被保留但没有对应编辑器/Blueprint 行为。
