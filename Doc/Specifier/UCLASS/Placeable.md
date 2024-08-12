# Placeable

Description: 指示可在编辑器中创建此类，而且可将此类放置到关卡、UI场景或蓝图（取决于类类型）中。此标志会传播到所有子类；子类可使用NotPlaceable说明符覆盖此标志。
Feature: Behavior
Type: bool
EClassFlagsOperation: &=~
EClassFlags: CLASS_NotPlaceable (../../Flags/EClassFlags/CLASS_NotPlaceable.md)
Status: Done

标明该类可以放置在关卡里。这个理论上可以覆盖掉基类的CLASS_NotPlaceable，从而变成可放置的。

源码里目前没有用到Placeable的地方，因为默认是placeable的。

placeable当前没法清除父类的notplaceable标记。

```cpp
UCLASS(Blueprintable, BlueprintType,placeable)	
class INSIDER_API AMyActor_Placeable :public AMyActor_NotPlaceable
{
	GENERATED_BODY()
};
error : The 'placeable' specifier cannot override a 'nonplaceable' base class. Classes are assumed to be placeable by default. Consider whether using the 'abstract' specifier on the base class would work.
```

![Untitled](Placeable/Untitled.png)