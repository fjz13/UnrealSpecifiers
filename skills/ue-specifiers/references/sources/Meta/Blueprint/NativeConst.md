---
title: "NativeConst"
id: "meta.NativeConst"
kind: "meta"
symbol: "NativeConst"
category: "Blueprint"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定有C++里的const标志"
usage: "UPARAM"
---

# NativeConst

- **功能描述：** 指定有C++里的const标志

- **使用位置：** UPARAM

- **引擎模块：** Blueprint

- **元数据类型：** bool

- **关联项：**

  UPARAM：[Const](../../Specifier/UPARAM/Blueprint/Const/Const.md)

- **常用程度：** ★

## 行为

UE5.8 parameter metadata；UHT/Blueprint 生成参数时用于 native const 语义。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `ObjectMacros.h` metadata declaration/comment
  - UE5.8 `BlueprintGraph` metadata constants or node usage
- 批次记录：`references/audits/ue5.8-p1-complete-pass.md`。

## 常见误用

手写内部/生成型 metadata 并期待替代正确的 C++ 函数签名或默认参数。
