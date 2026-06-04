---
title: "EditorConfig"
id: "meta.EditorConfig"
kind: "meta"
symbol: "EditorConfig"
category: "Config"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "保存编辑器的配置"
usage: "UCLASS"
---

# EditorConfig

- **功能描述：** 保存编辑器的配置

- **使用位置：** UCLASS

- **引擎模块：** Config

- **元数据类型：** string="abc"

- **关联项：**

  UCLASS：[EditorConfig](../../Specifier/UCLASS/Config/EditorConfig.md)

- **常用程度：** ★★★

## 行为

UE5.8 class/config metadata；由 UCLASS `EditorConfig` 写入，用于 editor config 上下文。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `ObjectMacros.h` config property metadata declaration/comment
  - UE5.8 `SettingsEditor`/`DeveloperSettings` metadata usage

## 常见误用

参数名、属性名或目标宏写错导致 metadata 被保留但没有对应编辑器/Blueprint 行为。
