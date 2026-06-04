---
title: "DisallowedAssetDataTags"
id: "meta.DisallowedAssetDataTags"
kind: "meta"
symbol: "DisallowedAssetDataTags"
category: "Asset"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "在UObject*属性上指定Tags来进行过滤，必须没有拥有该Tags才可以被选择"
usage: "UPROPERTY"
---

# DisallowedAssetDataTags

- **功能描述：** 在UObject*属性上指定Tags来进行过滤，必须没有拥有该Tags才可以被选择。
- **使用位置：** UPROPERTY
- **引擎模块：** Asset Property
- **元数据类型：** strings="a=b，c=d，e=f"
- **限制类型：** UObject*
- **关联项：** [RequiredAssetDataTags](RequiredAssetDataTags/RequiredAssetDataTags.md), [AssetRegistrySearchable](../../Specifier/UPROPERTY/Asset/AssetRegistrySearchable/AssetRegistrySearchable.md)
- **常用程度：** ★★
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。
