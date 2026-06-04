---
title: "UIMax"
id: "meta.UIMax"
kind: "meta"
symbol: "UIMax"
category: "Numeric"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定数字输入框上滚动条拖动的最大范围值"
usage: "UPROPERTY"
---

# UIMax

- **功能描述：** 指定数字输入框上滚动条拖动的最大范围值
- **使用位置：** UPROPERTY
- **引擎模块：** Numeric Property
- **元数据类型：** float/int
- **限制类型：** float,int32
- **关联项：** [UIMin](UIMin.md)
- **常用程度：** ★★★★★

## 行为

UE5.8 UHT 对 `UIMax` 执行 numeric validator，并在文档策略中检查 `UIMin/UIMax` 范围。它主要是 UI 范围，不等同于 hard clamp。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 UHT metadata validator/parser
  - UE5.8 BlueprintGraph 或 PropertyEditor metadata 读取路径

## 常见误用

用 `UIMax` 当作强制最大值；或填非数字字符串。
