---
title: "DisallowedStructs"
id: "meta.DisallowedStructs"
kind: "meta"
symbol: "DisallowedStructs"
category: "TypePicker"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "只在SmartObject模块中应用，用以在类选择器中排除掉某个类以及子类"
usage: "UPROPERTY"
---

# DisallowedStructs

## Decision Summary

- **Use when:** `DisallowedStructs` metadata 的 `UPROPERTY` 场景需要：只在SmartObject模块中应用，用以在类选择器中排除掉某个类以及子类。
- **Do not use when:** 目标声明不属于 `UPROPERTY`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 只在SmartObject模块中应用，用以在类选择器中排除掉某个类以及子类。
- **使用位置：** UPROPERTY
- **引擎模块：** TypePicker
- **元数据类型：** string="abc"
- **常用程度：** ★

只在SmartObject模块中应用，用以在类选择器中排除掉某个类以及子类。

## 源码：

```cpp
UPROPERTY(EditDefaultsOnly, Category = "SmartObject", meta=(DisallowedStructs="/Script/SmartObjectsModule.SmartObjectSlotAnnotation"))
TArray<FSmartObjectDefinitionDataProxy> DefinitionData;
```
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。
