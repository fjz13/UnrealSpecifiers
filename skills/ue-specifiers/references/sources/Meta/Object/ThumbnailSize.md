---
title: "ThumbnailSize"
id: "meta.ThumbnailSize"
kind: "meta"
symbol: "ThumbnailSize"
category: "Object"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "改变缩略图的大小"
usage: "UCLASS, UPROPERTY"
---

# ThumbnailSize

## Decision Summary

- **Use when:** `ThumbnailSize` metadata 的 `UCLASS, UPROPERTY` 场景需要：改变缩略图的大小。
- **Do not use when:** 目标声明不属于 `UCLASS, UPROPERTY`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 改变缩略图的大小。
- **使用位置：** UCLASS, UPROPERTY
- **引擎模块：** Object Property
- **元数据类型：** bool
- **关联项：** [DisplayThumbnail](DisplayThumbnail.md)

改变缩略图的大小。但发现并不会起作用。
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。

## 原理：

```cpp
void SObjectPropertyEntryBox::Construct( const FArguments& InArgs )
{
	// check if the property metadata wants us to display a thumbnail
const FString& DisplayThumbnailString = PropertyHandle->GetProperty()->GetMetaData(TEXT("DisplayThumbnail"));
if(DisplayThumbnailString.Len() > 0)
{
	bDisplayThumbnail = DisplayThumbnailString == TEXT("true");
}

// check if the property metadata has an override to the thumbnail size
const FString& ThumbnailSizeString = PropertyHandle->GetProperty()->GetMetaData(TEXT("ThumbnailSize"));
if ( ThumbnailSizeString.Len() > 0 )
{
	FVector2D ParsedVector;
	if ( ParsedVector.InitFromString(ThumbnailSizeString) )
	{
		ThumbnailSize.X = (int32)ParsedVector.X;
		ThumbnailSize.Y = (int32)ParsedVector.Y;
	}
}
}
```
