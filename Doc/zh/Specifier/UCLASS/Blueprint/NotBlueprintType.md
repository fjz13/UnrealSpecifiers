---
title: "NotBlueprintType"
id: "UCLASS.NotBlueprintType"
kind: "specifier"
symbol: "NotBlueprintType"
scope: "UCLASS"
category: "Blueprint"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "不可当做变量类型"
usage: "UCLASS / Blueprint"
---

# NotBlueprintType

- **功能描述：** 不可当做变量类型
- **引擎模块：** Blueprint
- **元数据类型：** bool
- **作用机制：** Meta移除[BlueprintType](../../../Meta/Blueprint/BlueprintType.md)
- **关联项：** [BlueprintType](BlueprintType/BlueprintType.md)
- **常用程度：★★★★**

## 行为

UE5.8 UHT 默认 specifier 写入 `NotBlueprintType=true` metadata，并移除当前 metadata index 的 `BlueprintType`。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtClassSpecifiers.cs` class specifier branch
  - UE5.8 `UhtClass.cs` class flag/metadata resolution and validation

## 常见误用

把 class specifier 的 metadata/flag 结果和 property/function specifier 混淆；或忽略继承/撤销类 specifier 的相互作用。
