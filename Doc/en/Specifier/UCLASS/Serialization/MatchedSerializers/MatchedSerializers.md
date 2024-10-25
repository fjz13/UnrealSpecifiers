# MatchedSerializers

- **Function Description:** Specifies that the class supports serialization of text structure
- **Engine Module:** Serialization
- **Metadata Type:** bool
- **Functionality Mechanism:** Add [CLASS_MatchedSerializers](../../../../Flags/EClassFlags/CLASS_MatchedSerializers.md) to ClassFlags and [MatchedSerializers](../../../../Meta/Serialization/MatchedSerializers.md) to Meta
- **Usage Frequency:** 0

This specifier is only allowed to be used in NoExportTypes.h and is considered an internal specifier for the engine's use.

Effectively, most classes possess this tag, except for those that do not export themselves, typically including those defined in NoExportTypes.h (unless MatchedSerializers is manually added, such as UObject), or metadata defined with DECLARE_CLASS_INTRINSIC directly in the source code.

Therefore, the majority of classes actually have this tag. In UHT, unless a class is marked NoExport, this tag is automatically added.

```cpp
// Force the MatchedSerializers on for anything being exported
if (!ClassExportFlags.HasAnyFlags(UhtClassExportFlags.NoExport))
{
			ClassFlags |= EClassFlags.MatchedSerializers;
}
```

## Structured Serializer:

If a class supports text format, the StructuredArchive's purpose is to serially expand the class's fields in a tree-like structure for serialization and display, facilitating human comprehension. If text format is not supported, all field values are compressed into a binary buffer (Data field), which is also the method used during runtime.

Test Code:

```cpp

UCLASS(Blueprintable, BlueprintType,editinlinenew)
class INSIDER_API UMyClass_MatchedSerializersSub :public UObject
{
public:
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MyInt_Default = 123;
};

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyClass_MatchedSerializersTestAsset:public UDataAsset
{
public:
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MyInt_Default = 123;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Instanced)
	UMyClass_MatchedSerializersSub* SubObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStruct* MyStructType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UClass* MyClassType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UEnum* MyEnumType;
};

void UMyClass_MatchedSerializers_Test::ApplyClassFlag()
{
	UMyClass_MatchedSerializersTestAsset::StaticClass()->ClassFlags |= CLASS_MatchedSerializers;
	UMyClass_MatchedSerializersSub::StaticClass()->ClassFlags |= CLASS_MatchedSerializers;
}

void UMyClass_MatchedSerializers_Test::RemoveClassFlag()
{
	UMyClass_MatchedSerializersTestAsset::StaticClass()->ClassFlags &= ~CLASS_MatchedSerializers;
	UMyClass_MatchedSerializersSub::StaticClass()->ClassFlags &= ~CLASS_MatchedSerializers;
}
```

Create a test data Asset in the editor

![Untitled](Untitled.png)

Then enable TextAssetFormatSupport (UEditorExperimentalSettings::bTextAssetFormatSupport) in the Editor options

![Untitled](Untitled%201.png)

Three menus will then appear on the asset, supporting the export of the asset as text.

![Untitled](Untitled%202.png)

ExportToTextFormat will generate a .utxt file in the same directory as the blueprint asset, formatted as JSON. By dynamically adding or removing the CLASS_MatchedSerializers tag, the differences produced by this tag can be compared:

![Untitled](Untitled%203.png)

It can be observed that there are significant differences in the serialized content. The right-side result without the CLASS_MatchedSerializers tag compresses all field values into a binary buffer (Data field).

## Internal Mechanism Principle:

The CLASS_MatchedSerializers tag is used in UClass::IsSafeToSerializeToStructuredArchives to indicate the use of a structured serializer. Support for text import and export is only considered in the editor environment.

Only SavePackage2.cpp and LinkerLoad.cpp are affected, occurring when saving UPackage as a subclass object. Therefore, simple in-memory Archive serialization cannot be used for testing.

```cpp
bool UClass::IsSafeToSerializeToStructuredArchives(UClass* InClass)
{
	while (InClass)
	{
		if (!InClass->HasAnyClassFlags(CLASS_MatchedSerializers))
		{
			return false;
		}
		InClass = InClass->GetSuperClass();
	}
	return true;
}

//LinkerLoad.cpp
bool bClassSupportsTextFormat = UClass::IsSafeToSerializeToStructuredArchives(Object->GetClass());
if (IsTextFormat())//If Ar serialization is in text format
{
			FStructuredArchiveSlot ExportSlot = GetExportSlot(Export.ThisIndex);

			if (bClassSupportsTextFormat) //If the class itself supports text format
			{
				Object->GetClass()->SerializeDefaultObject(Object, ExportSlot);
			}
			else
			{
				FStructuredArchiveChildReader ChildReader(ExportSlot);
				FArchiveUObjectFromStructuredArchive Adapter(ChildReader.GetRoot());
				Object->GetClass()->SerializeDefaultObject(Object, Adapter.GetArchive());
			}
}

//SavePackage2.cpp
#if WITH_EDITOR
			bool bSupportsText = UClass::IsSafeToSerializeToStructuredArchives(Export.Object->GetClass());
#else
			bool bSupportsText = false;
#endif

if (bSupportsText)
{
				Export.Object->GetClass()->SerializeDefaultObject(Export.Object, ExportSlot);
}
else
{
				FArchiveUObjectFromStructuredArchive Adapter(ExportSlot);
				Export.Object->GetClass()->SerializeDefaultObject(Export.Object, Adapter.GetArchive());
				Adapter.Close();
}
```

Text format is only effective in the editor environment.

As seen in the source code, if the class itself supports text format serialization, it can be directly serialized when Ar is in text format, using the default SerializeTaggedProperties. Otherwise, FArchiveUObjectFromStructuredArchive must be used to adapt, converting the object pointer to a combination of object path + int32 Index.

When printing all classes in the engine that contain or do not contain the CLASS_MatchedSerializers tag, it is found that classes in the UStruct inheritance chain begin to include the tag (but UClass does not), while classes above UField do not include it, such as various Property types. The class list can be found in the Doc txt file.