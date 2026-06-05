---
title: "MustBeLevelActor"
id: "meta.MustBeLevelActor"
kind: "meta"
symbol: "MustBeLevelActor"
category: "Object"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "意思是这个必须是场景里的Actor，而不是LevelScriptActor的意思"
usage: "UPROPERTY"
---

# MustBeLevelActor

## Decision Summary

- **Use when:** `MustBeLevelActor` metadata 的 `UPROPERTY` 场景需要：意思是这个必须是场景里的Actor，而不是LevelScriptActor的意思。
- **Do not use when:** 目标声明不属于 `UPROPERTY`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **使用位置：** UPROPERTY
- **引擎模块：** Object Property
- **元数据类型：** bool

意思是这个必须是场景里的Actor，而不是LevelScriptActor的意思。

触发时机在用箭头选择的当前选中actor的时候。
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。

## 源码中遇见：

```cpp
if (FObjectPropertyBase* ObjectProperty = CastField<FObjectPropertyBase>(Property))
{
	ObjectClass = ObjectProperty->PropertyClass;
	bMustBeLevelActor = ObjectProperty->GetOwnerProperty()->GetBoolMetaData(TEXT("MustBeLevelActor"));
	RequiredInterface = ObjectProperty->GetOwnerProperty()->GetClassMetaData(TEXT("MustImplement"));
}
```
