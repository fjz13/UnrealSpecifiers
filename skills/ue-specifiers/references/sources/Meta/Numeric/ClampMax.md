---
title: "ClampMax"
id: "meta.ClampMax"
kind: "meta"
symbol: "ClampMax"
category: "Numeric"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定数字输入框实际接受的最大值"
usage: "UPROPERTY"
---

# ClampMax

- **功能描述：** 指定数字输入框实际接受的最大值
- **使用位置：** UPROPERTY
- **引擎模块：** Numeric Property
- **元数据类型：** float/int
- **限制类型：** float,int32
- **关联项：** [UIMin](UIMin.md)
- **常用程度：** ★★★★★

## 行为

UE5.8 UHT 对 `ClampMax` 执行 numeric validator，非数字会报错。它表达编辑/赋值约束上限，区别于 slider UI 范围。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 UHT metadata validator/parser
  - UE5.8 BlueprintGraph 或 PropertyEditor metadata 读取路径

## 常见误用

和 `UIMax` 混淆；或填非数字字符串。
