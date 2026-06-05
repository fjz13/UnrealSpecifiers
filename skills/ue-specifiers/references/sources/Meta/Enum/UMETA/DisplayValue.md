---
title: "DisplayValue"
id: "meta.DisplayValue"
kind: "meta"
symbol: "DisplayValue"
scope: "UMETA"
category: "Enum"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "Enum /Script/Engine.AnimPhysCollisionType"
usage: "UENUM::UMETA"
---

# DisplayValue

## Decision Summary

- **Use when:** `DisplayValue` metadata 的 `UENUM::UMETA` 场景需要：Enum /Script/Engine.AnimPhysCollisionType。
- **Do not use when:** 目标声明不属于 `UENUM::UMETA`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** Enum /Script/Engine.AnimPhysCollisionType
- **使用位置：** UENUM::UMETA
- **引擎模块：** Enum Property
- **常用程度：** 0
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。

## 源码例子：

```cpp
UENUM()
enum class AnimPhysCollisionType : uint8
{
	CoM UMETA(DisplayName="CoM", DisplayValue="CoM", ToolTip="Only limit the center of mass from crossing planes."),
	CustomSphere UMETA(ToolTip="Use the specified sphere radius to collide with planes."),
	InnerSphere UMETA(ToolTip="Use the largest sphere that fits entirely within the body extents to collide with planes."),
	OuterSphere UMETA(ToolTip="Use the smallest sphere that wholely contains the body extents to collide with planes.")
};
```
