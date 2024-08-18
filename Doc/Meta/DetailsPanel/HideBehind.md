# HideBehind

功能描述: 只在指定的属性为true或不为空的时候本属性才显示
使用位置: UPROPERTY
Feature: Editor
引擎模块: DetailsPanel
元数据类型: string="abc"
限制类型: Foliage模块中
Status: OnlyInternal
常用程度: 1

```cpp
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Placement, meta=(UIMin = 0, ClampMin = 0, UIMax = 359, ClampMax = 359, HideBehind="AlignToNormal"))
	float AlignMaxAngle;
```

只在Foliage里用到，其实用EditCondition就可以达到同样的效果了。