---
title: "BlueprintCosmetic"
id: "UFUNCTION.BlueprintCosmetic"
kind: "specifier"
symbol: "BlueprintCosmetic"
scope: "UFUNCTION"
category: "Network"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "此函数为修饰性的，无法在DS上运行"
usage: "UFUNCTION / Network"
---

# BlueprintCosmetic

## Decision Summary

- **Use when:** `BlueprintCosmetic` specifier 的 `UFUNCTION / Network` 场景需要：此函数为修饰性的，无法在DS上运行。
- **Do not use when:** 声明宏、目标类型或代码契约不属于 `UFUNCTION / Network`。
- **Requires:** specifier 必须放在 UE5.8 UHT 支持的宏和声明位置，并满足正文 caveat。
- **Conflicts:** 不要和同类互斥 specifier 或语义相反的暴露/持久化/网络规则混用。
- **Prefer instead:** 能用更窄暴露范围或更明确 metadata 表达时，优先选择更窄方案。

- **功能描述：** 此函数为修饰性的，无法在DS上运行。

- **元数据类型：** bool
- **引擎模块：** Network
- **作用机制：** 在FunctionFlags中加入FUNC_BlueprintCosmetic
- **常用程度：** ★★★

这个函数是修饰性的，所谓修饰性是指这个函数的内容是为了展现一些与逻辑无关的内容，比如动画音效特效等。因为DS并没有实际的画面输出，因此这些修饰性的函数是对DS无意义的。因此这些修饰性函数会被无视掉。

但是也注意在ListenServer或Client上，这二者都会允许运行。因为这两个端都需要画面展示。

## 测试代码：

```cpp
UFUNCTION(BlueprintCallable, BlueprintCosmetic)
void MyFunc_BlueprintCosmetic();
```

## 测试蓝图：

节点上的电脑标记就是意味着只在客户端上运行。


结果输出

```cpp
MyFunc_BlueprintCosmetic    BP_Network_C_1  NM_ListenServer Local:ROLE_Authority    Remote:ROLE_SimulatedProxy
MyFunc_BlueprintCosmetic    BP_Network_C_1  NM_Client   Local:ROLE_SimulatedProxy   Remote:ROLE_Authority
MyFunc_BlueprintCosmetic    BP_Network_C_1  NM_Client   Local:ROLE_SimulatedProxy   Remote:ROLE_Authority
```

## 原理：

```cpp
int32 AActor::GetFunctionCallspace( UFunction* Function, FFrame* Stack )
{
// Dedicated servers don't care about "cosmetic" functions.
if (NetMode == NM_DedicatedServer && Function->HasAllFunctionFlags(FUNC_BlueprintCosmetic))
{
	DEBUG_CALLSPACE(TEXT("GetFunctionCallspace Blueprint Cosmetic Absorbed: %s"), *Function->GetName());
	return FunctionCallspace::Absorbed;
}
}
```

## 行为

在 UE5.8 UHT 中写入 `FUNC_BlueprintCosmetic`，用于标记 cosmetic Blueprint 函数。它不是网络发送标志，不能替代 `Client`/`NetMulticast`。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtFunctionSpecifiers.cs` 对应 specifier 分支
  - UE5.8 `UhtFunction.cs` replicated/event 校验

## 常见误用

把 cosmetic 限制和 RPC 方向混用；或在 dedicated server 关键逻辑里依赖 cosmetic 函数执行。
