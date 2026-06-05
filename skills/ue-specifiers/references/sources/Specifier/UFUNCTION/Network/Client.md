---
title: "Client"
id: "UFUNCTION.Client"
kind: "specifier"
symbol: "Client"
scope: "UFUNCTION"
category: "Network"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "在Client-owned的Actor上（PlayerController或Pawn）执行一个RPC函数，只运行在客户端上。对应的实现函数会添加_Implementation后缀"
usage: "UFUNCTION / Network"
---

# Client

## Decision Summary

- **Use when:** 服务器需要在 owning client 上执行某个 RPC。
- **Do not use when:** 客户端要请求服务器，或需要广播给所有客户端。
- **Requires:** 正确的网络 owner；通常搭配 `Reliable` 或 `Unreliable` 选择可靠性。
- **Conflicts:** RPC 方向 specifier 之间互斥；不要同时写 `Server` 或 `NetMulticast`。
- **Prefer instead:** 客户端请求服务器用 `Server`；广播用 `NetMulticast`。

- **功能描述：** 在Client-owned的Actor上（PlayerController或Pawn）执行一个RPC函数，只运行在客户端上。对应的实现函数会添加_Implementation后缀。
- **元数据类型：** bool
- **引擎模块：** Network
- **作用机制：** 在FunctionFlags加入FUNC_Net、FUNC_NetClient
- **常用程度：★★★★★**

在Client-owned的Actor上（PlayerController或Pawn）执行一个RPC函数，只运行在客户端上。对应的实现函数会添加_Implementation后缀。

一般用于从Server发送一个RPC到Client。和蓝图里RunOnClient的效果一样。

所谓Client-owned，参考文档：[https://docs.unrealengine.com/4.27/zh-CN/InteractiveExperiences/Networking/Actors/RPCs/](https://docs.unrealengine.com/4.27/zh-CN/InteractiveExperiences/Networking/Actors/RPCs/)


## 测试代码：

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyFunction_PlayerController :public APlayerController
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Client, Reliable)
	void MyFunc_RunOnClient();
};

void AMyFunction_PlayerController::MyFunc_RunOnClient_Implementation()
{
	UInsiderLibrary::PrintFuncStatus(this, TEXT("MyFunc_RunOnClient_Implementation"));
}
```

测试蓝图：PIE模式，一个ListenServer+2Client


## 测试输出结果：

```cpp
MyFunc_Client_Implementation    BP_NetworkPC_C_0    NM_Client   Local:ROLE_AutonomousProxy  Remote:ROLE_Authority
OtherClientFunc BP_NetworkPC_C_0    NM_Client   Local:ROLE_AutonomousProxy  Remote:ROLE_Authority
```

可见，测试代码中取第2个PC，发出一个Run on Client的RPC调用，最终在Client上成功触发。C++定义的函数和蓝图中添加的自定义RunOnClient事件效果是等价的。

而如果这个函数在Server owned Actor上执行，则只会在运行在服务器上，不会传递到客户端。

## 行为

在 UE5.8 UHT 中写入 `FUNC_Net | FUNC_NetClient`，并允许可选 C++ implementation name。UHT 拒绝 Blueprint event/Exec 与 replicated function 的非法组合。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtFunctionSpecifiers.cs` 对应 specifier 分支
  - UE5.8 `UhtFunction.cs` replicated/event 校验
  - 本地样例辅助对照：`D:/github/GitWorkspace/Hello/Source/Insider/Function/MyFunction_PlayerController.h`。

## 常见误用

在非 client-owned Actor 上期待 RPC 到目标客户端；或漏写 `Reliable`/`Unreliable`。
