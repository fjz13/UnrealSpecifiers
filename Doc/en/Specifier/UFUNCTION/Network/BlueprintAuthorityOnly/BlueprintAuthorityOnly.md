# BlueprintAuthorityOnly

- **Function description:** This function can only execute on a terminal with network access.
- **Metadata type:** bool
- **Engine module:** Network
- **Action mechanism:** Add [FUNC_BlueprintAuthorityOnly](../../../../Flags/EFunctionFlags/FUNC_BlueprintAuthorityOnly.md) to the FunctionFlags
- **Commonality:** ★★★

This function can only be executed on a client with network permissions. HasAuthority:: (GetLocalRole() == ROLE_Authority). There are four types of NetRole: ROLE_None (not replicated), ROLE_SimulatedProxy (simulated proxy on the client), ROLE_AutonomousProxy (anonymous proxy on the client, receiving player input), and ROLE_Authority (the server with permissions).

Thus, BlueprintAuthorityOnly restricts this function to run only on the server, which can be an LS server, a DS server, or a standalone server (considered as a server without a client).

Note that the Actor must be set to Replicates for testing purposes.

## Test Code:

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

## Blueprint Code:

![Untitled](Untitled.png)

For non-replicated Actors:

```cpp
MyFunc_Default  BP_Network_C_1  NM_ListenServer Local:ROLE_Authority    Remote:ROLE_None
MyFunc_Default  BP_Network_C_1  NM_Client   Local:ROLE_None Remote:ROLE_Authority
MyFunc_Default  BP_Network_C_1  NM_Client   Local:ROLE_None Remote:ROLE_Authority
```

For replicated Actors, with 1 Server and two Clients simultaneously, run the standard function:

```cpp
MyFunc_Default  BP_Network_C_1  NM_ListenServer Local:ROLE_Authority    Remote:ROLE_SimulatedProxy
MyFunc_Default  BP_Network_C_1  NM_Client   Local:ROLE_SimulatedProxy   Remote:ROLE_Authority
MyFunc_Default  BP_Network_C_1  NM_Client   Local:ROLE_SimulatedProxy   Remote:ROLE_Authority
```

If the BlueprintAuthorityOnly function is permitted:

```cpp
MyFunc_BlueprintAuthorityOnly   BP_Network_C_1  NM_ListenServer Local:ROLE_Authority    Remote:ROLE_SimulatedProxy
```

The results indicate that the Default function can run on all three ends, whereas BlueprintAuthorityOnly operates exclusively on the server and not on the client.

## Principle:

```cpp
int32 AActor::GetFunctionCallspace( UFunction* Function, FFrame* Stack )
{
	FunctionCallspace::Type Callspace = (LocalRole < ROLE_Authority) && Function->HasAllFunctionFlags(FUNC_BlueprintAuthorityOnly) ? FunctionCallspace::Absorbed : FunctionCallspace::Local;
}
```