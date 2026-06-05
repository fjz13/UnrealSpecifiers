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

## Decision Summary

- **Use when:** 迁移、诊断或阅读旧代码时需要识别 `Localized`。
- **Do not use when:** 不要在新的 UE5.8 代码中把它作为常规方案。
- **Requires:** 确认目标代码确实依赖旧版本或兼容路径，并阅读正文的版本说明。
- **Conflicts:** 与当前 UE5.8 推荐写法冲突时，以当前引擎行为为准。
- **Prefer instead:** 新代码优先使用正文或索引中指向的当前替代项。

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

## 常见误用

继续照旧资料在 FString 上写 `Localized`；UE5.8 下应移除并使用当前本地化/文本资源工作流。
