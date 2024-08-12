# NetMulticast

Description: 此函数将在服务器上本地执行，也将复制到所有客户端上，无论该Actor的 NetOwner 为何。网络间广播。
Type: bool
Feature: Network
Status: Done
+=EFunctionFlags: FUNC_Net (../../Flags/EFunctionFlags/FUNC_Net.md), FUNC_NetMulticast (../../Flags/EFunctionFlags/FUNC_NetMulticast.md)

定义一个多播RPC函数在服务器和客户端上都执行。对应的实现函数会添加_Implementation后缀

RPC执行的规则，参考文档：[https://docs.unrealengine.com/4.27/zh-CN/InteractiveExperiences/Networking/Actors/RPCs/](https://docs.unrealengine.com/4.27/zh-CN/InteractiveExperiences/Networking/Actors/RPCs/)

![Untitled](Client/Untitled.png)

测试代码：

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

![Untitled](NetMulticast/Untitled.png)

测试输出结果：

```cpp
LogInsider: Display: 46715a00    MyFunc_NetMulticast_Implementation  BP_Network_C_1  NM_ListenServer Local:ROLE_Authority    Remote:ROLE_SimulatedProxy
LogInsider: Display: 46e65000    MyFunc_NetMulticast_Implementation  BP_Network_C_1  NM_Client   Local:ROLE_SimulatedProxy   Remote:ROLE_Authority
LogInsider: Display: 29aaaa00    MyFunc_NetMulticast_Implementation  BP_Network_C_1  NM_Client   Local:ROLE_SimulatedProxy   Remote:ROLE_Authority

LogInsider: Display: 4ff44600    OtherMulticastFunc  BP_Network_C_1  NM_ListenServer Local:ROLE_Authority    Remote:ROLE_SimulatedProxy
LogInsider: Display: 3bf89b00    OtherMulticastFunc  BP_Network_C_1  NM_Client   Local:ROLE_SimulatedProxy   Remote:ROLE_Authority
LogInsider: Display: 29d68700    OtherMulticastFunc  BP_Network_C_1  NM_Client   Local:ROLE_SimulatedProxy   Remote:ROLE_Authority
```

在一个Server Owned的Actor上，发出Multicast RPC事件调用，可以见到在3个端都得到了调用。