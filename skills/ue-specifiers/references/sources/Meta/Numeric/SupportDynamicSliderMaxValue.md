---
title: "SupportDynamicSliderMaxValue"
id: "meta.SupportDynamicSliderMaxValue"
kind: "meta"
symbol: "SupportDynamicSliderMaxValue"
category: "Numeric"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "支持数字输入框上滚动条的最大范围值在Alt按下时被动态改变"
usage: "UPROPERTY"
---

# SupportDynamicSliderMaxValue

## Decision Summary

- **Use when:** `SupportDynamicSliderMaxValue` metadata 的 `UPROPERTY` 场景需要：支持数字输入框上滚动条的最大范围值在Alt按下时被动态改变。
- **Do not use when:** 目标声明不属于 `UPROPERTY`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 支持数字输入框上滚动条的最大范围值在Alt按下时被动态改变
- **使用位置：** UPROPERTY
- **引擎模块：** Numeric Property
- **元数据类型：** bool
- **限制类型：** FVector4
- **关联项：** [SupportDynamicSliderMinValue](SupportDynamicSliderMinValue.md)
- **常用程度：** ★

## 行为

UE5.8 numeric metadata；numeric slider 支持运行时调整 max value。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `ObjectMacros.h` numeric property metadata declaration/comment
  - UE5.8 Details numeric/color customization metadata usage

## 常见误用

参数名、属性名或目标宏写错导致 metadata 被保留但没有对应编辑器/Blueprint 行为。
