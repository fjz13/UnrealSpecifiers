# Transient

- **Function Description:** Do not serialize this property; it will be initialized with 0.
- **Metadata Type:** bool
- **Engine Module:** Serialization
- **Mechanism:** Add [CPF_Transient](../../../../Flags/EPropertyFlags/CPF_Transient.md) to PropertyFlags
- **Common Usage:** ★★★★★

During serialization, this property is skipped, and the default value is filled with 0.

Neither binary nor text serialization includes this property.

Usually used for temporary intermediate variables or variables holding calculated results.

## Sample Code:

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

Perform AssetActions→Export on such a BP DataAsset,

T3D Format:

```cpp
Begin Object Class=/Script/Insider.MyProperty_Serialization Name="BP_Serialization" ExportPath="/Script/Insider.MyProperty_Serialization'/Game/Property/BP_Serialization.BP_Serialization'"
   MyInt_Default=456
   MyInt_DuplicateTransient=456
End Object
```

COPY Format:

```cpp
Begin Object Class=/Script/Insider.MyProperty_Serialization Name="BP_Serialization" ExportPath="/Script/Insider.MyProperty_Serialization'/Game/Property/BP_Serialization.BP_Serialization'"
   MyInt_Default=456
End Object
```

If it is standard serialization:

It can be observed that obj2's MyInt_Transient property does not receive the new serialized value of 456.

![Untitled](Untitled.png)

## Principle Code:

The CPF_Transient flag is effective only when IsPersistent() is true, and not when saving a CDO. The SetIsPersistent() function is called in many places, such as in MemoryReader/MemoryWriter, where it always checks IsPersistent.

Therefore, Transient properties are ignored during serialization.

When ExportText is performed, CPF_Transient is checked, unless the PPF_IncludeTransient flag is explicitly included

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

Because Transient properties are not serialized, any changes to their values are not saved. When the Asset is opened, it will still display the default value and will not be copied.

![Untitled](Untitled%201.png)