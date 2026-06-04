---
title: "NativeConstTemplateArg"
id: "meta.NativeConstTemplateArg"
kind: "meta"
symbol: "NativeConstTemplateArg"
category: "UHT"
source_status: "verified_UE5.8"
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
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。
