# TextExportTransient

- **Function Description:** When exporting to .COPY format using ExportText, this attribute is ignored.

- **Metadata Type:** bool
- **Engine Module:** Serialization
- **Action Mechanism:** Include [CPF_TextExportTransient](../../../Flags/EPropertyFlags/CPF_TextExportTransient.md) in PropertyFlags
- **Common Usage:** ★

When exporting to .COPY format with ExportText, this attribute is ignored.

However, text export will still occur when copying properties with the mouse.

## *Test Code:

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

*Exported Results:

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

*The copy will still have the text in effect:

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

Thus, it can be observed that MyInt_TextExportTransient is not exported in COPY format.

## *Principle:

Note that when determining whether a Property should be serialized, the ShouldSerializeValue function is used for general serialization. For ExportText, the ShouldPort function is used for this purpose.

But if the serialization format is COPY, when setting PortFlags, an additional PPF_Copy flag is added. Therefore, the CPF_TextExportTransient check becomes effective in subsequent evaluations.

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