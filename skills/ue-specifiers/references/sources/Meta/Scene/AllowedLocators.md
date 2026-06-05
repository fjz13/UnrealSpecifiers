---
title: "AllowedLocators"
id: "meta.AllowedLocators"
kind: "meta"
symbol: "AllowedLocators"
category: "Scene"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "用来给Sequencer定位可绑定的对象"
usage: "UPROPERTY"
---

# AllowedLocators

## Decision Summary

- **Use when:** `AllowedLocators` metadata 的 `UPROPERTY` 场景需要：用来给Sequencer定位可绑定的对象。
- **Do not use when:** 目标声明不属于 `UPROPERTY`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 用来给Sequencer定位可绑定的对象
- **使用位置：** UPROPERTY
- **引擎模块：** Scene
- **元数据类型：** string="abc"
- **限制类型：** FUniversalObjectLocator
- **常用程度：** ★

用来给Sequencer定位可绑定的对象。

看起来是Sequencer用来定位Actor做属性绑定的辅助定位器。只用在FUniversalObjectLocator 这个写好的属性里，一般我们用不到去扩展这部分，因此只是OnlyInternal。
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。

## 源码中搜索得到：

```cpp

	// Helper struct for Binding Properties UI for locators.
USTRUCT()
struct FMovieSceneUniversalLocatorInfo
{
	GENERATED_BODY()

	// Locator for the entry
	UPROPERTY(EditAnywhere, Category = "Default", meta=(AllowedLocators="Actor"))
	FUniversalObjectLocator Locator;

	// Flags for how to resolve the locator
	UPROPERTY()
	ELocatorResolveFlags ResolveFlags = ELocatorResolveFlags::None;
};
```

看起来是允许定位的对象类型。

## 原理：

```cpp
TMap<FName, TSharedPtr<ILocatorEditor>> ApplicableLocators;

void FUniversalObjectLocatorCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
		TArray<FString> AllowedTypes;
		if (PropertyHandle->HasMetaData("AllowedLocators"))
		{
			PropertyHandle->GetMetaData("AllowedLocators").ParseIntoArray(AllowedTypes, TEXT(","));
		}
}

FUniversalObjectLocatorEditorModule& Module = FModuleManager::Get().LoadModuleChecked<FUniversalObjectLocatorEditorModule>("UniversalObjectLocatorEditor");
for (TPair<FName, TSharedPtr<ILocatorEditor>> Pair : Module.LocatorEditors)
{
	if (AllowedTypes.Num() == 0 || AllowedTypes.Contains(Pair.Key.ToString()))
	{
		ApplicableLocators.Add(Pair.Key, Pair.Value);
	}
}
```
