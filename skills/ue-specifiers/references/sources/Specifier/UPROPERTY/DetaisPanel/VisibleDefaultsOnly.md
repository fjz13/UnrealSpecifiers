---
title: "VisibleDefaultsOnly"
id: "UPROPERTY.VisibleDefaultsOnly"
kind: "specifier"
symbol: "VisibleDefaultsOnly"
scope: "UPROPERTY"
category: "DetailsPanel"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "在默认值细节面板可见，但不可编辑"
usage: "UPROPERTY / DetailsPanel"
---

# VisibleDefaultsOnly

- **功能描述：** 在默认值细节面板可见，但不可编辑
- **元数据类型：** bool
- **引擎模块：** DetailsPanel, Editor
- **作用机制：** 在PropertyFlags中加入CPF_Edit, CPF_DisableEditOnInstance
- **常用程度：** ★★★★★

一并参见EditAnywhere里的示例代码和效果。

## 行为

`VisibleDefaultsOnly` 让属性只在类默认值、Blueprint 默认值或 CDO 相关 Details Panel 中可见，但不可编辑；在实例 Details Panel 中禁用显示。

适合用于默认模板中需要展示但不允许手改的状态，例如由 C++ 构造的默认子对象引用、只读默认配置或由系统计算出的默认信息。

## UE5.8 审计结论

状态：`verified_UE5.8`

在 `D:/github/GitWorkspace/Hello/Source/Insider/Property/MyProperty_Test.h` 中，`MyInt_VisibleDefaultsOnly` 的样例注释记录了以下核心 flags：

```text
CPF_Edit | CPF_DisableEditOnInstance | CPF_EditConst
```

`bat/build-hello.bat` 已在 UE5.8 下成功编译 `HelloEditor Win64 Development`，说明该样例可通过 UE5.8 UHT/编译流程。

UE5.8 源码 `C:/Program Files/Epic Games/UE_5.8/Engine/Source/Programs/Shared/EpicGames.UHT/Specifiers/UhtPropertyMemberSpecifiers.cs` 中，UHT 解析逻辑把 `VisibleDefaultsOnly` 映射为 `Edit | EditConst | DisableEditOnInstance`，并且会拒绝同一个属性上出现多个 edit/visibility specifier。

## 常见误用

- 不要把 `VisibleDefaultsOnly` 当作“可编辑默认值”；它是可见但不可编辑。
- 不要和任何 `Edit*` 或其他 `Visible*` specifier 同时使用；edit/visibility 维度只能选择一个。
- 如果需要 Blueprint 读取，还需要额外添加 `BlueprintReadOnly`；Details Panel 可见性和 Blueprint 可见性是不同维度。
