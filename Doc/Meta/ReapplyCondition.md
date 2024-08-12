# ReapplyCondition

Description: // Properties that have a ReapplyCondition should be disabled behind the specified property when in reapply mode
Usage: UPROPERTY
Feature: Editor
Group: DetailsPanel
Type: string="abc"
Status: OnlyInternal

代码

```cpp
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Placement, meta=(UIMin = 0, ClampMin = 0, UIMax = 359, ClampMax = 359, ReapplyCondition="ReapplyRandomPitchAngle"))
	float RandomPitchAngle;
```

也只在Foliage中用到。