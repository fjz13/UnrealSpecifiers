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
