# EnumDisplayNameFn

Description: 在Runtime下为枚举字段提供自定义名称的函数回调
Usage: UENUM
Feature: Editor
Group: Numeric Property
Type: string="abc"
Status: Done

只在Runtime下生效，在Editor下依然不起作用。

测试代码：

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

测试蓝图：

![Untitled](EnumDisplayNameFn/Untitled.png)

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

原理代码：

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