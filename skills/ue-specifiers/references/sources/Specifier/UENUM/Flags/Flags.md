---
title: "Flags"
id: "UENUM.Flags"
kind: "specifier"
symbol: "Flags"
scope: "UENUM"
category: "Flags"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "把该枚举的值作为一个标志来拼接字符串输出"
usage: "UENUM / Flags"
---

# Flags

- **功能描述：**  把该枚举的值作为一个标志来拼接字符串输出。
- **元数据类型：** bool
- **引擎模块：** Trait
- **作用机制：** 在EnumFlags中添加Flags
- **常用程度：★★★★★**

把该枚举的值作为一个标志来拼接字符串输出。

指定作用的地方是当把一个值输出为字符串输出的时候。转换成字符串的方式：一种是直接查找精确相等的值，然后查找特定的枚举值。第二种就是把它当做标志，输出符合相应标记的“A | B | C”这种格式的值。Flags就是指定采用第二种方式。

但是要注意其枚举值是完全没有影响变化的。跟直接把枚举值定义为标记是不同的。

注意和meta(bitflags)的区分，后者是标记该枚举可以作为一个标记，可以作为Bitmask被筛选中。

## 示例代码：

```cpp
UENUM(BlueprintType)
enum class EMyEnum_Normal:uint8
{
	First,
	Second,
	Third,
};

/*
[EMyEnum_Flags	Enum->Field->Object	/Script/Insider.EMyEnum_Flags]
(BlueprintType = true, First.Name = EMyEnum_Flags::First, ModuleRelativePath = Enum/MyEnum_Flags.h, Second.Name = EMyEnum_Flags::Second, Third.Name = EMyEnum_Flags::Third)
	ObjectFlags:	RF_Public | RF_Transient
	Outer:	Package /Script/Insider
	EnumFlags:	EEnumFlags::Flags
	EnumDisplayNameFn:	0
	CppType:	EMyEnum_Flags
	CppForm:	EnumClass
{
	First = 0,
	Second = 1,
	Third = 2,
	EMyEnum_MAX = 3
};
*/
UENUM(BlueprintType,Flags)
enum class EMyEnum_Flags:uint8
{
	First,
	Second,
	Third,
};

void UMyActor_EnumBitFlags_Test::TestFlags()
{
	int value = 3;

	FString outStr_Normal = StaticEnum<EMyEnum_Normal>()->GetValueOrBitfieldAsString(value);
	FString outStr_Flags = StaticEnum<EMyEnum_Flags>()->GetValueOrBitfieldAsString(value);
	FString outStr_BitFlags = StaticEnum<EMyEnum_BitFlags>()->GetValueOrBitfieldAsString(value);

}
```

## 示例效果：

蓝图中的表示，依然只能选择单项。


而测试代码里打印出来的字符串：

可见outStr_Flags 的打印是字符串拼接的。


## 原理：

只在GetValueOrBitfieldAsString这个函数中生效，所以要用这个方法测试才生效。

```cpp
FString UEnum::GetValueOrBitfieldAsString(int64 InValue) const
{
	if (!HasAnyEnumFlags(EEnumFlags::Flags) || InValue == 0)
	{
		return GetNameStringByValue(InValue);
	}
	else
	{
		FString BitfieldString;
		bool WroteFirstFlag = false;
		while (InValue != 0)
		{
			int64 NextValue = 1ll << FMath::CountTrailingZeros64(InValue);
			InValue = InValue & ~NextValue;
			if (WroteFirstFlag)
			{
				// We don't just want to use the NameValuePair.Key because we want to strip enum class prefixes
				BitfieldString.Appendf(TEXT(" | %s"), *GetNameStringByValue(NextValue));
			}
			else
			{
				// We don't just want to use the NameValuePair.Key because we want to strip enum class prefixes
				BitfieldString.Appendf(TEXT("%s"), *GetNameStringByValue(NextValue));
				WroteFirstFlag = true;
			}
		}
		return BitfieldString;
	}
}
```

## 行为

UE5.8 UHT 的 enum specifier 分支写入 `EEnumFlags.Flags`。它影响 `UEnum` 把值作为 bitfield 字符串输出的路径，不会自动把枚举值改成 1、2、4 这种 mask 值。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtEnumSpecifiers.cs` `FlagsSpecifier` writes `EEnumFlags.Flags`
  - 本地样例辅助对照：`D:/github/GitWorkspace/Hello/Source/Insider/Enum/MyEnum_Flags.h`。

## 常见误用

把 `Flags` 当成 `meta=(Bitflags)` 或 `UseEnumValuesAsMaskValuesInEditor`；或忘记手动定义适合 bitmask 的枚举值。
