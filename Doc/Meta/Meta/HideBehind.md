# HideBehind

Usage: UPROPERTY
Feature: Editor
Type: string="abc"
Description: 只在指定的属性为true或不为空的时候本属性才显示
LimitedType: Foliage模块中
Status: OnlyInternal
Group: DetailsPanel

```cpp
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Placement, meta=(UIMin = 0, ClampMin = 0, UIMax = 359, ClampMax = 359, HideBehind="AlignToNormal"))
	float AlignMaxAngle;
```

只在Foliage里用到，其实用EditCondition就可以达到同样的效果了。