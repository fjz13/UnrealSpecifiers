---
title: "BlueprintType"
id: "meta.BlueprintType"
kind: "meta"
symbol: "BlueprintType"
category: "Blueprint"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "表明可以作为一个蓝图变量"
usage: "UCLASS, UENUM, UINTERFACE, USTRUCT"
---

# BlueprintType

## Decision Summary

- **Use when:** UCLASS/USTRUCT/UENUM/UINTERFACE 类型需要作为 Blueprint 变量、参数或返回类型。
- **Do not use when:** 只是想允许 Blueprint 派生类，或类型不应进入 Blueprint API。
- **Requires:** 类型及其暴露成员应适合 Blueprint 使用。
- **Conflicts:** 不等同于 `Blueprintable`。
- **Prefer instead:** 允许 Blueprint 继承用 `Blueprintable`；C++-only 类型不暴露。

- **功能描述：** 表明可以作为一个蓝图变量

- **使用位置：** UCLASS, UENUM, UINTERFACE, USTRUCT

- **引擎模块：** Blueprint

- **元数据类型：** bool

- **关联项：**

  UCLASS：[Blueprintable](../../Specifier/UCLASS/Blueprint/Blueprintable.md), [NotBlueprintable](../../Specifier/UCLASS/Blueprint/NotBlueprintable.md), [BlueprintType](../../Specifier/UCLASS/Blueprint/BlueprintType.md), [NotBlueprintType](../../Specifier/UCLASS/Blueprint/NotBlueprintType.md)

  Meta：[BlueprintInternalUseOnly](BlueprintInternalUseOnly.md), [BlueprintInternalUseOnlyHierarchical](BlueprintInternalUseOnlyHierarchical.md)

  UENUM：[BlueprintType](../../Specifier/UENUM/BlueprintType.md)

  UFUNCTION：[BlueprintInternalUseOnly](../../Specifier/UFUNCTION/UHT/BlueprintInternalUseOnly.md)

  UINTERFACE：[Blueprintable](../../Specifier/UINTERFACE/Blueprint/Blueprintable.md), [NotBlueprintable](../../Specifier/UINTERFACE/Blueprint/NotBlueprintable.md)

  USTRUCT：[BlueprintInternalUseOnly](../../Specifier/USTRUCT/Blueprint/BlueprintInternalUseOnly.md), [BlueprintType](../../Specifier/USTRUCT/Blueprint/BlueprintType.md)

- **常用程度：** ★★★★★

## 行为

UE5.8 class/struct/enum metadata；UHT 默认 `BlueprintType` specifier 写入，控制 Blueprint 类型暴露。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `ObjectMacros.h` metadata declaration/comment
  - UE5.8 `BlueprintGraph` metadata constants or node usage

## 常见误用

参数名、属性名或目标宏写错导致 metadata 被保留但没有对应编辑器/Blueprint 行为。
