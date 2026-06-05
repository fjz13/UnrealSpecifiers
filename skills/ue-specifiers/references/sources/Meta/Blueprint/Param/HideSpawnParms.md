---
title: "HideSpawnParms"
id: "meta.HideSpawnParms"
kind: "meta"
symbol: "HideSpawnParms"
category: "Blueprint"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "在UGamelayTask子类生成的蓝图异步节点上隐藏UGamelayTask子类继承链中某些属性"
usage: "UFUNCTION"
---

# HideSpawnParms

## Decision Summary

- **Use when:** `HideSpawnParms` metadata 的 `UFUNCTION` 场景需要：在UGamelayTask子类生成的蓝图异步节点上隐藏UGamelayTask子类继承链中某些属性。
- **Do not use when:** 目标声明不属于 `UFUNCTION`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 在UGamelayTask子类生成的蓝图异步节点上隐藏UGamelayTask子类继承链中某些属性。
- **使用位置：** UFUNCTION
- **元数据类型：** strings="a，b，c"
- **关联项：** [ExposedAsyncProxy](../ExposedAsyncProxy.md)

在UGamelayTask子类生成的蓝图异步节点上隐藏UGamelayTask子类继承链中某些属性。

HideSpawnParms 只在UK2Node_LatentGameplayTaskCall中判断，因此只作用于UGameplayTask的子类。在源码中找到的唯一用法是 HideSpawnParms = "Instigator”，但是其UGamelayTask子类继承链中并无该属性，因此其实是不发挥作用的。

```cpp
	UFUNCTION(BlueprintCallable, Meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true", HideSpawnParms = "Instigator"), Category = "Ability|Tasks")
	static UAbilityTask_StartAbilityState* StartAbilityState(UGameplayAbility* OwningAbility, FName StateName, bool bEndCurrentState = true);
```

保留和去掉HideSpawnParms 的蓝图的节点都为：


## 源码里发生的位置：

```cpp
void UK2Node_LatentGameplayTaskCall::CreatePinsForClass(UClass* InClass)
{
	// Tasks can hide spawn parameters by doing meta = (HideSpawnParms="PropertyA,PropertyB")
	// (For example, hide Instigator in situations where instigator is not relevant to your task)

	TArray<FString> IgnorePropertyList;
	{
		UFunction* ProxyFunction = ProxyFactoryClass->FindFunctionByName(ProxyFactoryFunctionName);

		const FString& IgnorePropertyListStr = ProxyFunction->GetMetaData(FName(TEXT("HideSpawnParms")));

		if (!IgnorePropertyListStr.IsEmpty())
		{
			IgnorePropertyListStr.ParseIntoArray(IgnorePropertyList, TEXT(","), true);
		}
	}
}
```

## 行为

UE5.8 function metadata；async task node 用于跳过指定 spawn 参数 pin。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `ObjectMacros.h` metadata declaration/comment
  - UE5.8 `BlueprintGraph` metadata constants or node usage

## 常见误用

参数名、属性名或目标宏写错导致 metadata 被保留但没有对应编辑器/Blueprint 行为。
