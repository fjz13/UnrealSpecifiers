# BlueprintAuthorityOnly

- **功能描述：** 这个函数只能在拥有网络权限的端上运行。
- **元数据类型：** bool
- **引擎模块：** Network
- **作用机制：** 在FunctionFlags中添加[FUNC_BlueprintAuthorityOnly](../../../../Flags/EFunctionFlags/FUNC_BlueprintAuthorityOnly.md)
- **常用程度：** ★★★

这个函数只能在拥有网络权限的端上运行。HasAuthority::（GetLocalRole() == ROLE_Authority）。共有4种NetRole: ROLE_None（不复制），ROLE_SimulatedProxy（在客户端上模拟的代理），ROLE_AutonomousProxy（在客户端上的匿名代理，接收玩家输入），ROLE_Authority（服务器拥有权限的）。

因此BlueprintAuthorityOnly限定这个函数只能在服务器上运行，这个“服务器”可以是LS服务器，DS服务器，单机（可以看作没有客户端的服务器）。

注意在测试的时候需要把该Actor设置为Replicates。

## 测试代码：

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyFunction_Network :public AActor
{
public:
	GENERATED_BODY()
public:
	//FunctionFlags:	FUNC_Final | FUNC_Native | FUNC_Public | FUNC_BlueprintCallable
	UFUNCTION(BlueprintCallable)
	void MyFunc_Default();

	//FunctionFlags:	FUNC_Final | FUNC_BlueprintAuthorityOnly | FUNC_Native | FUNC_Public | FUNC_BlueprintCallable
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
	void MyFunc_BlueprintAuthorityOnly();

	static void PrintFuncStatus(AActor* actor,FString funcName);
};

void AMyFunction_Network::MyFunc_Default()
{
	PrintFuncStatus(this,TEXT("MyFunc_Default"));
}

void AMyFunction_Network::MyFunc_BlueprintAuthorityOnly()
{
	PrintFuncStatus(this,TEXT("MyFunc_BlueprintAuthorityOnly"));
}

void AMyFunction_Network::PrintFuncStatus(AActor* actor, FString funcName)
{
	FString actorName = actor->GetName();

	FString localRoleStr;
	UEnum::GetValueAsString(actor->GetLocalRole(), localRoleStr);

	FString remoteRoleStr;
	UEnum::GetValueAsString(actor->GetRemoteRole(), remoteRoleStr);

	FString netModeStr = Insider::NetModeToString(actor->GetNetMode());

	FString str = FString::Printf(TEXT("%s\t%s\t%s\tLocal:%s\tRemote:%s"), *funcName,*actorName, *netModeStr, *localRoleStr, *remoteRoleStr);
	GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red, str);

	UE_LOG(LogInsider, Display, TEXT("%s"), *str);
}
```

## 蓝图代码：

![Untitled](Untitled.png)

对于不Replicated的Actor：

```cpp
MyFunc_Default  BP_Network_C_1  NM_ListenServer Local:ROLE_Authority    Remote:ROLE_None
MyFunc_Default  BP_Network_C_1  NM_Client   Local:ROLE_None Remote:ROLE_Authority
MyFunc_Default  BP_Network_C_1  NM_Client   Local:ROLE_None Remote:ROLE_Authority
```

而对于Replicated的Actor，同时有1个S和两个C，运行普通的函数：

```cpp
MyFunc_Default  BP_Network_C_1  NM_ListenServer Local:ROLE_Authority    Remote:ROLE_SimulatedProxy
MyFunc_Default  BP_Network_C_1  NM_Client   Local:ROLE_SimulatedProxy   Remote:ROLE_Authority
MyFunc_Default  BP_Network_C_1  NM_Client   Local:ROLE_SimulatedProxy   Remote:ROLE_Authority
```

如果允许的BlueprintAuthorityOnly函数：

```cpp
MyFunc_BlueprintAuthorityOnly   BP_Network_C_1  NM_ListenServer Local:ROLE_Authority    Remote:ROLE_SimulatedProxy
```

结果可见，Default的函数在3个端上都可以运行，而BlueprintAuthorityOnly只能在服务器上运行。而Client上无法运行。

## 原理：

```cpp
int32 AActor::GetFunctionCallspace( UFunction* Function, FFrame* Stack )
{
	FunctionCallspace::Type Callspace = (LocalRole < ROLE_Authority) && Function->HasAllFunctionFlags(FUNC_BlueprintAuthorityOnly) ? FunctionCallspace::Absorbed : FunctionCallspace::Local;
}
```