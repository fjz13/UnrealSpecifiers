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