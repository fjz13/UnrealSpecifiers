---
title: "AdvancedClassDisplay"
id: "meta.AdvancedClassDisplay"
kind: "meta"
symbol: "AdvancedClassDisplay"
category: "DetailsPanel"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定该类型的变量在高级显示里显示"
usage: "UCLASS"
---

# AdvancedClassDisplay

- **功能描述：** 指定该类型的变量在高级显示里显示

- **使用位置：** UCLASS

- **引擎模块：** DetailsPanel

- **元数据类型：** bool

- **关联项：**

  UCLASS：[AdvancedClassDisplay](../../Specifier/UCLASS/Category/AdvancedClassDisplay/AdvancedClassDisplay.md)

- **常用程度：** ★★★

## 行为

UE5.8 class metadata；与 UCLASS `AdvancedClassDisplay` 对应，使类属性默认显示在 advanced 区域。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `ObjectMacros.h` property/class metadata declaration/comment
  - UE5.8 `PropertyEditor` Details metadata usage
- 批次记录：`references/audits/ue5.8-p1-complete-pass.md`。

## 常见误用

参数名、属性名或目标宏写错导致 metadata 被保留但没有对应编辑器/Blueprint 行为。
