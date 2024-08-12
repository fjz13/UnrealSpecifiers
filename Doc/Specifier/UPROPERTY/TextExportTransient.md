# TextExportTransient

Description: 在ExportText导出为.COPY格式的时候，忽略该属性。复制拷贝依然会有文本生效
Type: bool
Feature: Serialization
EPropertyFlags: CPF_TextExportTransient (../../Flags/EPropertyFlags/CPF_TextExportTransient.md)
Status: Done

在ExportText导出为.COPY格式的时候，忽略该属性。

测试代码：

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyProperty_SerializationText :public UDataAsset
{
public:
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyInt_Default= 123;
		//PropertyFlags:	CPF_Edit | CPF_BlueprintVisible | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic | CPF_SkipSerialization 
	UPROPERTY(EditAnywhere, BlueprintReadWrite,SkipSerialization)
		int32 MyInt_SkipSerialization = 123;
		//PropertyFlags:	CPF_Edit | CPF_BlueprintVisible | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_TextExportTransient | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic 
	UPROPERTY(EditAnywhere, BlueprintReadWrite,TextExportTransient)
		int32 MyInt_TextExportTransient= 123;

};

void UMyProperty_SerializationText_Test::RunExportTest()
{
	UMyProperty_SerializationText* obj = NewObject<UMyProperty_SerializationText>(GetTransientPackage());

	obj->MyInt_Default = 456;
	obj->MyInt_SkipSerialization = 456;
	obj->MyInt_TextExportTransient = 456;

	FStringOutputDevice Ar;
	UExporter::ExportToOutputDevice(nullptr, obj, nullptr,Ar,TEXT("T3D"), 3);

	FStringOutputDevice Ar2;
	UExporter::ExportToOutputDevice(nullptr, obj, nullptr,Ar,TEXT("COPY"), 3);

	FString str=Ar;
}
```

导出的结果：

```cpp
T3D格式：
Begin Object Class=/Script/Insider.MyProperty_SerializationText Name="BP_SerializationText" ExportPath="/Script/Insider.MyProperty_SerializationText'/Game/Property/BP_SerializationText.BP_SerializationText'"
   MyInt_Default=456
   MyInt_SkipSerialization=456
   MyInt_TextExportTransient=456
End Object

COPY格式：
Begin Object Class=/Script/Insider.MyProperty_SerializationText Name="BP_SerializationText" ExportPath="/Script/Insider.MyProperty_SerializationText'/Game/Property/BP_SerializationText.BP_SerializationText'"
   MyInt_Default=456
   MyInt_SkipSerialization=456
End Object
```

复制拷贝依然会有文本生效：

```cpp
{
	"Tagged": [
		[
			"MyInt_Default",
			"456"
		],
		[
			"MyInt_SkipSerialization",
			"456"
		],
		[
			"MyInt_TextExportTransient",
			"456"
		]
	]
}
```

因此可以发现在COPY格式的时候，MyInt_TextExportTransient并没有被导出。

注意在判断一个Property是否应该序列化的时候，ShouldSerializeValue函数是用在普通的序列化的时候用来判断的。而在ExportText的时候，是用ShouldPort判断的。

但是如果序列化出的格式是COPY，在设置PortFlags的时候，会额外的加上PPF_Copy。因此在后续的判断里才会生效对CPF_TextExportTransient的判断。

原理的代码：

```cpp
if ( FCString::Stricmp(FileType, TEXT("COPY")) == 0 )
	{
		// some code which doesn't have access to the exporter's file type needs to handle copy/paste differently than exporting to file,
		// so set the export flag accordingly
		PortFlags |= PPF_Copy;
	}

//
// Return whether the property should be exported.
//
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