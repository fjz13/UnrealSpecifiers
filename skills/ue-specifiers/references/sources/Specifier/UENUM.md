---
title: "UENUM(标识符)"
id: "UENUM.UENUM(标识符)"
kind: "specifier"
symbol: "UENUM(标识符)"
scope: "UENUM"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "UE5.8 UHT 通过 UhtEnumParser 识别 UENUM，创建 enum 类型并使用 UhtTableNames.Enum 的 keyword/specifier table 解析枚举 specifier。该页是 UENUM "
usage: "UENUM"
---

# UENUM(标识符)

 ## Trait

| Name                                    | 引擎模块  | 功能描述                                   | 常用程度 |
| --------------------------------------- | --------- | ------------------------------------------ | -------- |
| [Flags](UENUM/Flags/Flags.md)           | Trait     | 把该枚举的值作为一个标志来拼接字符串输出。 | ★★★★★    |


 ## Blueprint

| Name                                    | 引擎模块  | 功能描述                                   | 常用程度 |
| --------------------------------------- | --------- | ------------------------------------------ | -------- |
| [BlueprintType](UENUM/BlueprintType.md) | Blueprint | 可以作为蓝图变量                           | ★★★★★    |

## 行为

UE5.8 UHT 通过 `UhtEnumParser` 识别 `UENUM`，创建 enum 类型并使用 `UhtTableNames.Enum` 的 keyword/specifier table 解析枚举 specifier。该页是 UENUM 条目索引，不是单个 specifier。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtEnumParser.cs` `UENUMKeyword`
  - UE5.8 `UhtTables.cs` creates the `Enum` keyword/specifier table
- 批次记录：`references/audits/ue5.8-p1-macro-param-struct-enum-pass.md`。

## 常见误用

把总览页当成可直接填写的 specifier；具体行为应跳转到 `BlueprintType`、`Flags` 或对应 metadata 条目。
