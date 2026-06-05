---
title: "NoEditInline"
id: "meta.NoEditInline"
kind: "meta"
symbol: "NoEditInline"
category: "DetailsPanel"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "Object properties pointing to an UObject instance whos class is marked editinline will not show their properties inli..."
usage: "UPROPERTY"
---

# NoEditInline

## Decision Summary

- **Use when:** `NoEditInline` metadata 的 `UPROPERTY` 场景需要：Object properties pointing to an UObject instance whos class is marked editinline will not show their properties inli...。
- **Do not use when:** 目标声明不属于 `UPROPERTY`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** Object properties pointing to an UObject instance whos class is marked editinline will not show their properties inline in property windows. Useful for getting actor components to appear in the component tree but not inline in the root actor details panel.
- **使用位置：** UPROPERTY
- **元数据类型：** bool
- **限制类型：** UObject*
- **关联项：** EditInline (EditInline.md)

对象引用默认就不能EditInline，因此也不需要额外再加上这个。除非Instanced之后？

结构属性默认就可以EditInline，加上这个后也没有作用，因此也不需要加上这个。

在源码中只找到：

```cpp
	UPROPERTY(VisibleAnywhere, Category = "Connection Point", meta = (NoEditInline))
	FLinearColor Color = FLinearColor::Black;
```

## 行为

UE5.8 property metadata；ObjectMacros 标注为 editinline object property 不在 Details 内联展开。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `ObjectMacros.h` property/class metadata declaration/comment
  - UE5.8 `PropertyEditor` Details metadata usage

## 常见误用

参数名、属性名或目标宏写错导致 metadata 被保留但没有对应编辑器/Blueprint 行为。
