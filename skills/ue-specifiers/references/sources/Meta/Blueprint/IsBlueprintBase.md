---
title: "IsBlueprintBase"
id: "meta.IsBlueprintBase"
kind: "meta"
symbol: "IsBlueprintBase"
category: "Blueprint"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "说明此类是否为创建蓝图的一个可接受基类，与 UCLASS 说明符、Blueprintable 或 'NotBlueprintable` 相似"
usage: "UCLASS, UINTERFACE"
---

# IsBlueprintBase

- **功能描述：** 说明此类是否为创建蓝图的一个可接受基类，与 UCLASS 说明符、Blueprintable 或 'NotBlueprintable` 相似。

- **使用位置：** UCLASS, UINTERFACE

- **引擎模块：** Blueprint

- **元数据类型：** bool

- **关联项：**

  UCLASS：[Blueprintable](../../Specifier/UCLASS/Blueprint/Blueprintable/Blueprintable.md), [NotBlueprintable](../../Specifier/UCLASS/Blueprint/NotBlueprintable.md)

  UINTERFACE：[Blueprintable](../../Specifier/UINTERFACE/Blueprint/Blueprintable/Blueprintable.md), [NotBlueprintable](../../Specifier/UINTERFACE/Blueprint/NotBlueprintable/NotBlueprintable.md)

- **常用程度：** ★★★★★

## 行为

UE5.8 class metadata；UHT `Blueprintable`/`NotBlueprintable` 写入，控制是否可作为 Blueprint base。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `ObjectMacros.h` metadata declaration/comment
  - UE5.8 `BlueprintGraph` metadata constants or node usage
- 批次记录：`references/audits/ue5.8-p1-complete-pass.md`。

## 常见误用

参数名、属性名或目标宏写错导致 metadata 被保留但没有对应编辑器/Blueprint 行为。
