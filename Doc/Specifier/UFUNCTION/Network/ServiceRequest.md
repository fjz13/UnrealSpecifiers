# ServiceRequest

功能描述: 此函数为RPC（远程过程调用）服务请求。rpc服务请求
元数据类型: bool
引擎模块: Network
MetaOperation: =true
Meta: CustomThunk (../../Meta/Meta/CustomThunk.md)
Status: Invalid
+=EFunctionFlags: FUNC_Net (../../Flags/EFunctionFlags/FUNC_Net.md), FUNC_Event (../../Flags/EFunctionFlags/FUNC_Event.md), FUNC_NetReliable (../../Flags/EFunctionFlags/FUNC_NetReliable.md), FUNC_NetRequest (../../Flags/EFunctionFlags/FUNC_NetRequest.md)

在源码里都没看到使用，只搜到

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

UDN回答：

Alex: Those specifiers were added quite a while ago as a way to mark functions as RPC requests/responses to and from a backend service, the name of which would be given as part of the specifier: UFUNCTION(ServiceRequest(<Endpoint Name>)). However, the feature was never fully implemented, and since then the specifiers have only been used internally (and even then, I don't believe "ServiceResponse" is used at all anymore). This is why there isn't any public documentation or examples available, as they're not formally supported in the engine. You can check out ServiceRequestSpecifier and ServiceResponseSpecifier in UhtFunctionSpecifiers.cs to see how UHT handles these specifiers.

Mi: 这两个标记是我们用来自由扩展和自己的服务器通信的（例如http request），譬如可以提供自己的NetDriver处理特定标记的ServiceRequest的RPC，自己序列化对应参数发给自己的服务。

“意思是如果使用引擎的默认实现的话，使用这两个标记是无效的吗？我尝试在服务器或者客户端发起对ServiceRequest标记的ufunction的调用，结果都是会打印错误日志”

是的，默认的UE client和DS通信的NetDriver的RPC不需要这两个关键字，用了之后会找不到相应处理的NetDriver的实现。

在Server Owned Actor上调用会出错：LogNet: Warning: UNetDriver::ProcessRemoteFunction: No owning connection for actor BP_Network_C_1. Function MyFunc_ServiceRequest will not be processed.

在PC上Server调用也会：

LogRep: Error: Rejected RPC function due to access rights. Object: BP_NetworkPC_C /Game/UEDPIE_0_StartMap.StartMap:PersistentLevel.BP_NetworkPC_C_1, Function: MyFunc_ServiceRequest
LogNet: Error: UActorChannel::ProcessBunch: Replicator.ReceivedBunch failed.  Closing connection. RepObj: BP_NetworkPC_C /Game/UEDPIE_0_StartMap.StartMap:PersistentLevel.BP_NetworkPC_C_1, Channel: 3