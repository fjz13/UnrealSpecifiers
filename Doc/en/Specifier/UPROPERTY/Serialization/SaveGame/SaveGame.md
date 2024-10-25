# SaveGame

- **Function Description:** During SaveGame archiving, only attributes marked with SaveGame are serialized, while other attributes are not.
- **Metadata Type:** bool
- **Engine Module:** Serialization
- **Common Usage:** ★★★★★

When archiving SaveGame, only attributes marked with SaveGame are serialized, excluding all others.

It specifically designates which properties are to be saved in the archive.

Substructure or subobject properties must also be tagged with SaveGame.

Many foundational structures within NoExportTypes.h are marked with SaveGame.

## Test Code:

```cpp
struct FMySaveGameArchive : public FObjectAndNameAsStringProxyArchive
{
    FMySaveGameArchive (FArchive& InInnerArchive)
        :   FObjectAndNameAsStringProxyArchive(InInnerArchive)
    {
        ArIsSaveGame = true;
    }
};

USTRUCT(BlueprintType)
struct FMySaveGameStruct
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString MyString_Default;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,SaveGame)
		FString MyString_SaveGame;
};

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyProperty_SaveGame :public USaveGame
{
public:
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyInt_Default = 123;
	//PropertyFlags:	CPF_Edit | CPF_BlueprintVisible | CPF_ZeroConstructor | CPF_SaveGame | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
		int32 MyInt_SaveGame = 123;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,SaveGame)
		FMySaveGameStruct MyStruct;
};

UMyProperty_SaveGame* UMyProperty_SaveGame_Test::LoadGameFromMemory(const TArray<uint8>& InSaveData)
{
	FMemoryReader MemoryReader(InSaveData, true);

	FObjectAndNameAsStringProxyArchive Ar(MemoryReader, true);
		Ar.ArIsSaveGame = true;//This tag must be added manually

	UMyProperty_SaveGame* OutSaveGameObject = NewObject<UMyProperty_SaveGame>(GetTransientPackage(), UMyProperty_SaveGame::StaticClass());
	OutSaveGameObject->Serialize(Ar);

	return OutSaveGameObject;
}

bool UMyProperty_SaveGame_Test::SaveGameToMemory(UMyProperty_SaveGame* SaveGameObject, TArray<uint8>& OutSaveData)
{
	FMemoryWriter MemoryWriter(OutSaveData, true);

	// Then save the object state, replacing object refs and names with strings
	FObjectAndNameAsStringProxyArchive Ar(MemoryWriter, false);
	Ar.ArIsSaveGame = true;//This tag must be added manually
	SaveGameObject->Serialize(Ar);

	return true; // Not sure if there's a failure case here.
}

void UMyProperty_SaveGame_Test::RunTest()
{
	UMyProperty_SaveGame* saveGame = Cast<UMyProperty_SaveGame>(UGameplayStatics::CreateSaveGameObject(UMyProperty_SaveGame::StaticClass()));
	saveGame->MyInt_Default = 456;
	saveGame->MyInt_SaveGame = 456;
	saveGame->MyStruct.MyString_Default = TEXT("Hello");
	saveGame->MyStruct.MyString_SaveGame = TEXT("Hello");

	TArray<uint8> outBytes;
	UMyProperty_SaveGame_Test::SaveGameToMemory(saveGame, outBytes);

	UMyProperty_SaveGame* saveGame2 = UMyProperty_SaveGame_Test::LoadGameFromMemory(outBytes);
}
```

The test results indicate that only attributes marked with SaveGame are serialized.

![Untitled](Untitled.png)

Equivalent to indicating in the Blueprint Details panel:

![Untitled](Untitled%201.png)

## Principle:

This tag is only detected when ArIsSaveGame, which means that this tag is only used when detecting the sub-object structure properties of the USaveGame object. But ArIsSaveGame needs to be set to true manually, otherwise this mechanism will not work by default. One way to achieve this is to manually add Ar.ArIsSaveGame = true;, or customize a FMySaveGameArchive for serialization.

In the source code, UEnhancedInputUserSettings is found to inherit from USaveGame and is saved using the archiving method.

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
```