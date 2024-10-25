# NetMulticast

- **Function Description:** Define a multicast RPC function that is executed on both the server and the client. The corresponding implementation function will have the _Implementation suffix appended.

- **Metadata Type:** bool
- **Engine Module:** Network
- **Action Mechanism:** Add [FUNC_Net](../../../../Flags/EFunctionFlags/FUNC_Net.md) and [FUNC_NetMulticast](../../../../Flags/EFunctionFlags/FUNC_NetMulticast.md) to the Function Flags
- **Usage Frequency:** ★★★★★

Define a multicast RPC function that is executed on both the server and the client. The corresponding implementation function will have the _Implementation suffix appended.

RPC execution rules, refer to the documentation: [https://docs.unrealengine.com/4.27/zh-CN/InteractiveExperiences/Networking/Actors/RPCs/](https://docs.unrealengine.com/4.27/zh-CN/InteractiveExperiences/Networking/Actors/RPCs/)

![Untitled](Untitled.png)

## Test Code:

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

Test Blueprint: PIE mode, with one ListenServer and two Clients

![Untitled](Untitled.png)

## Test Output Results:

```cpp
LogInsider: Display: 46715a00    MyFunc_NetMulticast_Implementation  BP_Network_C_1  NM_ListenServer Local:ROLE_Authority    Remote:ROLE_SimulatedProxy
LogInsider: Display: 46e65000    MyFunc_NetMulticast_Implementation  BP_Network_C_1  NM_Client   Local:ROLE_SimulatedProxy   Remote:ROLE_Authority
LogInsider: Display: 29aaaa00    MyFunc_NetMulticast_Implementation  BP_Network_C_1  NM_Client   Local:ROLE_SimulatedProxy   Remote:ROLE_Authority

LogInsider: Display: 4ff44600    OtherMulticastFunc  BP_Network_C_1  NM_ListenServer Local:ROLE_Authority    Remote:ROLE_SimulatedProxy
LogInsider: Display: 3bf89b00    OtherMulticastFunc  BP_Network_C_1  NM_Client   Local:ROLE_SimulatedProxy   Remote:ROLE_Authority
LogInsider: Display: 29d68700    OtherMulticastFunc  BP_Network_C_1  NM_Client   Local:ROLE_SimulatedProxy   Remote:ROLE_Authority
```

On a Server-Owned Actor, initiating a Multicast RPC event call can be observed to be invoked on all three ends.