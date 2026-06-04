---
title: "ReapplyCondition"
id: "meta.ReapplyCondition"
kind: "meta"
symbol: "ReapplyCondition"
category: "DetailsPanel"
source_status: "verified_UE5.8"
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

## 行为

UE5.8 details metadata；Details customization 用于条件重新应用。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `ObjectMacros.h` property/class metadata declaration/comment
  - UE5.8 `PropertyEditor` Details metadata usage

## 常见误用

参数名、属性名或目标宏写错导致 metadata 被保留但没有对应编辑器/Blueprint 行为。
