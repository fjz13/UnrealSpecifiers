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

## Decision Summary

- **Use when:** `DeprecatedProperty` metadata 的 `UPROPERTY` 场景需要：标记弃用，引用到该属性的蓝图会触发一个警告。
- **Do not use when:** 目标声明不属于 `UPROPERTY`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** 用在 `UPROPERTY`，通常配合 `DeprecationMessage`；C++ 编译警告仍需 `UE_DEPRECATED`。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 标记弃用，引用到该属性的蓝图会触发一个警告

- **使用位置：** UPROPERTY

- **引擎模块：** Development

- **元数据类型：** bool

- **关联项：**

  UCLASS：[Deprecated](../../Specifier/UCLASS/Development/Deprecated.md)

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
