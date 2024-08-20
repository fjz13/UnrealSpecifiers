# NotReplicated

- **引擎模块：**Blueprint, Network, Parameter
- **作用机制：**在PropertyFlags中加入[CPF_RepSkip](../../../Flags/EPropertyFlags/CPF_RepSkip.md)

参照UFUNCTION的ServiceRequest，该标识符弃用。

“Only parameters in service request functions can be marked NotReplicated”

```cpp
if (context.PropertySettings.PropertyCategory == UhtPropertyCategory.ReplicatedParameter)
			{
				context.PropertySettings.PropertyCategory = UhtPropertyCategory.RegularParameter;
				context.PropertySettings.PropertyFlags |= EPropertyFlags.RepSkip;
			}
			else
			{
				context.MessageSite.LogError("Only parameters in service request functions can be marked NotReplicated");
			}
```

源码里只知道

```cpp
// Currently some features such as not replicating all parameters isn't allowed on regular RPCs
UFUNCTION(ServiceRequest(Iris))
void FunctionWithNotReplicatedNonPODParameters(int Param0, bool Param1, int Param2, UPARAM(NotReplicated) const TArray<FTestReplicationStateDescriptor_TestStructWithRefCArray>& NotReplicatedParam3);
void FunctionWithNotReplicatedNonPODParameters_Implementation(int Param0, bool Param1, int Param2, UPARAM(NotReplicated) const TArray<FTestReplicationStateDescriptor_TestStructWithRefCArray>& NotReplicatedParam3);
```