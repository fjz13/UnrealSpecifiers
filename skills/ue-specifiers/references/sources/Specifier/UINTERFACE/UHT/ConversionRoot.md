---
title: "ConversionRoot"
id: "UINTERFACE.ConversionRoot"
kind: "specifier"
symbol: "ConversionRoot"
scope: "UINTERFACE"
category: "UHT"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "Sets IsConversionRoot metadata flag for this interface."
usage: "UINTERFACE / UHT"
---

# ConversionRoot

## Decision Summary

- **Use when:** `ConversionRoot` specifier 的 `UINTERFACE / UHT` 场景需要：Sets IsConversionRoot metadata flag for this interface.。
- **Do not use when:** 声明宏、目标类型或代码契约不属于 `UINTERFACE / UHT`。
- **Requires:** specifier 必须放在 UE5.8 UHT 支持的宏和声明位置，并满足正文 caveat。
- **Conflicts:** 不要和同类互斥 specifier 或语义相反的暴露/持久化/网络规则混用。
- **Prefer instead:** 能用更窄暴露范围或更明确 metadata 表达时，优先选择更窄方案。

- **功能描述：**  Sets IsConversionRoot metadata flag for this interface.
- **元数据类型：** bool
- **引擎模块：** Blueprint
- **作用机制：** 在Meta中加入[IsConversionRoot](../../../Meta/Blueprint/IsConversionRoot.md)

在源码中并不能找到该使用示例
## UE5.8 审计结论

UE5.8 UHT 或宏路径仍保留该条目；本轮按 UE5.8 标记为已验证。P3 中不少条目属于引擎内部、NoExportTypes 或插件专用用法，不建议普通项目代码直接套用。
