# IsAlwaysAccessible

功能描述: 指定UHT在生成文件的时候总是可以访问到改结构的声明，否则要在gen.cpp里生成镜像结构定义
元数据类型: bool
引擎模块: UHT
限制类型: 只在NoExportTypes.h供UHT使用
Status: Done
常用程度: 0

指定该结构的声明是否在UHT为NoExportTypes.h生成的gen.cpp里总是可以访问到。

换句话说其实就是是否这些结构在GeneratedCppIncludes.h的声明里可以找到。如果不可以找到，那在后面生成Z_Construct_UScriptStruct_FMatrix44d_Statics这种类似的时候就得再自己定义一个镜像结构定义。如果可以找到，比如FGuid，则就不需要。

因此这只是一个手动的内部标记，帮助UHT程序识别哪些结构要再创建镜像结构定义。

在NoExportTypes.h查看各个结构的时候，会发现有些结构（85/135）会标上IsAlwaysAccessible，而有些没有。这是因为UHT在为NoExportTypes.h生成gen.cpp的时候，

```cpp
\UnrealEngine\Engine\Source\Runtime\CoreUObject\Public\UObject\GeneratedCppIncludes.h
#include "UObject/Object.h"
#include "UObject/UObjectGlobals.h"
#include "UObject/CoreNative.h"
#include "UObject/Class.h"
#include "UObject/MetaData.h"
#include "UObject/UnrealType.h"
#include "UObject/EnumProperty.h"
#include "UObject/TextProperty.h"
#include "UObject/FieldPathProperty.h"

#if UE_ENABLE_INCLUDE_ORDER_DEPRECATED_IN_5_2
#include "CoreMinimal.h"
#endif

\Hello\Intermediate\Build\Win64\HelloEditor\Inc\CoreUObject\UHT\NoExportTypes.gen.cpp：
// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

//以下这两行
#include "UObject/GeneratedCppIncludes.h"//A
#include "UObject/NoExportTypes.h"//B
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeNoExportTypes() {}
```

在最开头的两个include里如果可以直接找到该struct的定义，则在gen.cpp中的A和B处需要结构定义的时候，就不需要再额外去找定义了。

```cpp
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FMatrix44f_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_CoreUObject,
		nullptr,
		nullptr,
		"Matrix44f",
		Z_Construct_UScriptStruct_FMatrix44f_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMatrix44f_Statics::PropPointers),
		sizeof(FMatrix44f),//这个A
		alignof(FMatrix44f),//这个B
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000038),
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMatrix44f_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FMatrix44f_Statics::Struct_MetaDataParams)
	};
```

如果找不到，比如FMatrix44f，是定义在Engine\Source\Runtime\Core\Public\Math\Matrix.h，则必须为它生成一个一模一样的定义（不include的作用是加快编译)：

```cpp
struct Z_Construct_UScriptStruct_FMatrix44f_Statics
	{
		struct FMatrix44f //内存布局一致的定义
		{
			FPlane4f XPlane;
			FPlane4f YPlane;
			FPlane4f ZPlane;
			FPlane4f WPlane;
		};

		static_assert(sizeof(FMatrix44f) < MAX_uint16);
		static_assert(alignof(FMatrix44f) < MAX_uint8);
```

当然如果子字段或者父类也找不到定义，则只需要把父定义先写在前面就可以了。因此cs里的FindNoExportStructsRecursive就是为了找到其相关的结构。没有标IsAlwaysAccessible则意味着要生成假的结构定义

```cpp
private static void FindNoExportStructsRecursive(List<UhtScriptStruct> outScriptStructs, UhtStruct structObj)
		{
			for (UhtStruct? current = structObj; current != null; current = current.SuperStruct)
			{
				// Is isn't true for noexport structs
				if (current is UhtScriptStruct scriptStruct)
				{
					if (scriptStruct.ScriptStructFlags.HasAnyFlags(EStructFlags.Native))
					{
						break;
					}

					// these are a special cases that already exists and if wrong if exported naively
					if (!scriptStruct.IsAlwaysAccessible)
					{
						outScriptStructs.Remove(scriptStruct);
						outScriptStructs.Add(scriptStruct);
					}
				}

				foreach (UhtType type in current.Children)
				{
					if (type is UhtProperty property)
					{
						foreach (UhtType referenceType in property.EnumerateReferencedTypes())
						{
							if (referenceType is UhtScriptStruct propertyScriptStruct)
							{
								FindNoExportStructsRecursive(outScriptStructs, propertyScriptStruct);
							}
						}
					}
				}
			}
		}
```