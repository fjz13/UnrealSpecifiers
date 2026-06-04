---
title: "MustBeLevelActor"
id: "meta.MustBeLevelActor"
kind: "meta"
symbol: "MustBeLevelActor"
category: "Object"
source_status: "imported_from_unreal_specifiers"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "意思是这个必须是场景里的Actor，而不是LevelScriptActor的意思"
usage: "UPROPERTY"
---

# MustBeLevelActor

- **使用位置：** UPROPERTY
- **引擎模块：** Object Property
- **元数据类型：** bool

意思是这个必须是场景里的Actor，而不是LevelScriptActor的意思。

触发时机在用箭头选择的当前选中actor的时候。

## 源码中遇见：

```cpp
if (FObjectPropertyBase* ObjectProperty = CastField<FObjectPropertyBase>(Property))
{
	ObjectClass = ObjectProperty->PropertyClass;
	bMustBeLevelActor = ObjectProperty->GetOwnerProperty()->GetBoolMetaData(TEXT("MustBeLevelActor"));
	RequiredInterface = ObjectProperty->GetOwnerProperty()->GetClassMetaData(TEXT("MustImplement"));
}
```