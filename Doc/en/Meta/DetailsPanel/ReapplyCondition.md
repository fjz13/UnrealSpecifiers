# ReapplyCondition

- **Function Description:** // Properties with a ReapplyCondition should be disabled and hidden behind the specified property when in reapply mode
- **Usage Location:** UPROPERTY
- **Engine Module:** DetailsPanel
- **Metadata Type:** string = "abc"
- **Commonly Used:** ★

## Code:

```cpp
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Placement, meta=(UIMin = 0, ClampMin = 0, UIMax = 359, ClampMax = 359, ReapplyCondition="ReapplyRandomPitchAngle"))
	float RandomPitchAngle;
```

Also used exclusively within Foliage.