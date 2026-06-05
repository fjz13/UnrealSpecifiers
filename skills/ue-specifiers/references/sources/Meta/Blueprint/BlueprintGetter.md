---
title: "BlueprintGetter"
id: "meta.BlueprintGetter"
kind: "meta"
symbol: "BlueprintGetter"
category: "Blueprint"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "采用一个自定义的get函数来读取"
usage: "UFUNCTION, UPROPERTY"
---

# BlueprintGetter

## Decision Summary

- **Use when:** `BlueprintGetter` metadata 的 `UFUNCTION, UPROPERTY` 场景需要：采用一个自定义的get函数来读取。
- **Do not use when:** 目标声明不属于 `UFUNCTION, UPROPERTY`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 采用一个自定义的get函数来读取。
  如果没有设置BlueprintSetter或BlueprintReadWrite, 则会默认设置BlueprintReadOnly.

- **使用位置：** UFUNCTION, UPROPERTY

- **引擎模块：** Blueprint

- **元数据类型：** string="abc"

- **关联项：**

  UFUNCTION：[BlueprintGetter](../../Specifier/UFUNCTION/Blueprint/BlueprintGetter.md)

  UPROPERTY：[BlueprintGetter](../../Specifier/UPROPERTY/Blueprint/BlueprintGetter.md)

- **常用程度：** ★★★

## 行为

UE5.8 property metadata；BlueprintGraph/UHT property accessor metadata，指定 getter function。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `ObjectMacros.h` metadata declaration/comment
  - UE5.8 `BlueprintGraph` metadata constants or node usage

## 常见误用

参数名、属性名或目标宏写错导致 metadata 被保留但没有对应编辑器/Blueprint 行为。
