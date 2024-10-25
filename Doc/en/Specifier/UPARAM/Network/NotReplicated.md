# NotReplicated

- **Engine modules:** Blueprint, Network, Parameter
- **Mechanism of action:** Add [CPF_RepSkip](../../../Flags/EPropertyFlags/CPF_RepSkip.md) to PropertyFlags

Referring to UFUNCTION's ServiceRequest, this specifier is deprecated.

“Only parameters within service request functions can be marked as NotReplicated.”

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

“The source code only has knowledge of this.”

```cpp
// Currently some features such as not replicating all parameters isn't allowed on regular RPCs
UFUNCTION(ServiceRequest(Iris))
void FunctionWithNotReplicatedNonPODParameters(int Param0, bool Param1, int Param2, UPARAM(NotReplicated) const TArray<FTestReplicationStateDescriptor_TestStructWithRefCArray>& NotReplicatedParam3);
void FunctionWithNotReplicatedNonPODParameters_Implementation(int Param0, bool Param1, int Param2, UPARAM(NotReplicated) const TArray<FTestReplicationStateDescriptor_TestStructWithRefCArray>& NotReplicatedParam3);
```