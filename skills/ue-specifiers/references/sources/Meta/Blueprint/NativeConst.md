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

## Decision Summary

- **Use when:** `NativeConst` metadata 的 `UPARAM` 场景需要：指定有C++里的const标志。
- **Do not use when:** 目标声明不属于 `UPARAM`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 指定有C++里的const标志

- **使用位置：** UPARAM

- **引擎模块：** Blueprint

- **元数据类型：** bool

- **关联项：**

  UPARAM：[Const](../../Specifier/UPARAM/Blueprint/Const.md)

- **常用程度：** ★

## 行为

UE5.8 parameter metadata；UHT/Blueprint 生成参数时用于 native const 语义。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `ObjectMacros.h` metadata declaration/comment
  - UE5.8 `BlueprintGraph` metadata constants or node usage

## 常见误用

手写内部/生成型 metadata 并期待替代正确的 C++ 函数签名或默认参数。
