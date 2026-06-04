---
title: "NonTransient"
id: "UCLASS.NonTransient"
kind: "specifier"
symbol: "NonTransient"
scope: "UCLASS"
category: "Serialization"
source_status: "imported_from_unreal_specifiers"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "使继承自基类的Transient说明符无效"
usage: "UCLASS / Serialization"
---

# NonTransient

- **功能描述：** 使继承自基类的Transient说明符无效。
- **引擎模块：** Serialization
- **元数据类型：** bool
- **作用机制：** 在ClassFlags中移除[CLASS_Transient](../../../Flags/EClassFlags/CLASS_Transient.md)
- **关联项：** [Transient](Transient/Transient.md)
- **常用程度：** ★★★