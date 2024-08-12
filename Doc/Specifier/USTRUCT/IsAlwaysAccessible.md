# IsAlwaysAccessible

Type: bool
Feature: UHT
LimitedType: 只在NoExportTypes.h供UHT使用
Description: 指定UHT在生成文件的时候总是可以访问到改结构的声明，否则要在gen.cpp里生成镜像结构定义
Status: Done

"The 'IsAlwaysAccessible' struct specifier is only valid in the NoExportTypes.h file”

在NoExportTypes.h查看各个结构的时候，会发现有些结构（85/135）会标上IsAlwaysAccessible，而有些没有。这是因为UHT在为NoExportTypes.h生成gen.cpp的时候，

```cpp
{// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

//以下这两行
#include "UObject/GeneratedCppIncludes.h"
#include "UObject/NoExportTypes.h"
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