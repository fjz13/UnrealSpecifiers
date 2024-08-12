# 不写UCLASS()

Type: bool
Feature: Trait
Description: 什么都不填写的默认值
EClassFlagsOperation: |=
EClassFlags: CLASS_MatchedSerializers (../../Flags/EClassFlags/CLASS_MatchedSerializers.md), CLASS_Native (../../Flags/EClassFlags/CLASS_Native.md), CLASS_TokenStreamAssembled (../../Flags/EClassFlags/CLASS_TokenStreamAssembled.md), CLASS_Intrinsic (../../Flags/EClassFlags/CLASS_Intrinsic.md), CLASS_Constructed (../../Flags/EClassFlags/CLASS_Constructed.md), CLASS_Abstract (../../Flags/EClassFlags/CLASS_Abstract.md)
Status: Done

```cpp
class INSIDER_API UMyClass_NoUCLASS :public UObject
{
	
};
```

默认的标记是：CLASS_Abstract | CLASS_MatchedSerializers | CLASS_Native | CLASS_TokenStreamAssembled | CLASS_Intrinsic | CLASS_Constructed。因此不能被NewObject生成对象。在手动去掉CLASS_Abstract后可以正常new，但是对象的名称依然是Object，显然是缺失了一些元数据信息。这些信息是在gen.cpp里UHT生成填充进去的。因为UHT不参加了，因此无法生成这些信息。