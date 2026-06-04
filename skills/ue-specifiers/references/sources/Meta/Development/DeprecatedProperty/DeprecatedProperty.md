---
title: "DeprecatedProperty"
id: "meta.DeprecatedProperty"
kind: "meta"
symbol: "DeprecatedProperty"
category: "Development"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "标记弃用，引用到该属性的蓝图会触发一个警告"
usage: "UPROPERTY"
---

# DeprecatedProperty

- **功能描述：** 标记弃用，引用到该属性的蓝图会触发一个警告

- **使用位置：** UPROPERTY

- **引擎模块：** Development

- **元数据类型：** bool

- **关联项：**

  UCLASS：[Deprecated](../../../Specifier/UCLASS/Development/Deprecated/Deprecated.md)

- **常用程度：** ★

标记弃用，引用到该属性的蓝图会触发一个警告

## 示例代码：

```cpp
// Simple
UPROPERTY(BlueprintReadWrite, meta=(DeprecatedProperty, DeprecationMessage="This is deprecated"))
FString PlantName;

// Better
UPROPERTY(BlueprintReadWrite, meta=(DisplayName="PlantName", DeprecatedProperty, DeprecationMessage="PlantName is deprecated, instead use PlantDisplayName."))
FString DEPRECATED_PlantName;
```


## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。
