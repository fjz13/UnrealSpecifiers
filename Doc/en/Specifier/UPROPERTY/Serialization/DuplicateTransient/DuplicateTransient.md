# DuplicateTransient

- **Function description:** This attribute is ignored during object duplication or when exporting in COPY format.

- **Metadata type:** bool
- **Engine module:** Serialization
- **Action mechanism:** Add [CPF_DuplicateTransient](../../../../Flags/EPropertyFlags/CPF_DuplicateTransient.md) to PropertyFlags
- **Commonality:** ★★

This attribute is ignored when duplicating objects or exporting in COPY format.

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

	UMyProperty_Serialization* obj3= DuplicateObject<UMyProperty_Serialization>(obj,GetTransientPackage());
}

```

## Example Effect:

When duplicating a blueprint, it is evident that DuplicateTransient is not copied

![Untitled](Untitled.png)

When copying in C++, it is observed that MyInt_DuplicateTransient is not duplicated; it remains 123 instead of 456.

![Untitled](Untitled.png)

## Principle:

During text export, if the format is T3D, the attribute will still be exported. However, if the format is COPY, it will not be exported.

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

During binary serialization:

The attribute will only be skipped if PPF_Duplicate is active (either during DuplicateObject or asset copy)

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

When duplicating an asset, both DuplicateAsset and DuplicateObject occur. At this point, PortFlags equals PPF_Duplicate, and ShouldSerializeValue is triggered for assessment. The attribute will be skipped at this stage