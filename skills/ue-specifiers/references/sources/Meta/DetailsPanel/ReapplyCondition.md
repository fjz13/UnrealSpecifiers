---
title: "ReapplyCondition"
id: "meta.ReapplyCondition"
kind: "meta"
symbol: "ReapplyCondition"
category: "DetailsPanel"
source_status: "imported_from_unreal_specifiers"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "// Properties that have a ReapplyCondition should be disabled behind the specified property when in reapply mode"
usage: "UPROPERTY"
---

# ReapplyCondition

- **功能描述：** // Properties that have a ReapplyCondition should be disabled behind the specified property when in reapply mode
- **使用位置：** UPROPERTY
- **引擎模块：** DetailsPanel
- **元数据类型：** string="abc"
- **常用程度：** ★

## 代码：

```cpp
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Placement, meta=(UIMin = 0, ClampMin = 0, UIMax = 359, ClampMax = 359, ReapplyCondition="ReapplyRandomPitchAngle"))
	float RandomPitchAngle;
```

也只在Foliage中用到。