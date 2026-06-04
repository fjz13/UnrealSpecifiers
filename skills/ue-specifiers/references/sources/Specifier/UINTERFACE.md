---
title: "UINTERFACE(标识符)"
id: "UINTERFACE.UINTERFACE(标识符)"
kind: "specifier"
symbol: "UINTERFACE(标识符)"
scope: "UINTERFACE"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "UE5.8 UHT 通过 UhtInterfaceClassParser 识别 UINTERFACE，创建 interface class 并使用 UhtTableNames.Interface 的 keyword/specifier ta"
usage: "UINTERFACE"
---

# UINTERFACE(标识符)

## DllExport

| Name                                                         | 引擎模块  | 功能描述                                                | 常用程度 |
| ------------------------------------------------------------ | --------- | ------------------------------------------------------- | -------- |
| [MinimalAPI](UINTERFACE/UHT/MinimalAPI.md)                   | DllExport | 指定该UInterface对象不导出到别的模块                    | ★        |


## Blueprint

| Name                                                         | 引擎模块  | 功能描述                                                | 常用程度 |
| ------------------------------------------------------------ | --------- | ------------------------------------------------------- | -------- |
| [Blueprintable](UINTERFACE/Blueprint/Blueprintable.md) | Blueprint | 可以在蓝图中实现                                        | ★★★★★    |
| [NotBlueprintable](UINTERFACE/Blueprint/NotBlueprintable.md) | Blueprint | 指定不可以在蓝图中实现                                  | ★★★      |
| [ConversionRoot](UINTERFACE/UHT/ConversionRoot.md)           | Blueprint | Sets IsConversionRoot metadata flag for this interface. | 💀        |

## 行为

UE5.8 UHT 通过 `UhtInterfaceClassParser` 识别 `UINTERFACE`，创建 interface class 并使用 `UhtTableNames.Interface` 的 keyword/specifier table 解析 specifier。该页是 UINTERFACE 条目索引，不是单个 specifier。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtInterfaceClassParser.cs` routes `UINTERFACE` to interface specifier table
  - UE5.8 `UhtTables.cs` creates the `Interface` keyword/specifier table

## 常见误用

把总览页当成 specifier；具体行为应跳转到 `Blueprintable`、`NotBlueprintable` 或 interface/class 相关条目。
