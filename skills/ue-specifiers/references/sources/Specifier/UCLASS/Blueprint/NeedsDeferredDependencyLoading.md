---
title: "NeedsDeferredDependencyLoading"
id: "UCLASS.NeedsDeferredDependencyLoading"
kind: "specifier"
symbol: "NeedsDeferredDependencyLoading"
scope: "UCLASS"
category: "Blueprint"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "UCLASS(NeedsDeferredDependencyLoading, MinimalAPI)"
usage: "UCLASS / Blueprint"
---

# NeedsDeferredDependencyLoading

## Decision Summary

- **Use when:** `NeedsDeferredDependencyLoading` specifier 的 `UCLASS / Blueprint` 场景需要：UCLASS(NeedsDeferredDependencyLoading, MinimalAPI)。
- **Do not use when:** 声明宏、目标类型或代码契约不属于 `UCLASS / Blueprint`。
- **Requires:** specifier 必须放在 UE5.8 UHT 支持的宏和声明位置，并满足正文 caveat。
- **Conflicts:** 不要和同类互斥 specifier 或语义相反的暴露/持久化/网络规则混用。
- **Prefer instead:** 能用更窄暴露范围或更明确 metadata 表达时，优先选择更窄方案。

- **引擎模块：** Blueprint
- **元数据类型：** bool
- **作用机制：** 在ClassFlags增加CLASS_NeedsDeferredDependencyLoading

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

## 行为

UE5.8 UHT 写入 `CLASS_NeedsDeferredDependencyLoading`，用于延迟依赖加载路径。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtClassSpecifiers.cs` class specifier branch
  - UE5.8 `UhtClass.cs` class flag/metadata resolution and validation

## 常见误用

把低层/引擎内部 class flag 当成常规 gameplay class 设计工具。
