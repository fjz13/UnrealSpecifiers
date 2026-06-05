---
title: "DuplicateTransient"
id: "UPROPERTY.DuplicateTransient"
kind: "specifier"
symbol: "DuplicateTransient"
scope: "UPROPERTY"
category: "Serialization"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "在对象复制或COPY格式导出的时候，忽略该属性"
usage: "UPROPERTY / Serialization"
---

# DuplicateTransient

## Decision Summary

- **Use when:** `DuplicateTransient` specifier 的 `UPROPERTY / Serialization` 场景需要：在对象复制或COPY格式导出的时候，忽略该属性。
- **Do not use when:** 声明宏、目标类型或代码契约不属于 `UPROPERTY / Serialization`。
- **Requires:** specifier 必须放在 UE5.8 UHT 支持的宏和声明位置，并满足正文 caveat。
- **Conflicts:** 不要和同类互斥 specifier 或语义相反的暴露/持久化/网络规则混用。
- **Prefer instead:** 能用更窄暴露范围或更明确 metadata 表达时，优先选择更窄方案。

- **功能描述：** 在对象复制或COPY格式导出的时候，忽略该属性。

- **元数据类型：** bool
- **引擎模块：** Serialization
- **作用机制：** 在PropertyFlags中加入CPF_DuplicateTransient
- **常用程度：** ★★

在对象复制或COPY格式导出的时候，忽略该属性。

## 行为

`DuplicateTransient` 会给属性加入 `CPF_DuplicateTransient`。对象复制、copy/paste 或带 `PPF_Duplicate` 的序列化路径会跳过该属性，使复制出来的对象保留默认值或重新初始化后的值。

适合不应从源对象继承到副本的运行期状态、缓存、临时引用或复制后必须重新计算的字段。

## UE5.8 审计结论

状态：`verified_UE5.8`

UE5.8 UHT 源码 `C:/Program Files/Epic Games/UE_5.8/Engine/Source/Programs/Shared/EpicGames.UHT/Specifiers/UhtPropertyMemberSpecifiers.cs` 中，`DuplicateTransient` 会设置 `EPropertyFlags.DuplicateTransient`。

UE5.8 CoreUObject 源码 `Runtime/CoreUObject/Private/UObject/Property.cpp` 中：

- `FProperty::ShouldSerializeValue` 在属性有 `CPF_DuplicateTransient` 且 archive port flags 包含 `PPF_Duplicate` 时返回 `false`。
- `FProperty::ShouldPort` 在 `PPF_Copy` 路径中把 `CPF_DuplicateTransient` 视为 transient，除非端口标志显式包含 transient/default parsing。

在 `D:/github/GitWorkspace/Hello/Source/Insider/Property/Serialization/MyProperty_Serialization.h` 中，`MyInt_DuplicateTransient` 的样例注释记录了 `CPF_DuplicateTransient`。`bat/build-hello.bat` 已在 UE5.8 下成功编译 `HelloEditor Win64 Development`。

## 常见误用

- `DuplicateTransient` 主要影响复制路径，不是普通持久化序列化的通用替代品。
- 如果属性在所有持久化保存中都不应保存，应考虑 `Transient`。
- 如果只想排除非 PIE 复制，应考虑 `NonPIEDuplicateTransient`。
- `DuplicateTransient` 不会阻止属性在代码里被赋值，也不控制 Blueprint 访问。

## 示例代码：

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyProperty_Serialization :public UDataAsset
{
public:
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyInt_Default = 123;
		//PropertyFlags:	CPF_Edit | CPF_BlueprintVisible | CPF_ZeroConstructor | CPF_Transient | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient)
		int32 MyInt_Transient = 123;
		//PropertyFlags:	CPF_Edit | CPF_BlueprintVisible | CPF_ZeroConstructor | CPF_DuplicateTransient | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DuplicateTransient)
		int32 MyInt_DuplicateTransient = 123;
		//PropertyFlags:	CPF_Edit | CPF_BlueprintVisible | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_NonPIEDuplicateTransient | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UPROPERTY(EditAnywhere, BlueprintReadWrite, NonPIEDuplicateTransient)
		int32 MyInt_NonPIEDuplicateTransient = 123;
};

void UMyProperty_Serialization_Test::RunTest()
{

	UMyProperty_Serialization* obj = NewObject<UMyProperty_Serialization>(GetTransientPackage());

	obj->MyInt_Default = 456;
	obj->MyInt_Transient = 456;
	obj->MyInt_DuplicateTransient = 456;
	obj->MyInt_NonPIEDuplicateTransient = 456;

	UMyProperty_Serialization* obj3= DuplicateObject<UMyProperty_Serialization>(obj,GetTransientPackage());
}

```

## 示例效果：

复制蓝图，可以看到DuplicateTransient并不会被复制


在采用C++复制的时候：也看到MyInt_DuplicateTransient 并不会产生复制，还是123而不是456。


## 原理：

在文本导出的时候，如果是T3D格式，则依然会导出。如果是COPY格式，则不导出。

```cpp
bool FProperty::ShouldPort( uint32 PortFlags/*=0*/ ) const
{
// if we're copying, treat DuplicateTransient as transient
	if ((PortFlags & PPF_Copy) && HasAnyPropertyFlags(CPF_DuplicateTransient | CPF_TextExportTransient) && !(PortFlags & (PPF_ParsingDefaultProperties | PPF_IncludeTransient)))
	{
		return false;
	}
}
```

在二进制序列化的时候：

只有在PPF_Duplicate生效的时候，（DuplicateObject或者资产复制），才会跳过该属性

```cpp
bool FProperty::ShouldSerializeValue(FArchive& Ar) const
{
// Skip properties marked DuplicateTransient when duplicating
	if ((PropertyFlags & CPF_DuplicateTransient) && (Ar.GetPortFlags() & PPF_Duplicate))
	{
		return false;
	}
}
```

在对资产进行Duplidate的时候，发生DuplicateAsset然后DuplicateObject，这个时候PortFlags=PPF_Duplicate，然后会触发ShouldSerializeValue进行判断。这个时候会跳过该属性
