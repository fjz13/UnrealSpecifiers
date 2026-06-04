---
title: "GetRestrictedEnumValues"
id: "meta.GetRestrictedEnumValues"
kind: "meta"
symbol: "GetRestrictedEnumValues"
scope: "GetRestrictedEnumValues"
category: "Enum"
source_status: "imported_from_unreal_specifiers"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定一个函数来指定枚举属性值的哪些枚举选项是禁用的"
usage: "UPROPERTY"
---

# GetRestrictedEnumValues

- **功能描述：** 指定一个函数来指定枚举属性值的哪些枚举选项是禁用的
- **使用位置：** UPROPERTY
- **引擎模块：** Enum Property
- **元数据类型：** string="abc"
- **限制类型：** TArray<FString> FuncName() const;
- **关联项：** [ValidEnumValues](ValidEnumValues/ValidEnumValues.md)
- **常用程度：** ★★★

Restricted和Invalid的区别是：

Invalid会隐藏掉该选项值

Restricted依然会显示该选项值，只是会灰调不可选。

指定的函数名字必须是一个UFUNCTION函数，这样才能通过名字找到该函数。