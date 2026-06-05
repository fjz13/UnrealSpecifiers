---
title: "EditInstanceOnly"
id: "UPROPERTY.EditInstanceOnly"
kind: "specifier"
symbol: "EditInstanceOnly"
scope: "UPROPERTY"
category: "DetailsPanel"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "只能在实例的细节面板上编辑该属性"
usage: "UPROPERTY / DetailsPanel"
---

# EditInstanceOnly

## Decision Summary

- **Use when:** 属性只应在已放置实例或运行时实例的 Details Panel 中编辑。
- **Do not use when:** 蓝图类默认值也需要配置该属性。
- **Requires:** 需要 Blueprint 访问时另加 `BlueprintReadOnly` 或 `BlueprintReadWrite`。
- **Conflicts:** `EditAnywhere`、`EditDefaultsOnly`、`VisibleAnywhere`、`VisibleDefaultsOnly`、`VisibleInstanceOnly`。
- **Prefer instead:** 类默认值可编辑用 `EditDefaultsOnly`；两侧都可编辑用 `EditAnywhere`。

- **功能描述：** 只能在实例的细节面板上编辑该属性

- **元数据类型：** bool
- **引擎模块：** DetailsPanel, Editor
- **作用机制：** 在PropertyFlags中加入CPF_Edit, CPF_DisableEditOnTemplate
- **常用程度：** ★★★★★

一并参见EditAnywhere里的示例代码和效果。

## 行为

`EditInstanceOnly` 让属性只在实例 Details Panel 中可编辑，不允许在类默认值、Blueprint 默认值或 CDO 相关 Details Panel 中编辑。

适合用于“每个关卡实例单独配置，但默认模板不应设置”的属性，例如场景中放置对象的实例引用、实例位置相关参数或 per-instance 调试配置。

## UE5.8 审计结论

状态：`verified_UE5.8`

在 `D:/github/GitWorkspace/Hello/Source/Insider/Property/MyProperty_Test.h` 中，`MyInt_EditInstanceOnly` 的样例注释记录了以下核心 flags：

```text
CPF_Edit | CPF_DisableEditOnTemplate
```

`bat/build-hello.bat` 已在 UE5.8 下成功编译 `HelloEditor Win64 Development`，说明该样例可通过 UE5.8 UHT/编译流程。

UE5.8 源码 `C:/Program Files/Epic Games/UE_5.8/Engine/Source/Programs/Shared/EpicGames.UHT/Specifiers/UhtPropertyMemberSpecifiers.cs` 中，UHT 解析逻辑把 `EditInstanceOnly` 映射为 `Edit | DisableEditOnTemplate`，并且会拒绝同一个属性上出现多个 edit/visibility specifier。

## 常见误用

- 不要和 `EditAnywhere`、`EditDefaultsOnly`、`VisibleAnywhere`、`VisibleDefaultsOnly`、`VisibleInstanceOnly` 同时使用；edit/visibility 维度只能选择一个。
- `EditInstanceOnly` 不提供 Blueprint 访问能力；Blueprint 访问仍需 `BlueprintReadOnly` 或 `BlueprintReadWrite`。
- 如果属性应在 Blueprint 默认值里配置，不要用 `EditInstanceOnly`，应改用 `EditDefaultsOnly` 或 `EditAnywhere`。
