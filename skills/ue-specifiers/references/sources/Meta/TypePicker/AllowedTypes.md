---
title: "AllowedTypes"
id: "meta.AllowedTypes"
kind: "meta"
symbol: "AllowedTypes"
category: "TypePicker"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "为FPrimaryAssetId可以指定允许的资产类型"
usage: "UPROPERTY"
---

# AllowedTypes

## Decision Summary

- **Use when:** `AllowedTypes` metadata 的 `UPROPERTY` 场景需要：为FPrimaryAssetId可以指定允许的资产类型。
- **Do not use when:** 目标声明不属于 `UPROPERTY`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 为FPrimaryAssetId可以指定允许的资产类型。
- **使用位置：** UPROPERTY
- **引擎模块：** TypePicker
- **元数据类型：** strings="a，b，c"
- **限制类型：** FPrimaryAssetId
- **常用程度：** ★★★

为FPrimaryAssetId可以指定允许的资产类型。
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。

## 测试代码：

```cpp
UCLASS(BlueprintType)
class INSIDER_API UMyProperty_PrimaryAsset :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PrimaryAsset")
	FPrimaryAssetId MyPrimaryAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PrimaryAsset",meta=(AllowedTypes="MyAsset"))
	FPrimaryAssetId MyPrimaryAsset_Allowed;
};

```

## 测试结果：

在项目中已经事先定义了多个UPrimaryDataAsset，也在ProjectSettings里设置了。（如何定义请查看别的文章详解）。

可见MyPrimaryAsset_Allowed的选项只有一个了，说明受到了限制。


## 原理：

在FPrimaryAssetId 的定制化FPrimaryAssetIdCustomization中，会查看该标记，解析AllowedTypes的值并把它设置到成员变量AllowedTypes中去，最终达成筛选。

```cpp
TArray<FPrimaryAssetType> FPrimaryAssetIdCustomization::AllowedTypes;

void FPrimaryAssetIdCustomization::CustomizeHeader(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	check(UAssetManager::IsInitialized());

	StructPropertyHandle = InStructPropertyHandle;

	const FString& TypeFilterString = StructPropertyHandle->GetMetaData("AllowedTypes");
	if( !TypeFilterString.IsEmpty() )
	{
		TArray<FString> CustomTypeFilterNames;
		TypeFilterString.ParseIntoArray(CustomTypeFilterNames, TEXT(","), true);

		for(auto It = CustomTypeFilterNames.CreateConstIterator(); It; ++It)
		{
			const FString& TypeName = *It;

			AllowedTypes.Add(*TypeName);
		}
	}

	IAssetManagerEditorModule::MakePrimaryAssetIdSelector(
	FOnGetPrimaryAssetDisplayText::CreateSP(this, &FPrimaryAssetIdCustomization::GetDisplayText),
	FOnSetPrimaryAssetId::CreateSP(this, &FPrimaryAssetIdCustomization::OnIdSelected),
	bAllowClear, AllowedTypes, AllowedClasses, DisallowedClasses)

	}
```
