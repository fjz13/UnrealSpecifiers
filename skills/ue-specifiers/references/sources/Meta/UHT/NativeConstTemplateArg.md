---
title: "NativeConstTemplateArg"
id: "meta.NativeConstTemplateArg"
kind: "meta"
symbol: "NativeConstTemplateArg"
category: "UHT"
source_status: "imported_from_unreal_specifiers"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定该属性是一个const的模板参数"
usage: "UPROPERTY"
---

# NativeConstTemplateArg

- **功能描述：** 指定该属性是一个const的模板参数。
- **使用位置：** UPROPERTY
- **引擎模块：** UHT
- **元数据类型：** bool
- **常用程度：** 0

指定该属性是一个const的模板参数。

在源码里并没有找到使用的地方。只有在UHT中用到。

在UHT中查看主要是UhtArrayProperty和UhtObjectPropertyBase，UhtOptionalProperty。