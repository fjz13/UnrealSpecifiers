---
title: "UPARAM(标识符)"
id: "UPARAM.UPARAM(标识符)"
kind: "specifier"
symbol: "UPARAM(标识符)"
scope: "UPARAM"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "UE5.8 UHT 在解析 property argument 时遇到 UPARAM 会切换到 property argument specifier table。该页是 UPARAM 条目索引，不是单个 specifier"
usage: "UPARAM"
---

# UPARAM(标识符)

 ## Blueprint

| Name                                                       | 功能描述                             | 引擎模块                      | 常用程度 |
| ---------------------------------------------------------- | ------------------------------------ | ----------------------------- | -------- |
| [DisplayName](UPARAM/Blueprint/DisplayName/DisplayName.md) | 更改函数参数在蓝图节点上的显示名字   | Blueprint, Parameter          | ★★★★★    |
| [ref](UPARAM/Blueprint/ref/ref.md)                         | 使得函数的参数变成引用类型           | Blueprint, Parameter          | ★★★★★    |
| [Const](UPARAM/Blueprint/Const/Const.md)                   | 指定该函数参数不可更改               | Blueprint, Parameter          | ★        |
| [Required](UPARAM/Blueprint/Required/Required.md)          | 指定函数的参数节点必须连接提供一个值 | Blueprint, Parameter          | ★★       |


 ## Network

| Name                                                       | 功能描述                             | 引擎模块                      | 常用程度 |
| ---------------------------------------------------------- | ------------------------------------ | ----------------------------- | -------- |
| [NotReplicated](UPARAM/Network/NotReplicated.md)           |                                      | Blueprint, Network, Parameter | 💀        |

## 行为

UE5.8 UHT 在解析 property argument 时遇到 `UPARAM` 会切换到 property argument specifier table。该页是 UPARAM 条目索引，不是单个 specifier。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtPropertyParser.cs` detects `UPARAM` and uses `UhtTableNames.PropertyArgument`
  - UE5.8 `UhtTables.cs` creates the property argument specifier table

## 常见误用

把总览页当成可填写 specifier；具体参数行为应跳到 `ref`、`Const`、`DisplayName`、`Required`、`NotReplicated`。
