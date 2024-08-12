# UCLASS()

Description: 什么都不填写的默认值
Feature: Trait
Type: bool
EClassFlagsOperation: |=
EClassFlags: CLASS_MatchedSerializers (../../Flags/EClassFlags/CLASS_MatchedSerializers.md), CLASS_Native (../../Flags/EClassFlags/CLASS_Native.md), CLASS_RequiredAPI (../../Flags/EClassFlags/CLASS_RequiredAPI.md), CLASS_TokenStreamAssembled (../../Flags/EClassFlags/CLASS_TokenStreamAssembled.md), CLASS_Intrinsic (../../Flags/EClassFlags/CLASS_Intrinsic.md), CLASS_Constructed (../../Flags/EClassFlags/CLASS_Constructed.md)
Status: Done

```cpp
UCLASS()
class INSIDER_API UMyClass_Default :public UObject
{
		GENERATED_BODY()
};
```

不能在蓝图中被继承，不能在蓝图中定义变量。

默认是都没有，但依然都可以通过蓝图ConstructObject创建出来。对于想要拥有反射功能，但是并不想在蓝图中被使用会挺适合。默认的拥有这些标志：CLASS_MatchedSerializers | CLASS_Native | CLASS_RequiredAPI | CLASS_TokenStreamAssembled | CLASS_Intrinsic | CLASS_Constructed