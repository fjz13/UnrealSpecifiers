---
title: "RepRetry"
id: "UPROPERTY.RepRetry"
kind: "specifier"
symbol: "RepRetry"
scope: "UPROPERTY"
category: "Network"
source_status: "removed_or_deprecated"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "UE5.8 中已废弃。UHT 遇到 RepRetry 会记录 deprecated 错误，不应再作为可推荐的 UPROPERTY specifier 使用"
usage: "UPROPERTY / Network"
---

# RepRetry

## Decision Summary

- **Use when:** 迁移、诊断或阅读旧代码时需要识别 `RepRetry`。
- **Do not use when:** 不要在新的 UE5.8 代码中把它作为常规方案。
- **Requires:** 确认目标代码确实依赖旧版本或兼容路径，并阅读正文的版本说明。
- **Conflicts:** 与当前 UE5.8 推荐写法冲突时，以当前引擎行为为准。
- **Prefer instead:** 新代码优先使用正文或索引中指向的当前替代项。

- **功能描述：** UE5.8 中已废弃。UHT 遇到 `RepRetry` 会记录 deprecated 错误，不应再作为可推荐的 UPROPERTY specifier 使用。
- **元数据类型：** bool
- **引擎模块：** Network

## 行为

UE5.8 UHT 中 `RepRetry` specifier 直接记录 deprecated 错误，不再作为可推荐的 UPROPERTY specifier。旧资料中关于结构体属性复制失败后重试的说明只适合历史背景参考。

## UE5.8 审计结论

- 状态：`removed_or_deprecated`。
- 结论：UE5.8 下已标记为废弃/不可推荐。
- 证据：
  - UE5.8 `UhtPropertyMemberSpecifiers.cs` 对应 specifier 分支
  - 本地样例辅助对照：`D:/github/GitWorkspace/Hello/Source/Insider/Property/Network/MyProperty_Network.h 中保留 deprecated 注释样例`。

## 常见误用

继续照 UE4/旧文档写 `RepRetry`；UE5.8 下应移除并重新评估结构体复制设计。
