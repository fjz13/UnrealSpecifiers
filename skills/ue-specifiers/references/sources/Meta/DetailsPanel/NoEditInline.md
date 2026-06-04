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
- 批次记录：`references/audits/ue5.8-p1-complete-pass.md`。

## 常见误用

参数名、属性名或目标宏写错导致 metadata 被保留但没有对应编辑器/Blueprint 行为。
