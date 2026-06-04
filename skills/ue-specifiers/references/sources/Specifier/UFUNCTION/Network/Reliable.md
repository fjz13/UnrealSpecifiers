---
title: "Reliable"
id: "UFUNCTION.Reliable"
kind: "specifier"
symbol: "Reliable"
scope: "UFUNCTION"
category: "Network"
source_status: "imported_from_unreal_specifiers"
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
- **作用机制：** 在FunctionFlags加入[FUNC_NetReliable](../../../Flags/EFunctionFlags/FUNC_NetReliable.md)
- **常用程度：★★★★★**

指定一个RPC函数为“可靠的”，当遇见网络错误时会重发以保证到达。一般用在逻辑关键的函数上。

具体的原理涉及到了重发信息包的逻辑。