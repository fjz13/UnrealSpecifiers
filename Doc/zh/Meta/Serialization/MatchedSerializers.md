---
title: "MatchedSerializers"
id: "meta.MatchedSerializers"
kind: "meta"
symbol: "MatchedSerializers"
category: "Serialization"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "只在NoExportTypes.h中使用，标明采用结构序列化器。是否支持文本导入导出"
usage: "UCLASS"
---

# MatchedSerializers

- **功能描述：** 只在NoExportTypes.h中使用，标明采用结构序列化器。是否支持文本导入导出

- **使用位置：** UCLASS

- **引擎模块：** Serialization

- **元数据类型：** bool

- **关联项：**

  UCLASS：[MatchedSerializers](../../Specifier/UCLASS/Serialization/MatchedSerializers/MatchedSerializers.md)

- **常用程度：** 0

```cpp
if (!GetUnrealSourceFile().IsNoExportTypes())
{
	LogError(TEXT("The 'MatchedSerializers' class specifier is only valid in the NoExportTypes.h file"));
}
ParsedClassFlags |= CLASS_MatchedSerializers;
```

跟在Class中标记MatchedSerializers是等价的
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。
