---
title: "FullyExpand"
id: "meta.FullyExpand"
kind: "meta"
symbol: "FullyExpand"
category: "Object"
source_status: "imported_from_unreal_specifiers"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "但是没有发现该Meta被使用的原理代码"
usage: "UPROPERTY"
---

# FullyExpand

- **使用位置：** UPROPERTY
- **元数据类型：** bool
- **关联项：** [ShowInnerProperties](ShowInnerProperties/ShowInnerProperties.md)

但是没有发现该Meta被使用的原理代码。

在源码中搜索发现有多处应用，但实际上没有原理代码。

```cpp
	/** The options that are available on the node. */
	UPROPERTY(EditAnywhere, Instanced, Category = "Options", meta=(ShowInnerProperties, FullyExpand="true"))
	TObjectPtr<UMovieGraphValueContainer> SelectOptions;

	/** The currently selected option. */
	UPROPERTY(EditAnywhere, Instanced, Category = "Options", meta=(ShowInnerProperties, FullyExpand="true"))
	TObjectPtr<UMovieGraphValueContainer> SelectedOption;
```