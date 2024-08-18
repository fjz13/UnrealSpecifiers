# Intrinsic

功能描述: 指定UHT完全不为此类生成代码，需要自己手写。
引擎模块: UHT
元数据类型: bool
EClassFlagsOperation: |=
EClassFlags: CLASS_Intrinsic (../../Flags/EClassFlags/CLASS_Intrinsic.md)
Status: Done
常用程度: 0

指定UHT完全不为此类生成代码，需要自己手写。

只在C++直接设定，一般新类不设定这个，标记这个的都是UE4内部原生的那些类，相当于已经在源码中手写了元数据代码。

noexport至少还会解析生成元数据，只是缺少注册。因此instric类的所有元数据flags要自己手动标记。但是intrinsic完全不生成代码。其generated.h和.gen.cpp里面都是空的。noexporttyps.h里的目前采用intrinsic的类只有UCLASS(noexport, Intrinsic)class UModel{}，这还是被cpp不编译的。

```cpp
//UCLASS(Intrinsic)
//class INSIDER_API UMyClass_Intrinsic :public UObject	//syntax error: missing ';' before '<class-head>'
//{
//	GENERATED_BODY()
//
//};

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