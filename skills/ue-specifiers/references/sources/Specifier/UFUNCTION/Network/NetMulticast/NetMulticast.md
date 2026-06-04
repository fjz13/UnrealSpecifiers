---
title: "NetMulticast"
id: "UFUNCTION.NetMulticast"
kind: "specifier"
symbol: "NetMulticast"
scope: "UFUNCTION"
category: "Network"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "定义一个多播RPC函数在服务器和客户端上都执行。对应的实现函数会添加_Implementation后缀"
usage: "UFUNCTION / Network"
---

# NetMulticast

- **功能描述：** 定义一个多播RPC函数在服务器和客户端上都执行。对应的实现函数会添加_Implementation后缀。

- **元数据类型：** bool
- **引擎模块：** Network
- **作用机制：** 在FunctionFlags中加入FUNC_Net、FUNC_NetMulticast
- **常用程度：★★★★★**

定义一个多播RPC函数在服务器和客户端上都执行。对应的实现函数会添加_Implementation后缀。

RPC执行的规则，参考文档：[https://docs.unrealengine.com/4.27/zh-CN/InteractiveExperiences/Networking/Actors/RPCs/](https://docs.unrealengine.com/4.27/zh-CN/InteractiveExperiences/Networking/Actors/RPCs/)


## 测试代码：

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyFunction_Network :public AActor
{
public:
	GENERATED_BODY()

public:
		UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void MyFunc_NetMulticast();
};

void AMyFunction_Network::MyFunc_NetMulticast_Implementation()
{
	UInsiderLibrary::PrintFuncStatus(this, TEXT("MyFunc_NetMulticast_Implementation"));
}
```

测试蓝图：PIE模式，一个ListenServer+2Client


## 测试输出结果：

```cpp
LogInsider: Display: 46715a00    MyFunc_NetMulticast_Implementation  BP_Network_C_1  NM_ListenServer Local:ROLE_Authority    Remote:ROLE_SimulatedProxy
LogInsider: Display: 46e65000    MyFunc_NetMulticast_Implementation  BP_Network_C_1  NM_Client   Local:ROLE_SimulatedProxy   Remote:ROLE_Authority
LogInsider: Display: 29aaaa00    MyFunc_NetMulticast_Implementation  BP_Network_C_1  NM_Client   Local:ROLE_SimulatedProxy   Remote:ROLE_Authority

LogInsider: Display: 4ff44600    OtherMulticastFunc  BP_Network_C_1  NM_ListenServer Local:ROLE_Authority    Remote:ROLE_SimulatedProxy
LogInsider: Display: 3bf89b00    OtherMulticastFunc  BP_Network_C_1  NM_Client   Local:ROLE_SimulatedProxy   Remote:ROLE_Authority
LogInsider: Display: 29d68700    OtherMulticastFunc  BP_Network_C_1  NM_Client   Local:ROLE_SimulatedProxy   Remote:ROLE_Authority
```

在一个Server Owned的Actor上，发出Multicast RPC事件调用，可以见到在3个端都得到了调用。

## 行为

在 UE5.8 UHT 中写入 `FUNC_Net | FUNC_NetMulticast`。UHT 拒绝与 Blueprint event 组合。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtFunctionSpecifiers.cs` 对应 specifier 分支
  - UE5.8 `UhtFunction.cs` replicated/event 校验
  - 本地样例辅助对照：`D:/github/GitWorkspace/Hello/Source/Insider/Function/MyFunction_Network.h`。

## 常见误用

以为客户端调用 multicast 会广播给所有端；或漏写 `Reliable`/`Unreliable`。
