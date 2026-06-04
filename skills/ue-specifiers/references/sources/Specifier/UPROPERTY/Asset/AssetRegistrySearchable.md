---
title: "AssetRegistrySearchable"
id: "UPROPERTY.AssetRegistrySearchable"
kind: "specifier"
symbol: "AssetRegistrySearchable"
scope: "UPROPERTY"
category: "Asset"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "标记该属性可以作为AssetRegistry的Tag和Value值来进行资产的过滤搜索"
usage: "UPROPERTY / Asset"
---

# AssetRegistrySearchable

- **功能描述：** 标记该属性可以作为AssetRegistry的Tag和Value值来进行资产的过滤搜索
- **元数据类型：** bool
- **引擎模块：** Asset
- **作用机制：** 在PropertyFlags中加入CPF_AssetRegistrySearchable，在Meta中加入[RequiredAssetDataTags](../../../Meta/Asset/RequiredAssetDataTags.md)、[DisallowedAssetDataTags](../../../Meta/Asset/DisallowedAssetDataTags.md)
- **常用程度：** ★★★

不能用在结构属性上。

子类也可以重载GetAssetRegistryTags以提供自定义的Tag。

## 测试代码：

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyProperty_AssetRegistrySearchable :public UDataAsset
{
public:
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AssetRegistrySearchable, Category = DataRegistry)
		FString MyIdForSearch;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 OtherValue = 123;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DataRegistry)
		FString MyOtherIdForSearch;
public:
	virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override
	{
		//called on CDO and instances
		Super::GetAssetRegistryTags(Context);
		Context.AddTag(FAssetRegistryTag(TEXT("MyOtherId"),MyOtherIdForSearch, UObject::FAssetRegistryTag::TT_Alphabetical));
	}
};

```

## 测试结果：

在EditorUtilityWidget中测试，可见ListAssetByTagValue都可以搜索找到该Asset。


测试的蓝图代码，也可用IAssetRegistry::Get()->GetAssetsByTagValues(tagValues,outAssets);来进行搜索，不过要注意搜索的时机要在AssetRegistry加载之后，AssetRegistry如果是Runtime要记得序列化到磁盘

```cpp
//DefaultEngine.ini
[AssetRegistry]
bSerializeAssetRegistry=true
```

## 原理：

可查看GetAssetRegistryTags的函数的实现和调用。在UObject::GetAssetRegistryTags中调用使用，把该属性的值作为AssetData的Tag供给AssetRegistry

## 行为

UE5.8 UHT 的 property member specifier 分支写入 `CPF_AssetRegistrySearchable`。它让属性参与 asset registry tag/search 相关路径。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtPropertyMemberSpecifiers.cs` `AssetRegistrySearchableSpecifier` writes `CPF_AssetRegistrySearchable`
  - 本地样例辅助对照：`D:/github/GitWorkspace/Hello/Source/Insider/Property/Asset/MyProperty_AssetRegistrySearchable.h`。

## 常见误用

用于非资产/不参与资产注册语义的数据并期待运行时查询自动变快；它不是复制、保存或 Blueprint 暴露标志。
