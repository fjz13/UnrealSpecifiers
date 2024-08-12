# ReapplyCondition

Usage: UPROPERTY
Feature: Editor
Type: string="abc"
Description: // Properties that have a ReapplyCondition should be disabled behind the specified property when in reapply mode
Status: OnlyInternal
Group: DetailsPanel

代码

```cpp
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Placement, meta=(UIMin = 0, ClampMin = 0, UIMax = 359, ClampMax = 359, ReapplyCondition="ReapplyRandomPitchAngle"))
	float RandomPitchAngle;
```

也只在Foliage中用到。