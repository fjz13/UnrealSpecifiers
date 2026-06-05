---
title: "Unreliable"
id: "UFUNCTION.Unreliable"
kind: "specifier"
symbol: "Unreliable"
scope: "UFUNCTION"
category: "Network"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定一个RPC函数为“不可靠的”，当遇见网络错误时就会被丢弃。一般用在传播效果表现的函数上，就算漏掉也没有关系"
usage: "UFUNCTION / Network"
---

# Unreliable

## Decision Summary

- **Use when:** RPC 是高频、表现型或可被后续状态覆盖，允许丢包。
- **Do not use when:** RPC 丢失会破坏游戏状态、交易、授权或关键用户操作。
- **Requires:** 必须搭配 RPC 方向 specifier，如 `Server`、`Client` 或 `NetMulticast`。
- **Conflicts:** `Reliable`。
- **Prefer instead:** 关键低频事件用 `Reliable`；持续状态优先考虑属性复制。

- **功能描述：** 指定一个RPC函数为“不可靠的”，当遇见网络错误时就会被丢弃。一般用在传播效果表现的函数上，就算漏掉也没有关系。

- **元数据类型：** bool
- **引擎模块：** Network
- **常用程度：★★★★★**

指定一个RPC函数为“不可靠的”，当遇见网络错误时就会被丢弃。一般用在传播效果表现的函数上，就算漏掉也没有关系。

## 行为

在 UE5.8 UHT 中写入 `Unreliable` export flag；`UhtFunction` 校验会和 `Reliable` 互斥，并要求只用于 replicated function。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtFunctionSpecifiers.cs` 对应 specifier 分支
  - UE5.8 `UhtFunction.cs` replicated/event 校验

## 常见误用

在非 RPC 函数上单独写 `Unreliable`；或和 `Reliable` 同时写。
