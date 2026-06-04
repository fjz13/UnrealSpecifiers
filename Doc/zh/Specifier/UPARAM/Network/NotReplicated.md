---
title: "NotReplicated"
id: "UPARAM.NotReplicated"
kind: "specifier"
symbol: "NotReplicated"
scope: "UPARAM"
category: "Network"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "只用于 ServiceRequest 产生的 replicated parameter，可把该参数标记为不参与 service request 参数复制"
usage: "UPARAM / Network"
---

# NotReplicated

- **功能描述：** 只用于 `ServiceRequest` 产生的 replicated parameter，可把该参数标记为不参与 service request 参数复制。
- **引擎模块：** Blueprint, Network, Parameter
- **作用机制：** 在PropertyFlags中加入CPF_RepSkip

UE5.8 中该 specifier 仍存在，但只允许 service request functions 的 replicated parameter 使用。

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

## 行为

UE5.8 UHT 的 property argument `NotReplicated` 只允许 service request replicated parameter；通过时把参数 category 改为 regular parameter 并写入 `CPF_RepSkip`。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtPropertyArgumentSpecifiers.cs` `NotReplicatedSpecifier` handles only replicated service parameters

## 常见误用

在普通 UFUNCTION 参数上使用；UHT 会报 only service request functions can use it。
