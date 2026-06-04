---
title: "HideBehind"
id: "meta.HideBehind"
kind: "meta"
symbol: "HideBehind"
category: "DetailsPanel"
source_status: "imported_from_unreal_specifiers"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "只在指定的属性为true或不为空的时候本属性才显示"
usage: "UPROPERTY"
---

# HideBehind

- **功能描述：** 只在指定的属性为true或不为空的时候本属性才显示
- **使用位置：** UPROPERTY
- **引擎模块：** DetailsPanel
- **元数据类型：** string="abc"
- **限制类型：** Foliage模块中
- **常用程度：** ★

```cpp
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Placement, meta=(UIMin = 0, ClampMin = 0, UIMax = 359, ClampMax = 359, HideBehind="AlignToNormal"))
	float AlignMaxAngle;
```

只在Foliage里用到，其实用EditCondition就可以达到同样的效果了。