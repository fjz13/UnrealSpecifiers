---
title: "VisibleInstanceOnly"
id: "UPROPERTY.VisibleInstanceOnly"
kind: "specifier"
symbol: "VisibleInstanceOnly"
scope: "UPROPERTY"
category: "DetailsPanel"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "在实例细节面板可见，但不可编辑"
usage: "UPROPERTY / DetailsPanel"
---

# VisibleInstanceOnly

- **功能描述：** 在实例细节面板可见，但不可编辑
- **元数据类型：** bool
- **引擎模块：** DetailsPanel, Editor
- **作用机制：** 在PropertyFlags中加入CPF_Edit, CPF_DisableEditOnTemplate
- **常用程度：** ★★★★★

一并参见EditAnywhere里的示例代码和效果。

## 行为

`VisibleInstanceOnly` 让属性只在实例 Details Panel 中可见，但不可编辑；在类默认值、Blueprint 默认值或 CDO 相关 Details Panel 中禁用显示。

适合用于实例运行状态、实例绑定结果、场景对象引用等只想让关卡实例查看但不允许手改的属性。

## UE5.8 审计结论

状态：`verified_UE5.8`

在 `D:/github/GitWorkspace/Hello/Source/Insider/Property/MyProperty_Test.h` 中，`MyInt_VisibleInstanceOnly` 的样例注释记录了以下核心 flags：

```text
CPF_Edit | CPF_DisableEditOnTemplate | CPF_EditConst
```

`bat/build-hello.bat` 已在 UE5.8 下成功编译 `HelloEditor Win64 Development`，说明该样例可通过 UE5.8 UHT/编译流程。

UE5.8 源码 `C:/Program Files/Epic Games/UE_5.8/Engine/Source/Programs/Shared/EpicGames.UHT/Specifiers/UhtPropertyMemberSpecifiers.cs` 中，UHT 解析逻辑把 `VisibleInstanceOnly` 映射为 `Edit | EditConst | DisableEditOnTemplate`，并且会拒绝同一个属性上出现多个 edit/visibility specifier。

## 常见误用

- 不要把 `VisibleInstanceOnly` 当作“实例可编辑”；它是实例可见但不可编辑。
- 不要和任何 `Edit*` 或其他 `Visible*` specifier 同时使用；edit/visibility 维度只能选择一个。
- 如果属性应在默认值面板可见，应使用 `VisibleDefaultsOnly` 或 `VisibleAnywhere`。
