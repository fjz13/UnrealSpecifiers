# HideSpawnParms

功能描述: 在UGamelayTask子类生成的蓝图异步节点上隐藏UGamelayTask子类继承链中某些属性。
使用位置: UFUNCTION
Feature: Blueprint
元数据类型: strings="a，b，c"
Status: Done
Parent item: ExposedAsyncProxy (ExposedAsyncProxy.md)

在UGamelayTask子类生成的蓝图异步节点上隐藏UGamelayTask子类继承链中某些属性。

HideSpawnParms 只在UK2Node_LatentGameplayTaskCall中判断，因此只作用于UGameplayTask的子类。在源码中找到的唯一用法是 HideSpawnParms = "Instigator”，但是其UGamelayTask子类继承链中并无该属性，因此其实是不发挥作用的。

```cpp
	UFUNCTION(BlueprintCallable, Meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true", HideSpawnParms = "Instigator"), Category = "Ability|Tasks")
	static UAbilityTask_StartAbilityState* StartAbilityState(UGameplayAbility* OwningAbility, FName StateName, bool bEndCurrentState = true);
```

保留和去掉HideSpawnParms 的蓝图的节点都为：

![Untitled](HideSpawnParms/Untitled.png)

源码里发生的位置：

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