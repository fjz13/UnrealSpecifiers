---
title: "VisibleAnywhere"
id: "UPROPERTY.VisibleAnywhere"
kind: "specifier"
symbol: "VisibleAnywhere"
scope: "UPROPERTY"
category: "DetailsPanel"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "在默认值和实例细节面板均可见，但不可编辑"
usage: "UPROPERTY / DetailsPanel"
---

# VisibleAnywhere

- **功能描述：** 在默认值和实例细节面板均可见，但不可编辑

- **元数据类型：** bool
- **引擎模块：** DetailsPanel, Editor
- **作用机制：** 在PropertyFlags中加入[CPF_Edit](../../../Flags/EPropertyFlags/CPF_Edit.md), [CPF_EditConst](../../../Flags/EPropertyFlags/CPF_EditConst.md)
- **常用程度：** ★★★★★

一并参见EditAnywhere里的示例代码和效果。

## 行为

`VisibleAnywhere` 让属性在类默认值和实例的 Details Panel 中都可见，但不可编辑。它适合展示由代码、组件或运行时状态维护的值。

## UE5.8 审计结论

在 UE5.8 UHT 源码 `UhtPropertyMemberSpecifiers.cs` 中，`VisibleAnywhereSpecifier` 会设置 `EPropertyFlags.Edit | EPropertyFlags.EditConst`，并通过 `SeenEditSpecifier` 与其他 edit/visibility specifier 互斥。Hello 样例 `Property/MyProperty_Test.h` 中的属性 flags 对应 `CPF_Edit | CPF_EditConst`。

## 常见误用

- `VisibleAnywhere` 不是“任意位置可编辑”，它是可见但只读。
- 不要和任何 `Edit*` 或其他 `Visible*` specifier 同时使用。
- Blueprint 读写权限仍由 `BlueprintReadOnly`、`BlueprintReadWrite` 等 specifier 单独控制。
