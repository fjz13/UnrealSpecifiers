---
title: "BlueprintInternalUseOnly"
id: "meta.BlueprintInternalUseOnly"
kind: "meta"
symbol: "BlueprintInternalUseOnly"
category: "Blueprint"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "标明该元素是作为蓝图系统的内部调用或使用，不暴露出来在用户层面直接定义或使用"
usage: "UFUNCTION, USTRUCT"
---

# BlueprintInternalUseOnly

- **功能描述：** 标明该元素是作为蓝图系统的内部调用或使用，不暴露出来在用户层面直接定义或使用。

- **使用位置：** UFUNCTION, USTRUCT

- **引擎模块：** Blueprint

- **元数据类型：** bool

- **关联项：**

  Meta：[BlueprintType](BlueprintType.md), [BlueprintInternalUseOnlyHierarchical](BlueprintInternalUseOnlyHierarchical.md)

  UFUNCTION：[BlueprintInternalUseOnly](../../Specifier/UFUNCTION/UHT/BlueprintInternalUseOnly.md)

  USTRUCT：[BlueprintInternalUseOnly](../../Specifier/USTRUCT/Blueprint/BlueprintInternalUseOnly.md)

- **常用程度：** ★★★

也可以用在USTRUCT上，标明该结构不可用来定义新BP变量，但可作为别的类的成员变量暴露和变量传递。

用在UFUNCTION上时：此函数是一个内部实现细节，用于实现另一个函数或节点。其从未直接在蓝图图表中公开。
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。
