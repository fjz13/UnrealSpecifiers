---
title: "NeedsDeferredDependencyLoading"
id: "UCLASS.NeedsDeferredDependencyLoading"
kind: "specifier"
symbol: "NeedsDeferredDependencyLoading"
scope: "UCLASS"
category: "Blueprint"
source_status: "imported_from_unreal_specifiers"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "UCLASS(NeedsDeferredDependencyLoading, MinimalAPI)"
usage: "UCLASS / Blueprint"
---

# NeedsDeferredDependencyLoading

- **引擎模块：** Blueprint
- **元数据类型：** bool
- **作用机制：** 在ClassFlags增加[CLASS_NeedsDeferredDependencyLoading](../../../Flags/EClassFlags/CLASS_NeedsDeferredDependencyLoading.md)

## 源码例子：

```cpp
UCLASS(NeedsDeferredDependencyLoading, MinimalAPI)
class UBlueprintGeneratedClass : public UClass, public IBlueprintPropertyGuidProvider
{
}
```

## 原理：

```cpp
if (ClassFlags.HasAnyFlags(EClassFlags.NeedsDeferredDependencyLoading) && !IsChildOf(Session.UClass))
{
	// CLASS_NeedsDeferredDependencyLoading can only be set on classes derived from UClass
	this.LogError($"'NeedsDeferredDependencyLoading' is set on '{SourceName}' but the flag can only be used with classes derived from UClass.");
}
```