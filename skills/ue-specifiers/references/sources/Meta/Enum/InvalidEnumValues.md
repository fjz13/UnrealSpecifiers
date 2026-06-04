---
title: "InvalidEnumValues"
id: "meta.InvalidEnumValues"
kind: "meta"
symbol: "InvalidEnumValues"
scope: "InvalidEnumValues"
category: "Enum"
source_status: "verified_UE5.8"
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
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。
