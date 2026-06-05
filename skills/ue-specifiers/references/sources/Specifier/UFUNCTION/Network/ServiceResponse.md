---
title: "ServiceResponse"
id: "UFUNCTION.ServiceResponse"
kind: "specifier"
symbol: "ServiceResponse"
scope: "UFUNCTION"
category: "Network"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "此函数为RPC服务响应。rpc服务回复"
usage: "UFUNCTION / Network"
---

# ServiceResponse

## Decision Summary

- **Use when:** `ServiceResponse` specifier 的 `UFUNCTION / Network` 场景需要：此函数为RPC服务响应。rpc服务回复。
- **Do not use when:** 声明宏、目标类型或代码契约不属于 `UFUNCTION / Network`。
- **Requires:** specifier 必须放在 UE5.8 UHT 支持的宏和声明位置，并满足正文 caveat。
- **Conflicts:** 不要和同类互斥 specifier 或语义相反的暴露/持久化/网络规则混用。
- **Prefer instead:** 能用更窄暴露范围或更明确 metadata 表达时，优先选择更窄方案。

- **功能描述：** 此函数为RPC服务响应。rpc服务回复

- **元数据类型：** bool
- **引擎模块：** Network
- **作用机制：** 在FunctionFlags加入FUNC_Net、FUNC_Event、FUNC_NetReliable、FUNC_NetResponse

在源码里一个也没看到使用。

## 行为

在 UE5.8 UHT 中写入 `FUNC_Net | FUNC_NetReliable | FUNC_NetResponse`，并要求 endpoint name。它和 `ServiceRequest` 配套使用。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtFunctionSpecifiers.cs` 对应 specifier 分支
  - UE5.8 `UhtFunction.cs` replicated/event 校验
  - 本地样例辅助对照：`D:/github/GitWorkspace/Hello/Source/Insider/Function/MyFunction_PlayerController.h`。

## 常见误用

不写 endpoint；或在普通 Gameplay 通信里优先使用 service response。
