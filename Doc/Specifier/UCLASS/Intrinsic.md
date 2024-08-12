# Intrinsic

Description: 只在C++直接设定，一般新类不设定这个，标记这个的都是UE4内部原生的那些类，相当于已经在源码中手写了元数据代码。
Feature: UHT
Type: bool
EClassFlagsOperation: |=
EClassFlags: CLASS_Intrinsic (../../Flags/EClassFlags/CLASS_Intrinsic.md)
Status: Done
Trait: Internal

指定UHT完全不生成代码。noexport至少还会解析生成元数据，只是缺少注册。因此instric类的所有元数据flags要自己手动标记。但是intrinsic完全不生成代码。其generated.h和.gen.cpp里面都是空的。noexporttyps.h里的

目前采用intrinsic的类只有UCLASS(noexport, Intrinsic)class UModel{}，这还是被cpp不编译的。

编译的错误：//syntax error: missing ';' before '<class-head>’

```cpp
//.h
class INSIDER_API UMyClass_Intrinsic :public UObject
{
	DECLARE_CLASS_INTRINSIC(UMyClass_Intrinsic, UObject, CLASS_MatchedSerializers, TEXT("/Script/Insider"))
};
//.cpp
IMPLEMENT_INTRINSIC_CLASS(UMyClass_Intrinsic, INSIDER_API, UObject, INSIDER_API, "/Script/Insider", {})

class COREUOBJECT_API UInterface : public UObject
{
	DECLARE_CLASS_INTRINSIC(UInterface, UObject, CLASS_Interface | CLASS_Abstract, TEXT("/Script/CoreUObject"))
};
```