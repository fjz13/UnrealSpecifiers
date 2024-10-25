# HideBehind

- **Function Description:** This attribute is only displayed when the specified attribute is true or not null
- **Usage Location:** UPROPERTY
- **Engine Module:** DetailsPanel
- **Metadata Type:** string="abc"
- **Restriction Type:** Within the Foliage module
- **Commonality:** ★

```cpp
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Placement, meta=(UIMin = 0, ClampMin = 0, UIMax = 359, ClampMax = 359, HideBehind="AlignToNormal"))
	float AlignMaxAngle;
```

Exclusive to the Foliage module, the same effect can actually be achieved using EditCondition.