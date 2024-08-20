# WithValidation

- **功能描述：**指定一个RPC函数在执行前需要验证，只有验证通过才可以执行。
- **元数据类型：**bool
- **引擎模块：**Network
- **作用机制：**在FunctionFlags中加入[FUNC_NetValidate](../../../Flags/EFunctionFlags/FUNC_NetValidate.md)
- **常用程度：★★★★★**

指定一个RPC函数在执行前需要验证，只有验证通过才可以执行。

WithValidation实际上可以用于Client，Server，NetMulticast的RPC函数，但一般来说还是用在Server的最多，因为一般是Server的数据最权威可以进行数据合法性校验。

## 测试代码：

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyFunction_PlayerController :public APlayerController
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Client, Reliable,WithValidation)
	void MyFunc2_RunOnClient();

		UFUNCTION(BlueprintCallable, Server, Reliable,WithValidation)
	void MyFunc2_RunOnServer();
};

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyFunction_Network :public AActor
{
public:
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable,WithValidation)
	void MyFunc2_NetMulticast();
};

void AMyFunction_PlayerController::MyFunc2_RunOnServer_Implementation()
{
	UInsiderLibrary::PrintFuncStatus(this, TEXT("MyFunc2_RunOnServer_Implementation"));
}

bool AMyFunction_PlayerController::MyFunc2_RunOnServer_Validate()
{
	UInsiderLibrary::PrintFuncStatus(this, TEXT("MyFunc2_RunOnServer_Validate"));
	return true;
}

bool AMyFunction_Network::MyFunc2_NetMulticast_Validate()
{
	UInsiderLibrary::PrintFuncStatus(this, TEXT("MyFunc2_NetMulticast_Validate"));
	return true;
}
```

## 测试结果：

```cpp
RunOnClient:
LogInsider: Display: 815f7800    MyFunc2_RunOnClient_Validate    BP_NetworkPC_C_0    NM_Client   Local:ROLE_AutonomousProxy  Remote:ROLE_Authority
LogInsider: Display: 815f7800    MyFunc2_RunOnClient_Implementation  BP_NetworkPC_C_0    NM_Client   Local:ROLE_AutonomousProxy  Remote:ROLE_Authority

RunOnServer:
LogInsider: Display: 7fd11800    MyFunc2_RunOnServer_Validate    BP_NetworkPC_C_1    NM_ListenServer Local:ROLE_Authority    Remote:ROLE_AutonomousProxy
LogInsider: Display: 7fd11800    MyFunc2_RunOnServer_Implementation  BP_NetworkPC_C_1    NM_ListenServer Local:ROLE_Authority    Remote:ROLE_AutonomousProxy

Multicast: ServerOwned
LogInsider: Display: 947e6400    MyFunc2_NetMulticast_Validate   BP_Network_C_1  NM_ListenServer Local:ROLE_Authority    Remote:ROLE_SimulatedProxy
LogInsider: Display: 947e6400    MyFunc2_NetMulticast_Implementation BP_Network_C_1  NM_ListenServer Local:ROLE_Authority    Remote:ROLE_SimulatedProxy
LogInsider: Display: 8795eb00    MyFunc2_NetMulticast_Validate   BP_Network_C_1  NM_Client   Local:ROLE_SimulatedProxy   Remote:ROLE_Authority
LogInsider: Display: 8795eb00    MyFunc2_NetMulticast_Implementation BP_Network_C_1  NM_Client   Local:ROLE_SimulatedProxy   Remote:ROLE_Authority
LogInsider: Display: 8f6a3700    MyFunc2_NetMulticast_Validate   BP_Network_C_1  NM_Client   Local:ROLE_SimulatedProxy   Remote:ROLE_Authority
LogInsider: Display: 8f6a3700    MyFunc2_NetMulticast_Implementation BP_Network_C_1  NM_Client   Local:ROLE_SimulatedProxy   Remote:ROLE_Authority

```

## 原理：

如果加上WithValidation标记，在UHT生成代码的时候就会：

```cpp
DEFINE_FUNCTION(AMyFunction_PlayerController::execMyFunc2_RunOnServer)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		if (!P_THIS->MyFunc2_RunOnServer_Validate())
		{
			RPC_ValidateFailed(TEXT("MyFunc2_RunOnServer_Validate"));
			return;
		}
		P_THIS->MyFunc2_RunOnServer_Implementation();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AMyFunction_PlayerController::execMyFunc2_RunOnClient)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		if (!P_THIS->MyFunc2_RunOnClient_Validate())
		{
			RPC_ValidateFailed(TEXT("MyFunc2_RunOnClient_Validate"));
			return;
		}
		P_THIS->MyFunc2_RunOnClient_Implementation();
		P_NATIVE_END;
	}

DEFINE_FUNCTION(AMyFunction_Network::execMyFunc2_NetMulticast)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	if (!P_THIS->MyFunc2_NetMulticast_Validate())
	{
		RPC_ValidateFailed(TEXT("MyFunc2_NetMulticast_Validate"));
		return;
	}
	P_THIS->MyFunc2_NetMulticast_Implementation();
	P_NATIVE_END;
}
```