---
title: "Native"
id: "UPROPERTY.Native"
kind: "specifier"
symbol: "Native"
scope: "UPROPERTY"
category: "UHT"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "属性为本地：C++代码负责对其进行序列化并公开到垃圾回收"
usage: "UPROPERTY / UHT"
---

# Native

## Decision Summary

- **Use when:** `Native` specifier 的 `UPROPERTY / UHT` 场景需要：属性为本地：C++代码负责对其进行序列化并公开到垃圾回收。
- **Do not use when:** 声明宏、目标类型或代码契约不属于 `UPROPERTY / UHT`。
- **Requires:** specifier 必须放在 UE5.8 UHT 支持的宏和声明位置，并满足正文 caveat。
- **Conflicts:** 不要和同类互斥 specifier 或语义相反的暴露/持久化/网络规则混用。
- **Prefer instead:** 能用更窄暴露范围或更明确 metadata 表达时，优先选择更窄方案。

- **功能描述：** 属性为本地：C++代码负责对其进行序列化并公开到垃圾回收 。
- **元数据类型：** bool
- **引擎模块：** Behavior

已被删除
## UE5.8 审计结论

UE5.8 UHT 或宏路径仍保留该条目；本轮按 UE5.8 标记为已验证。P3 中不少条目属于引擎内部、NoExportTypes 或插件专用用法，不建议普通项目代码直接套用。
