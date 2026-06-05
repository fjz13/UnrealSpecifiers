---
title: "EditDefaultsOnly"
id: "UPROPERTY.EditDefaultsOnly"
kind: "specifier"
symbol: "EditDefaultsOnly"
scope: "UPROPERTY"
category: "DetailsPanel"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "只能在默认值面板里编辑"
usage: "UPROPERTY / DetailsPanel"
---

# EditDefaultsOnly

## Decision Summary

- **Use when:** 属性只应在 CDO、蓝图类默认值或 archetype 默认值中编辑。
- **Do not use when:** 放到关卡里的单个实例也需要改值。
- **Requires:** 需要 Blueprint 访问时另加 `BlueprintReadOnly` 或 `BlueprintReadWrite`。
- **Conflicts:** `EditAnywhere`、`EditInstanceOnly`、`VisibleAnywhere`、`VisibleDefaultsOnly`、`VisibleInstanceOnly`。
- **Prefer instead:** 默认值和实例都可编辑用 `EditAnywhere`；只改实例用 `EditInstanceOnly`。

- **功能描述：** 只能在默认值面板里编辑
- **元数据类型：** bool
- **引擎模块：** DetailsPanel, Editor
- **作用机制：** 在PropertyFlags中加入CPF_Edit, CPF_DisableEditOnInstance
- **常用程度：** ★★★★★

一并参见EditAnywhere里的示例代码和效果。

## 行为

`EditDefaultsOnly` 让属性只在类默认值、Blueprint 默认值或 CDO 相关 Details Panel 中可编辑，不允许在关卡实例 Details Panel 中编辑。

适合用于“设计阶段配置一次，实例不应单独覆盖”的属性，例如资产默认参数、类级别调优参数、默认组件配置等。

## UE5.8 审计结论

状态：`verified_UE5.8`

在 `D:/github/GitWorkspace/Hello/Source/Insider/Property/MyProperty_Test.h` 中，`MyInt_EditDefaultsOnly` 的样例注释记录了以下核心 flags：

```text
CPF_Edit | CPF_DisableEditOnInstance
```

`bat/build-hello.bat` 已在 UE5.8 下成功编译 `HelloEditor Win64 Development`，说明该样例可通过 UE5.8 UHT/编译流程。

UE5.8 源码 `C:/Program Files/Epic Games/UE_5.8/Engine/Source/Programs/Shared/EpicGames.UHT/Specifiers/UhtPropertyMemberSpecifiers.cs` 中，UHT 解析逻辑把 `EditDefaultsOnly` 映射为 `Edit | DisableEditOnInstance`，并且会拒绝同一个属性上出现多个 edit/visibility specifier。

## 常见误用

- 不要和 `EditAnywhere`、`EditInstanceOnly`、`VisibleAnywhere`、`VisibleDefaultsOnly`、`VisibleInstanceOnly` 同时使用；edit/visibility 维度只能选择一个。
- `EditDefaultsOnly` 只控制 Details Panel 编辑权限，不等于 Blueprint 可读写；Blueprint 访问仍需 `BlueprintReadOnly` 或 `BlueprintReadWrite`。
- 如果需要实例可编辑，应使用 `EditInstanceOnly` 或 `EditAnywhere`。
