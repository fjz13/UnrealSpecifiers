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

## Decision Summary

- **Use when:** `UPARAM(标识符)` specifier 的 `UPARAM` 场景需要：UE5.8 UHT 在解析 property argument 时遇到 UPARAM 会切换到 property argument specifier table。该页是 UPARAM 条目索引，不是单个 specifier。
- **Do not use when:** 声明宏、目标类型或代码契约不属于 `UPARAM`。
- **Requires:** specifier 必须放在 UE5.8 UHT 支持的宏和声明位置，并满足正文 caveat。
- **Conflicts:** 不要和同类互斥 specifier 或语义相反的暴露/持久化/网络规则混用。
- **Prefer instead:** 能用更窄暴露范围或更明确 metadata 表达时，优先选择更窄方案。

 ## Blueprint

| Name                                                       | 功能描述                             | 引擎模块                      | 常用程度 |
| ---------------------------------------------------------- | ------------------------------------ | ----------------------------- | -------- |
| [DisplayName](UPARAM/Blueprint/DisplayName.md) | 更改函数参数在蓝图节点上的显示名字   | Blueprint, Parameter          | ★★★★★    |
| [ref](UPARAM/Blueprint/ref.md)                         | 使得函数的参数变成引用类型           | Blueprint, Parameter          | ★★★★★    |
| [Const](UPARAM/Blueprint/Const.md)                   | 指定该函数参数不可更改               | Blueprint, Parameter          | ★        |
| [Required](UPARAM/Blueprint/Required.md)          | 指定函数的参数节点必须连接提供一个值 | Blueprint, Parameter          | ★★       |


 ## Network

| Name                                                       | 功能描述                             | 引擎模块                      | 常用程度 |
| ---------------------------------------------------------- | ------------------------------------ | ----------------------------- | -------- |
| [NotReplicated](UPARAM/NotReplicated.md)           |                                      | Blueprint, Network, Parameter | 💀        |

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
