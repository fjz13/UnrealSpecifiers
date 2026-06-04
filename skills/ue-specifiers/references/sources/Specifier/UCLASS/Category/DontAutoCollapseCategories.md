---
title: "DontAutoCollapseCategories"
id: "UCLASS.DontAutoCollapseCategories"
kind: "specifier"
symbol: "DontAutoCollapseCategories"
scope: "UCLASS"
category: "Category"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "使列出的类别的继承自父类的AutoCollapseCategories说明符无效"
usage: "UCLASS / Category"
---

# DontAutoCollapseCategories

- **功能描述：**  使列出的类别的继承自父类的AutoCollapseCategories说明符无效。
- **引擎模块：** Category
- **元数据类型：** strings="a，b，c"
- **作用机制：** 在Meta中去除[AutoCollapseCategories](../../../Meta/DetailsPanel/AutoCollapseCategories.md)
- **关联项：** [AutoCollapseCategories](AutoCollapseCategories/AutoCollapseCategories.md)
- **常用程度：★**

根据代码，只是简单的移除AutoCollapseCategories，和AutoExpandCategories的区别就是不会自动加一个展开。在源码里搜了一下，并没有使用到。而且当前的源码实现有bug，做不到去除。

```cpp
case EClassMetadataSpecifier::AutoExpandCategories:

	FHeaderParser::RequireSpecifierValue(*this, PropSpecifier);

	for (FString& Value : PropSpecifier.Values)
	{
		AutoCollapseCategories.RemoveSwap(Value);
		AutoExpandCategories.AddUnique(MoveTemp(Value));
	}
	break;

case EClassMetadataSpecifier::AutoCollapseCategories:

	FHeaderParser::RequireSpecifierValue(*this, PropSpecifier);

	for (FString& Value : PropSpecifier.Values)
	{
		AutoExpandCategories.RemoveSwap(Value);
		AutoCollapseCategories.AddUnique(MoveTemp(Value));
	}
	break;
case EClassMetadataSpecifier::DontAutoCollapseCategories:

	FHeaderParser::RequireSpecifierValue(*this, PropSpecifier);

	for (const FString& Value : PropSpecifier.Values)
	{
			AutoCollapseCategories.RemoveSwap(Value);//当前AutoCollapseCategories的值还是空的。去除是没有用的
	}
	break;

改动：
FUnrealClassDefinitionInfo::MergeClassCategories()放最后：
// Merge DontAutoCollapseCategories and AutoCollapseCategories
	for (const FString& Value : DontAutoCollapseCategories)
	{
		AutoCollapseCategories.RemoveSwap(Value);
	}
	DontAutoCollapseCategories.Empty();

改为：
case EClassMetadataSpecifier::DontAutoCollapseCategories:

			FHeaderParser::RequireSpecifierValue(*this, PropSpecifier);

			for (FString& Value : PropSpecifier.Values)
			{
				DontAutoCollapseCategories.AddUnique(MoveTemp(Value));
				//AutoCollapseCategories.RemoveSwap(Value);
			}
			break;
```

## 行为

UE5.8 UHT 从 `AutoCollapseCategories` 中移除指定分类，用于撤销父类/前置规则。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtClassSpecifiers.cs` class specifier branch
  - UE5.8 `UhtClass.cs` class flag/metadata resolution and validation

## 常见误用

把 class specifier 的 metadata/flag 结果和 property/function specifier 混淆；或忽略继承/撤销类 specifier 的相互作用。
