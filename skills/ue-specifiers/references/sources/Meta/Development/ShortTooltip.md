---
title: "ShortTooltip"
id: "meta.ShortTooltip"
kind: "meta"
symbol: "ShortTooltip"
category: "Development"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "提供一个更简洁版本的提示文本，例如在类型选择器的时候显示"
usage: "Any"
---

# ShortTooltip

- **功能描述：** 提供一个更简洁版本的提示文本，例如在类型选择器的时候显示
- **使用位置：** Any
- **元数据类型：** string="abc"
- **关联项：** [ToolTip](ToolTip/ToolTip.md)

## 行为

UE5.8 UHT 的 tooltip 查询在请求 short tooltip 时优先读取 `ShortToolTip`，没有时回退到 `ToolTip`。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtType.cs` short tooltip fallback path

## 常见误用

大小写写成不被读取的键；或以为它会替代所有 Details/Blueprint UI 的长 tooltip。
