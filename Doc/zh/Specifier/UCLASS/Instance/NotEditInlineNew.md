---
title: "NotEditInlineNew"
id: "UCLASS.NotEditInlineNew"
kind: "specifier"
symbol: "NotEditInlineNew"
scope: "UCLASS"
category: "Instance"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "不能通过EditInline按钮创建"
usage: "UCLASS / Instance"
---

# NotEditInlineNew

- **功能描述：**  不能通过EditInline按钮创建
- **引擎模块：** Instance
- **元数据类型：** bool
- **作用机制：** 在ClassFlags中移除CLASS_EditInlineNew
- **关联项：** EditInlineNew (EditInlineNew.md)
- **常用程度：★**

## 行为

UE5.8 UHT 移除 `CLASS_EditInlineNew`，用于撤销 inline new 类标志。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtClassSpecifiers.cs` class specifier branch
  - UE5.8 `UhtClass.cs` class flag/metadata resolution and validation

## 常见误用

把 class specifier 的 metadata/flag 结果和 property/function specifier 混淆；或忽略继承/撤销类 specifier 的相互作用。
