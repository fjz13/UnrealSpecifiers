# NoExport

Description: 不会为该类创建自动生成代码，只用来给UHT提供解析定义。
Type: bool
Feature: UHT
Example: E:\P4V\Engine\Source\Runtime\CoreUObject\Public\UObject\NoExportTypes.h里定义了很多，还有用!CPP包起来的。所以基本上都是只用来给UHT分析的作用
Status: Done

指定UHT不要用来自动生成注册的代码，而只是进行词法分析提取元数据。定义的结构常常用宏包起来以不在C++中应用。实际上应用可以只要保持C++中内存布局一样，就可以自己多定义。使用场景：想自己定义一个UHT头喂给UHT分析，然后自己在别处定义实际的C++。一种典型用途是C++里的实际多个类继承于一个模板基类，如FVector2MaterialInput，这样可以每个特化子类定一个UHT类型别名。另一种目的是把UHT要分析的头文件都放在一个文件里，加速UHT分析生成，不用分析多个文件，反正只要UHT信息和内存布局对就行。

```cpp
#if !CPP	// begin noexport class
USTRUCT(noexport, BlueprintType) //如果不写noexport，会报错：Expected a GENERATED_BODY() at the start of the struct、
struct FFloatRK4SpringInterpolator
{
	
	UPROPERTY(EditAnywhere, Category = "FloatRK4SpringInterpolator")
	float StiffnessConstant;

	/** 0 = Undamped, <1 = Underdamped, 1 = Critically damped, >1 = Over damped */
	UPROPERTY(EditAnywhere, Category = "FloatRK4SpringInterpolator")
	float DampeningRatio;

	bool bIsInitialized;
	bool bIsInMotion;
	float TimeRemaining;
	FRK4SpringConstants SpringConstants;

	float LastPosition;
	RK4Integrator::FRK4State<float> State;
};
#endif	// end noexport class

//实际应用：
template <typename T>
struct FRK4SpringInterpolator
{
protected:
	float StiffnessConstant;
	float DampeningRatio;

	bool bIsInitialized;
	bool bIsInMotion;
	float TimeRemaining;
	FRK4SpringConstants SpringConstants;

	T LastPosition;
	RK4Integrator::FRK4State<T> State;
}

struct FFloatRK4SpringInterpolator : FRK4SpringInterpolator<float>
struct FVectorRK4SpringInterpolator : FRK4SpringInterpolator<FVector>
```

不生成的代码包括：

```cpp
USTRUCT(BlueprintType,noexport)
struct INSIDER_API FMyStruct_NoExport
{
	//抑制：GENERATED_BODY()解释生成的：
	//static class UScriptStruct* StaticStruct();	

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Score;
};

//抑制：
//template<> INSIDER_API UScriptStruct* StaticStruct<struct FMyStruct_NoExport>();
```

 .h里不会生成，因此不会在别的模块里使用

```cpp
template<> INSIDER_API UScriptStruct* StaticStruct<struct FMyStruct_NoExport>();
```

但是依然会在Module.init.gen.cpp里生成Z_Construct_UScriptStruct_FMyStruct_NoExport的调用，因此还是会在蓝图里暴露出来。

```cpp
#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeInsider_init() {}
	INSIDER_API UScriptStruct* Z_Construct_UScriptStruct_FMyStruct_NoExport();
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_Insider;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_Insider()
	{
		if (!Z_Registration_Info_UPackage__Script_Insider.OuterSingleton)
		{
			static UObject* (*const SingletonFuncArray[])() = {
					(UObject* (*)())Z_Construct_UScriptStruct_FMyStruct_NoExport,//这里注入调用
			};
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/Insider",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0x02A7B98C,
				0xFA17C3C4,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_Insider.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_Insider.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_Insider(Z_Construct_UPackage__Script_Insider, TEXT("/Script/Insider"), Z_Registration_Info_UPackage__Script_Insider, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x02A7B98C, 0xFA17C3C4));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
```

![Untitled](NoExport/Untitled.png)

![Untitled](NoExport/Untitled%201.png)

加上noexport的区别是不能用StaticStruct和没了TCppStructOps，不能做一些优化。其他还是可以正常使用，就像FVector一样。

缺失的代码，也可以通过手动添加代码来获得。

```cpp
USTRUCT(BlueprintType,noexport)
struct INSIDER_API FMyStruct_NoExport
{
	//GENERATED_BODY()	//missing type specifier - int assumed，..generated.h里只是定一个StaticStruct()函数

	static class UScriptStruct* StaticStruct();	//可以自己定义

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Score;

};

template<> INSIDER_API UScriptStruct* StaticStruct<struct FMyStruct_NoExport>();//可以自己定义

//.cpp
//链入函数声明，在其他的cpp里已经有实现，所以可以正常调用到
INSIDER_API UScriptStruct* Z_Construct_UScriptStruct_FMyStruct_NoExport();
UPackage* Z_Construct_UPackage__Script_Insider();

static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_MyStruct_NoExport;

class UScriptStruct* FMyStruct_NoExport::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_MyStruct_NoExport.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_MyStruct_NoExport.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FMyStruct_NoExport, Z_Construct_UPackage__Script_Insider(), TEXT("MyStruct_NoExport"));
	}
	return Z_Registration_Info_UScriptStruct_MyStruct_NoExport.OuterSingleton;
}

template<> INSIDER_API UScriptStruct* StaticStruct<FMyStruct_NoExport>()
{
	return FMyStruct_NoExport::StaticStruct();
}
```