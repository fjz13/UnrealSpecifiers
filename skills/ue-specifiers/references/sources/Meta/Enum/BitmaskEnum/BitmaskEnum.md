---
title: "BitmaskEnum"
id: "meta.BitmaskEnum"
kind: "meta"
symbol: "BitmaskEnum"
scope: "BitmaskEnum"
category: "Enum"
source_status: "imported_from_unreal_specifiers"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "使用位标记后采用的枚举名字"
usage: "UPROPERTY"
---

# BitmaskEnum

- **功能描述：** 使用位标记后采用的枚举名字
- **使用位置：** UPROPERTY
- **元数据类型：** string="abc"
- **限制类型：** 用来表示枚举值的int32
- **关联项：** [Bitmask](../Bitmask/Bitmask.md)
- **常用程度：** ★★★★★

如果没有标上BitmaskEnum，则无法提供标记的的名称值

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyActor_EnumBitFlags_Test:public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Meta = (Bitmask))
	int32 MyNormalWithoutEnum;
};
```

如果没有标上BitmaskEnum，则无法提供标记的的名称值

![Untitled](Untitled.png)