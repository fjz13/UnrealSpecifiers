---
title: "OptionalWidget"
id: "meta.OptionalWidget"
kind: "meta"
symbol: "OptionalWidget"
category: "Widget"
source_status: "verified_UE5.8"
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
- **关联项：** [BindWidget](BindWidget.md)
- **常用程度：** ★★★

必须配合BindWidget使用。

BindWidget+OptionalWidget=BindWidgetOptional
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。
