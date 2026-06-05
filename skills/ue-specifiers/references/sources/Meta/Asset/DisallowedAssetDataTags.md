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

## Decision Summary

- **Use when:** `DisallowedAssetDataTags` metadata 的 `UPROPERTY` 场景需要：在UObject*属性上指定Tags来进行过滤，必须没有拥有该Tags才可以被选择。
- **Do not use when:** 目标声明不属于 `UPROPERTY`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 在UObject*属性上指定Tags来进行过滤，必须没有拥有该Tags才可以被选择。
- **使用位置：** UPROPERTY
- **引擎模块：** Asset Property
- **元数据类型：** strings="a=b，c=d，e=f"
- **限制类型：** UObject*
- **关联项：** [RequiredAssetDataTags](RequiredAssetDataTags.md), [AssetRegistrySearchable](../../Specifier/UPROPERTY/Asset/AssetRegistrySearchable.md)
- **常用程度：** ★★
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。
