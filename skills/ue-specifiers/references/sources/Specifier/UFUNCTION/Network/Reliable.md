---
title: "Reliable"
id: "UFUNCTION.Reliable"
kind: "specifier"
symbol: "Reliable"
scope: "UFUNCTION"
category: "Network"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定一个RPC函数为“可靠的”，当遇见网络错误时会重发以保证到达。一般用在逻辑关键的函数上"
usage: "UFUNCTION / Network"
---

# Reliable

- **功能描述：** 指定一个RPC函数为“可靠的”，当遇见网络错误时会重发以保证到达。一般用在逻辑关键的函数上。

- **元数据类型：** bool
- **引擎模块：** Network
- **作用机制：** 在FunctionFlags加入FUNC_NetReliable
- **常用程度：★★★★★**

指定一个RPC函数为“可靠的”，当遇见网络错误时会重发以保证到达。一般用在逻辑关键的函数上。

具体的原理涉及到了重发信息包的逻辑。

## 行为

在 UE5.8 UHT 中写入 `FUNC_NetReliable`。`UhtFunction` 校验要求 replicated function 必须在 `Reliable` 和 `Unreliable` 中二选一，并禁止两者同时存在。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtFunctionSpecifiers.cs` 对应 specifier 分支
  - UE5.8 `UhtFunction.cs` replicated/event 校验
  - 本地样例辅助对照：`D:/github/GitWorkspace/Hello/Source/Insider/Function/MyFunction_Network.h`。
- 批次记录：`references/audits/ue5.8-p0-complete-pass.md`。

## 常见误用

在非 RPC 函数上单独写 `Reliable`；或同时写 `Reliable, Unreliable`。
