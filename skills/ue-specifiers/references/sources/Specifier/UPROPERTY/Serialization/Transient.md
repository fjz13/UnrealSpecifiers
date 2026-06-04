---
title: "Transient"
id: "UPROPERTY.Transient"
kind: "specifier"
symbol: "Transient"
scope: "UPROPERTY"
category: "Serialization"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "不序列化该属性，该属性初始化时候会被0填充"
usage: "UPROPERTY / Serialization"
---

# Transient

- **功能描述：** 不序列化该属性，该属性初始化时候会被0填充。
- **元数据类型：** bool
- **引擎模块：** Serialization
- **作用机制：** 在PropertyFlags中加入CPF_Transient
- **常用程度：★★★★★**

序列化的时候略过该属性，用0来填充默认值。

二进制和文本都不序列化该属性。

一般用于一些临时中间变量或计算后的结果变量。

## 行为

`Transient` 会给属性加入 `CPF_Transient`。持久化序列化时该属性会被跳过；文本导出时默认也会跳过，除非端口标志显式包含 transient 属性。

适合运行期缓存、中间计算结果、临时对象引用、编辑器辅助状态等不应保存到资产、包、配置或普通持久化数据里的字段。

## UE5.8 审计结论

状态：`verified_UE5.8`

UE5.8 UHT 源码 `C:/Program Files/Epic Games/UE_5.8/Engine/Source/Programs/Shared/EpicGames.UHT/Specifiers/UhtPropertyMemberSpecifiers.cs` 中，`Transient` 会设置 `EPropertyFlags.Transient`。

UE5.8 CoreUObject 源码 `Runtime/CoreUObject/Private/UObject/Property.cpp` 中：

- `FProperty::ShouldSerializeValue` 在属性有 `CPF_Transient`、archive 为 persistent 且不是 serializing defaults 时返回 `false`。
- `FProperty::ShouldPort` 在没有 `PPF_ParsingDefaultProperties` 或 `PPF_IncludeTransient` 时跳过 `CPF_Transient` 属性。

在 `D:/github/GitWorkspace/Hello/Source/Insider/Property/Serialization/MyProperty_Serialization.h` 中，`MyInt_Transient` 的样例注释记录了 `CPF_Transient`。`bat/build-hello.bat` 已在 UE5.8 下成功编译 `HelloEditor Win64 Development`。

## 常见误用

- `Transient` 不等于“运行时永远不会有值”；它只是控制默认持久化/导出/复制路径是否保存该属性。
- `Transient` 不控制 Blueprint 访问；如需 Blueprint 读写仍要单独使用 `BlueprintReadOnly` 或 `BlueprintReadWrite`。
- 不要把需要 SaveGame、Config 或资产持久保存的数据标成 `Transient`。
- 对对象复制专门跳过的场景，优先考虑 `DuplicateTransient` 或 `NonPIEDuplicateTransient`。

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

	//save obj
	TArray<uint8> outBytes;
	FMemoryWriter MemoryWriter(outBytes, true);
	FObjectAndNameAsStringProxyArchive Ar(MemoryWriter, false);
	obj->Serialize(Ar);

	//load
	FMemoryReader MemoryReader(outBytes, true);

	FObjectAndNameAsStringProxyArchive Ar2(MemoryReader, true);

	UMyProperty_Serialization* obj2 = NewObject<UMyProperty_Serialization>(GetTransientPackage());
	obj2->Serialize(Ar2);
}
```

对这么一个BP DataAsset进行AssetActions→Export，

T3D格式：

```cpp
Begin Object Class=/Script/Insider.MyProperty_Serialization Name="BP_Serialization" ExportPath="/Script/Insider.MyProperty_Serialization'/Game/Property/BP_Serialization.BP_Serialization'"
   MyInt_Default=456
   MyInt_DuplicateTransient=456
End Object
```

COPY格式：

```cpp
Begin Object Class=/Script/Insider.MyProperty_Serialization Name="BP_Serialization" ExportPath="/Script/Insider.MyProperty_Serialization'/Game/Property/BP_Serialization.BP_Serialization'"
   MyInt_Default=456
