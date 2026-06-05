---
title: "EnumDisplayNameFn"
id: "meta.EnumDisplayNameFn"
kind: "meta"
symbol: "EnumDisplayNameFn"
scope: "EnumDisplayNameFn"
category: "Enum"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "在Runtime下为枚举字段提供自定义名称的函数回调"
usage: "UENUM"
---

# EnumDisplayNameFn

## Decision Summary

- **Use when:** `EnumDisplayNameFn` metadata 的 `UENUM` 场景需要：在Runtime下为枚举字段提供自定义名称的函数回调。
- **Do not use when:** 目标声明不属于 `UENUM`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 在Runtime下为枚举字段提供自定义名称的函数回调
- **使用位置：** UENUM
- **引擎模块：** Enum Property
- **元数据类型：** string="abc"
- **常用程度：** ★★

只在Runtime下生效，在Editor下依然不起作用。
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。

## 测试代码：

```cpp
//[EMyEnum_CustomDisplay	Enum->Field->Object	/Script/Insider.EMyEnum_CustomDisplay]
//(BlueprintType = true, EnumDisplayNameFn = GetMyEnumCustomDisplayName, First.Name = EMyEnum_CustomDisplay::First, IsBlueprintBase = true, ModuleRelativePath = Enum/MyEnum_Test.h, Second.Name = EMyEnum_CustomDisplay::Second, Third.Name = EMyEnum_CustomDisplay::Third)
//	ObjectFlags:	RF_Public | RF_Transient
//	Outer:	Package /Script/Insider
//	EnumFlags:	EEnumFlags::None
//	EnumDisplayNameFn:	6adb4804
//	CppType:	EMyEnum_CustomDisplay
//	CppForm:	EnumClass
//{
//	First = 0,
//	Second = 1,
//	Third = 2,
//	EMyEnum_MAX = 3
//};

UENUM(Blueprintable, meta = (EnumDisplayNameFn = "GetMyEnumCustomDisplayName"))
enum class EMyEnum_CustomDisplay :uint8
{
	First,
	Second,
	Third,
};

extern FText GetMyEnumCustomDisplayName(int32 val);

FText GetMyEnumCustomDisplayName(int32 val)
{
	EMyEnum_CustomDisplay enumValue = (EMyEnum_CustomDisplay)val;
	switch (enumValue)
	{
	case EMyEnum_CustomDisplay::First:
		return FText::FromString(TEXT("My_First"));
	case EMyEnum_CustomDisplay::Second:
		return FText::FromString(TEXT("My_Second"));
	case EMyEnum_CustomDisplay::Third:
		return FText::FromString(TEXT("My_Third"));
	default:
		return FText::FromString(TEXT("Invalid MyEnum"));
	}
}
```

## 测试蓝图：


EnumDisplayNameFn 的函数设置是在gen.cpp中完成的，因此并不需要成为UFUNCTION。

```cpp
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_Insider_EMyEnum_CustomDisplay_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_Insider,
	GetMyEnumCustomDisplayName,             //这里！！！
	"EMyEnum_CustomDisplay",
	"EMyEnum_CustomDisplay",
	Z_Construct_UEnum_Insider_EMyEnum_CustomDisplay_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_Insider_EMyEnum_CustomDisplay_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_Insider_EMyEnum_CustomDisplay_Statics::Enum_MetaDataParams), Z_Construct_UEnum_Insider_EMyEnum_CustomDisplay_Statics::Enum_MetaDataParams)
};
```

## 原理代码：

```cpp

/FText UEnum::GetDisplayNameTextByIndex(int32 NameIndex) const
{
	FString RawName = GetNameStringByIndex(NameIndex);

	if (RawName.IsEmpty())
	{
		return FText::GetEmpty();
	}

#if WITH_EDITOR
	FText LocalizedDisplayName;
	// In the editor, use metadata and localization to look up names
	static const FString Namespace = TEXT("UObjectDisplayNames");
	const FString Key = GetFullGroupName(false) + TEXT(".") + RawName;

	FString NativeDisplayName;
	if (HasMetaData(TEXT("DisplayName"), NameIndex))
	{
		NativeDisplayName = GetMetaData(TEXT("DisplayName"), NameIndex);
	}
	else
	{
		NativeDisplayName = FName::NameToDisplayString(RawName, false);
	}

	if (!(FText::FindText(Namespace, Key, /*OUT*/LocalizedDisplayName, &NativeDisplayName)))
	{
		LocalizedDisplayName = FText::FromString(NativeDisplayName);
	}

	if (!LocalizedDisplayName.IsEmpty())
	{
		return LocalizedDisplayName;
	}
#endif
	//Runtime下到这里
	if (EnumDisplayNameFn)
	{
		return (*EnumDisplayNameFn)(NameIndex);
	}

	return FText::FromString(GetNameStringByIndex(NameIndex));
}
```
