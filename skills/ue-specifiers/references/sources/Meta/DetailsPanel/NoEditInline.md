---
title: "NoEditInline"
id: "meta.NoEditInline"
kind: "meta"
symbol: "NoEditInline"
category: "DetailsPanel"
source_status: "imported_from_unreal_specifiers"
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