End Object
```

如果是普通的序列化：

可见obj2的MyInt_Transient 属性并没有从序列化中获得新值456.


## 原理代码：

判断CPF_Transient的生效，只有在IsPersistent()的时候，并且不是在保存CDO。SetIsPersistent()的调用在很多地方都出现，比如在MemoryReader/MemoryWriter都是IsPersistent。

因此Transient是在序列化的时候会被忽略。

在ExportText的时候发现会进行CPF_Transient的判断，除非强制进行包括PPF_IncludeTransient

```cpp
bool FProperty::ShouldSerializeValue(FArchive& Ar) const
{
	// Skip the property if the archive says we should
	if (Ar.ShouldSkipProperty(this))
	{
		return false;
	}

	// Skip non-SaveGame properties if we're saving game state
	if (!(PropertyFlags & CPF_SaveGame) && Ar.IsSaveGame())
	{
		return false;
	}

	const uint64 SkipFlags = CPF_Transient | CPF_DuplicateTransient | CPF_NonPIEDuplicateTransient | CPF_NonTransactional | CPF_Deprecated | CPF_DevelopmentAssets | CPF_SkipSerialization;
	if (!(PropertyFlags & SkipFlags))
	{
		return true;
	}

	// Skip properties marked Transient when persisting an object, unless we're saving an archetype
	if ((PropertyFlags & CPF_Transient) && Ar.IsPersistent() && !Ar.IsSerializingDefaults())
	{

		return false;
	}

	// Skip properties marked DuplicateTransient when duplicating
	if ((PropertyFlags & CPF_DuplicateTransient) && (Ar.GetPortFlags() & PPF_Duplicate))
	{
		return false;
	}

	// Skip properties marked NonPIEDuplicateTransient when duplicating, but not when we're duplicating for PIE
	if ((PropertyFlags & CPF_NonPIEDuplicateTransient) && !(Ar.GetPortFlags() & PPF_DuplicateForPIE) && (Ar.GetPortFlags() & PPF_Duplicate))
	{
		return false;
	}

	// Skip properties marked NonTransactional when transacting
	if ((PropertyFlags & CPF_NonTransactional) && Ar.IsTransacting())
	{
		return false;
	}

	// Skip deprecated properties when saving or transacting, unless the archive has explicitly requested them
	if ((PropertyFlags & CPF_Deprecated) && !Ar.HasAllPortFlags(PPF_UseDeprecatedProperties) && (Ar.IsSaving() || Ar.IsTransacting() || Ar.WantBinaryPropertySerialization()))
	{
		return false;
	}

	// Skip properties marked SkipSerialization, unless the archive is forcing them
	if ((PropertyFlags & CPF_SkipSerialization) && (Ar.WantBinaryPropertySerialization() || !Ar.HasAllPortFlags(PPF_ForceTaggedSerialization)))
	{
		return false;
	}

	// Skip editor-only properties when the archive is rejecting them
	if (IsEditorOnlyProperty() && Ar.IsFilterEditorOnly())
	{
		return false;
	}

	// Otherwise serialize!
	return true;
}

///////////////////////////////////////////
bool FProperty::ShouldPort( uint32 PortFlags/*=0*/ ) const
{
	// if no size, don't export
	if (GetSize() <= 0)
	{
		return false;
	}

	if (HasAnyPropertyFlags(CPF_Deprecated) && !(PortFlags & (PPF_ParsingDefaultProperties | PPF_UseDeprecatedProperties)))
	{
		return false;
	}

	// if we're parsing default properties or the user indicated that transient properties should be included
	if (HasAnyPropertyFlags(CPF_Transient) && !(PortFlags & (PPF_ParsingDefaultProperties | PPF_IncludeTransient)))
	{
		return false;
	}

	// if we're copying, treat DuplicateTransient as transient
	if ((PortFlags & PPF_Copy) && HasAnyPropertyFlags(CPF_DuplicateTransient | CPF_TextExportTransient) && !(PortFlags & (PPF_ParsingDefaultProperties | PPF_IncludeTransient)))
	{
		return false;
	}

	// if we're not copying for PIE and NonPIETransient is set, don't export
	if (!(PortFlags & PPF_DuplicateForPIE) && HasAnyPropertyFlags(CPF_NonPIEDuplicateTransient))
	{
		return false;
	}

	// if we're only supposed to export components and this isn't a component property, don't export
	if ((PortFlags & PPF_SubobjectsOnly) && !ContainsInstancedObjectProperty())
	{
		return false;
	}

	// hide non-Edit properties when we're exporting for the property window
	if ((PortFlags & PPF_PropertyWindow) && !(PropertyFlags & CPF_Edit))
	{
		return false;
	}

	return true;
}
```

因为不序列Transient属性，因此该属性修改值也并不会被保存起来。打开Asset的时候依然会是默认值，也并不会被复制。

