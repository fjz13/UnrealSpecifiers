---
title: "InvalidEnumValues"
id: "meta.InvalidEnumValues"
kind: "meta"
symbol: "InvalidEnumValues"
scope: "InvalidEnumValues"
category: "Enum"
source_status: "imported_from_unreal_specifiers"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定枚举属性值上不可选的枚举值选项，用以排除一些选项"
usage: "UPROPERTY"
---

# InvalidEnumValues

- **功能描述：** 指定枚举属性值上不可选的枚举值选项，用以排除一些选项
- **使用位置：** UPROPERTY
- **引擎模块：** Enum Property
- **元数据类型：** strings="a，b，c"
- **限制类型：** 枚举属性值
- **关联项：** [ValidEnumValues](ValidEnumValues/ValidEnumValues.md)
- **常用程度：** ★★★

如果同时指定了InvalidEnumValues和ValidEnumValues，且里面的值有重叠，则还是以InvalidEnumValues的为准：这项枚举值就是非法的。