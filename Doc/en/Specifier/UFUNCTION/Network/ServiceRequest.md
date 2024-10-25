# ServiceRequest

- **Function Description:** This function serves as an RPC (Remote Procedure Call) service request. RPC service request
- **Metadata Type:** bool
- **Engine Module:** Network
- **Action Mechanism:** [CustomThunk](../../../Meta/UHT/CustomThunk.md) is added to Meta, and [FUNC_Net](../../../Flags/EFunctionFlags/FUNC_Net.md), [FUNC_Event](../../../Flags/EFunctionFlags/FUNC_Event.md), [FUNC_NetReliable](../../../Flags/EFunctionFlags/FUNC_NetReliable.md), and [FUNC_NetRequest](../../../Flags/EFunctionFlags/FUNC_NetRequest.md) are added to FunctionFlags

No usage was found in the source code, only search results were obtained

```cpp
UCLASS()
class UTestReplicationStateDescriptor_TestFunctionWithNotReplicatedNonPODParameters : public UObject
{
	GENERATED_BODY()

protected:
	// Currently some features such as not replicating all parameters isn't allowed on regular RPCs
	UFUNCTION(ServiceRequest(Iris))
	void FunctionWithNotReplicatedNonPODParameters(int Param0, bool Param1, int Param2, UPARAM(NotReplicated) const TArray<FTestReplicationStateDescriptor_TestStructWithRefCArray>& NotReplicatedParam3);
	void FunctionWithNotReplicatedNonPODParameters_Implementation(int Param0, bool Param1, int Param2, UPARAM(NotReplicated) const TArray<FTestReplicationStateDescriptor_TestStructWithRefCArray>& NotReplicatedParam3);
};
```

## UDN Response:

Alex: Those specifiers were added quite a while ago as a way to mark functions as RPC requests/responses to and from a backend service, the name of which would be given as part of the specifier: UFUNCTION(ServiceRequest(<Endpoint Name>)). However, the feature was never fully implemented, and since then the specifiers have only been used internally (and even then, I don't believe "ServiceResponse" is used at all anymore). This is why there isn't any public documentation or examples available, as they're not formally supported in the engine. You can check out ServiceRequestSpecifier and ServiceResponseSpecifier in UhtFunctionSpecifiers.cs to see how UHT handles these specifiers.

Mi: These two tags are used by us to freely expand our communication with our own servers (e.g., HTTP requests). For instance, we can provide our own NetDriver to handle the RPC for ServiceRequest with specific tags, serializing the corresponding parameters ourselves and sending them to our service.

"Does this mean that if the engine's default implementation is used, these two tags are ineffective? When I attempt to initiate a call to a ufunction with the ServiceRequest tag on the server or client, an error log is printed."

Yes, the default NetDriver for UE client and DS communication does not require these two keywords. Using them will result in the corresponding NetDriver implementation not being found.

An error occurs when calling on a Server-Owned Actor: LogNet: Warning: UNetDriver::ProcessRemoteFunction: No owning connection for actor BP_Network_C_1. Function MyFunc_ServiceRequest will not be processed.

An error also occurs when the server calls on a PC:

LogRep: Error: Rejected RPC function due to access rights. Object: BP_NetworkPC_C /Game/UEDPIE_0_StartMap.StartMap:PersistentLevel.BP_NetworkPC_C_1, Function: MyFunc_ServiceRequest
LogNet: Error: UActorChannel::ProcessBunch: Replicator.ReceivedBunch failed.  Closing connection. RepObj: BP_NetworkPC_C /Game/UEDPIE_0_StartMap.StartMap:PersistentLevel.BP_NetworkPC_C_1, Channel: 3