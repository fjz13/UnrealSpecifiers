---
title: "BlueprintInternalUseOnlyHierarchical"
id: "meta.BlueprintInternalUseOnlyHierarchical"
kind: "meta"
symbol: "BlueprintInternalUseOnlyHierarchical"
category: "Blueprint"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "标明该结构及其子类都不暴露给用户定义和使用，均只能在蓝图系统内部使用"
usage: "USTRUCT"
---

# BlueprintInternalUseOnlyHierarchical

- **功能描述：** 标明该结构及其子类都不暴露给用户定义和使用，均只能在蓝图系统内部使用

- **使用位置：** USTRUCT

- **引擎模块：** Blueprint

- **元数据类型：** bool

- **关联项：**

  Meta：[BlueprintInternalUseOnly](BlueprintInternalUseOnly.md), [BlueprintType](BlueprintType.md)

  USTRUCT：[BlueprintInternalUseOnlyHierarchical ](../../Specifier/USTRUCT/Blueprint/BlueprintInternalUseOnlyHierarchical.md)

- **常用程度：** ★

指明一个不向最终用户公开的BlueprintType类型的结构以及其派生的结构。
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。
