---
title: "Localized"
id: "UPROPERTY.Localized"
kind: "specifier"
symbol: "Localized"
scope: "UPROPERTY"
category: "Asset"
source_status: "removed_or_deprecated"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "UE5.8 中已废弃。UHT 遇到 Localized 会记录 deprecated 错误，不应再作为可推荐的 UPROPERTY specifier 使用"
usage: "UPROPERTY / Asset"
---

# Localized

- **功能描述：** UE5.8 中已废弃。UHT 遇到 `Localized` 会记录 deprecated 错误，不应再作为可推荐的 UPROPERTY specifier 使用。
- **元数据类型：** bool
- **引擎模块：** Behavior
- **限制类型：** FString

## 行为

UE5.8 UHT 的 `Localized` property specifier 分支直接记录 deprecated 错误，不再作为可推荐的 UPROPERTY specifier。

## UE5.8 审计结论

- 状态：`removed_or_deprecated`。
- 结论：UE5.8 下已标记为废弃/不可推荐。
- 证据：
  - UE5.8 `UhtPropertyMemberSpecifiers.cs` `LocalizedSpecifier` logs deprecated error
- 批次记录：`references/audits/ue5.8-p1-macro-param-struct-enum-pass.md`。

## 常见误用

继续照旧资料在 FString 上写 `Localized`；UE5.8 下应移除并使用当前本地化/文本资源工作流。
