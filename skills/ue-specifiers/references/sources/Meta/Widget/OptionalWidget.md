---
title: "OptionalWidget"
id: "meta.OptionalWidget"
kind: "meta"
symbol: "OptionalWidget"
category: "Widget"
source_status: "imported_from_unreal_specifiers"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定在C++类中该Widget属性可以绑定到UMG的某个同名控件，也可以不绑定"
usage: "UPROPERTY"
---

# OptionalWidget

- **功能描述：** 指定在C++类中该Widget属性可以绑定到UMG的某个同名控件，也可以不绑定。
- **使用位置：** UPROPERTY
- **引擎模块：** Widget Property
- **元数据类型：** bool
- **限制类型：** UWidget子类里属性
- **关联项：** [BindWidget](BindWidget/BindWidget.md)
- **常用程度：** ★★★

必须配合BindWidget使用。

BindWidget+OptionalWidget=BindWidgetOptional