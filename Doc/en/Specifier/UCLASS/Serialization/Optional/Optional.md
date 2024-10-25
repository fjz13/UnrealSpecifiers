# Optional

- **Function Description:** Indicates that objects of this class are optional and can be excluded from saving during the Cooking process.

- **Engine Module:** Serialization
- **Functionality Mechanism:** Add [CLASS_Optional](../../../../Flags/EClassFlags/CLASS_Optional.md) to ClassFlags
- **Commonly Used:** ★

Objects of this class are optional and can be chosen to be ignored during the Cooking process.

- Usually, data marked as EditorOnly, such as MetaData, does not exist at runtime and is saved in separate specific files.
- Optional objects are typically enclosed within the WITH_EDITORONLY_DATA macro and are used exclusively in the editor.
- During the Cooking process, the engine will, based on the EDITOROPTIONAL configuration, add SAVE_Optional to decide whether to serialize the object value along with others, such as metadata.

## Example Code:

```cpp
//ClassFlags:	CLASS_Optional | CLASS_MatchedSerializers | CLASS_Native | CLASS_RequiredAPI | CLASS_TokenStreamAssembled | CLASS_Intrinsic | CLASS_Constructed
UCLASS(Optional)
class INSIDER_API UMyClass_Optional :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyProperty = 123;
};

UCLASS()
class INSIDER_API UMyClass_NotOptional :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyProperty = 123;
};

UCLASS()
class INSIDER_API UMyClass_Optional_Test :public UObject
{
	GENERATED_BODY()
public:

#if WITH_EDITORONLY_DATA
	UPROPERTY()
		UMyClass_Optional* MyOptionalObject;

#endif // WITH_EDITORONLY_DATA

public:
	UPROPERTY()
		UMyClass_NotOptional* MyNotOptionalObject;
public:
	static void CreatePackageAndSave();
	static void LoadPackageAndTest();
};

void UMyClass_Optional_Test::CreatePackageAndSave()
{
	FString packageName = TEXT("/Game/MyOptionTestPackage");
	FString assetPath = FPackageName::LongPackageNameToFilename(packageName, FPackageName::GetAssetPackageExtension());

	IFileManager::Get().Delete(*assetPath, false, true);

	UPackage* package = CreatePackage(*packageName);
	FSavePackageArgs saveArgs{};
	//saveArgs.TopLevelFlags = EObjectFlags::RF_Public | EObjectFlags::RF_Standalone;
	saveArgs.Error = GError;
	saveArgs.SaveFlags=SAVE_NoError;

	//SAVE_Optional = 0x00008000,	///< Indicate that we to save optional exports. This flag is only valid while cooking. Optional exports are filtered if not specified during cooking.

	UMyClass_Optional_Test* testObject = NewObject<UMyClass_Optional_Test>(package, TEXT("testObject"));

#if WITH_EDITORONLY_DATA
	testObject->MyOptionalObject = NewObject<UMyClass_Optional>(testObject, TEXT("MyOptionalObject"));
	testObject->MyOptionalObject->MyProperty = 456;
#endif

	testObject->MyNotOptionalObject = NewObject<UMyClass_NotOptional>(testObject, TEXT("MyNotOptionalObject"));

	testObject->MyNotOptionalObject->MyProperty = 456;

	FString str = UInsiderSubsystem::Get().PrintObject(package, EInsiderPrintFlags::All);
	FString str2 = UInsiderSubsystem::Get().PrintObject(testObject, EInsiderPrintFlags::All);
	FString str3 = UInsiderSubsystem::Get().PrintObject(UMyClass_Optional::StaticClass(), EInsiderPrintFlags::All);
	FString str4 = UInsiderSubsystem::Get().PrintObject(UMyClass_NotOptional::StaticClass(), EInsiderPrintFlags::All);

	bool result = UPackage::SavePackage(package, testObject, *assetPath, saveArgs);

}

void UMyClass_Optional_Test::LoadPackageAndTest()
{
	FString packageName = TEXT("/Game/MyOptionTestPackage");
	FString assetPath = FPackageName::LongPackageNameToFilename(packageName, FPackageName::GetAssetPackageExtension());

	UPackage* package = LoadPackage(nullptr, *assetPath, LOAD_None);
	package->FullyLoad();

	UMyClass_Optional_Test* newTestObject = LoadObject<UMyClass_Optional_Test>(package, TEXT("testObject"), *assetPath);
	//UMyClass_Transient_Test* newTestObject = nullptr;

	/*const TArray<FObjectExport>& exportMap = package->GetLinker()->ExportMap;
	for (const auto& objExport : exportMap)
	{
		if (objExport.ObjectName == TEXT("testObject"))
		{
			newTestObject = Cast<UMyClass_Transient_Test>(objExport.Object);
			break;
		}
	}*/
	FString str = UInsiderSubsystem::Get().PrintObject(package, EInsiderPrintFlags::All);

}

```

## Example Effect:

The standard SavePackage method is ineffective; serialization and saving will still occur. The special saving method occurs during the Cook stage, and this example does not specifically test it.

![Untitled](Untitled.png)

Searching for "Optional" in the source code reveals that it is generally used by the EditorOnlyData and CookedMetaData classes.

```cpp
UCLASS(Optional, Within=Enum)
class ENGINE_API UEnumCookedMetaData : public UObject
UCLASS(Optional, Within=ScriptStruct)
class ENGINE_API UStructCookedMetaData : public UObject
UCLASS(Optional, Within=Class)
class ENGINE_API UClassCookedMetaData : public UObject

UMaterialInterfaceEditorOnlyData* UMaterialInterface::CreateEditorOnlyData()
{
	const UClass* EditorOnlyClass = GetEditorOnlyDataClass();
	check(EditorOnlyClass);
	check(EditorOnlyClass->HasAllClassFlags(CLASS_Optional));

	const FString EditorOnlyName = MaterialInterface::GetEditorOnlyDataName(*GetName());
	const EObjectFlags EditorOnlyFlags = GetMaskedFlags(RF_PropagateToSubObjects);
	return NewObject<UMaterialInterfaceEditorOnlyData>(this, EditorOnlyClass, *EditorOnlyName, EditorOnlyFlags);
}
```

There are also some verifications within the engine:

```cpp
UnrealTypeDefinitionInfo.cpp:
// Validate if we are using editor only data in a class or struct definition
if (HasAnyClassFlags(CLASS_Optional))
{
	for (TSharedRef<FUnrealPropertyDefinitionInfo> PropertyDef : GetProperties())
	{
		if (PropertyDef->GetPropertyBase().IsEditorOnlyProperty())
		{
			PropertyDef->LogError(TEXT("Cannot specify editor only property inside an optional class."));
		}
		else if (PropertyDef->GetPropertyBase().ContainsEditorOnlyProperties())
		{
			PropertyDef->LogError(TEXT("Do not specify struct property containing editor only properties inside an optional class."));
		}
	}
}
```

Discovered through the source code:

//SAVE_Optional = 0x00008000,	///< Indicate that we to save optional exports. This flag is only valid while cooking. Optional exports are filtered if not specified during cooking.

SAVE_Optional is applied to UUserDefinedEnum, UUserDefinedStruct, and UBlueprintGeneratedClass MetaData objects.

```cpp
void UUserDefinedStruct::PreSaveRoot(FObjectPreSaveRootContext ObjectSaveContext)
{
	Super::PreSaveRoot(ObjectSaveContext);

	if (ObjectSaveContext.IsCooking() && (ObjectSaveContext.GetSaveFlags() & SAVE_Optional))
	{
	//This object, with 'this' as its Outer, marked with RF_Standalone | RF_Public, will result in the sub-object being serialized
			UStructCookedMetaData* CookedMetaData = NewCookedMetaData();
			CookedMetaData->CacheMetaData(this);

		if (!CookedMetaData->HasMetaData())
		{
				PurgeCookedMetaData();//Cleanup of this CookedMetaData object is required
		}
	}
	else
	{
		PurgeCookedMetaData();
	}
}
```

Moreover, during the Cooking process, if specified,

bCookEditorOptional = Switches.Contains(TEXT("EDITOROPTIONAL")); // Produce the optional editor package data alongside the cooked data.

the CookEditorOptional attribute will be added

CookFlags |= bCookEditorOptional ? ECookInitializationFlags::CookEditorOptional : ECookInitializationFlags::None;

Subsequently, SAVE_Optional will be conveyed to the Package's SaveFlags

SaveFlags |= COTFS.IsCookFlagSet(ECookInitializationFlags::CookEditorOptional) ? SAVE_Optional : SAVE_None;

Thus, when including a Package, the IsSaveOptional() check will determine whether to create an Optional Realm

```cpp
TArray<ESaveRealm> FSaveContext::GetHarvestedRealmsToSave()
{
	TArray<ESaveRealm> HarvestedContextsToSave;
	if (IsCooking())
	{
		HarvestedContextsToSave.Add(ESaveRealm::Game);
		if (IsSaveOptional())
		{
			HarvestedContextsToSave.Add(ESaveRealm::Optional);
		}
	}
	else
	{
		HarvestedContextsToSave.Add(ESaveRealm::Editor);
	}
	return HarvestedContextsToSave;
}
```

Also, if an Object is found with CLASS_Optional, it will not be treated as an Export (child object) but as an Import (referenced object), and the Optional object may be stored in an external independent file.

```cpp
ESavePackageResult HarvestPackage(FSaveContext& SaveContext)
{
// If we have a valid optional context and we are saving it,
	// transform any harvested non optional export into imports
	// Mark other optional import package as well
	if (!SaveContext.IsSaveAutoOptional() &&
		SaveContext.IsSaveOptional() &&
		SaveContext.IsCooking() &&
		SaveContext.GetHarvestedRealm(ESaveRealm::Optional).GetExports().Num() &&
		SaveContext.GetHarvestedRealm(ESaveRealm::Game).GetExports().Num())
	{
		bool bHasNonOptionalSelfReference = false;
		FHarvestedRealm& OptionalContext = SaveContext.GetHarvestedRealm(ESaveRealm::Optional);
		for (auto It = OptionalContext.GetExports().CreateIterator(); It; ++It)
		{
			if (!It->Obj->GetClass()->HasAnyClassFlags(CLASS_Optional))
			{
				// Make sure the export is found in the game context as well
				if (FTaggedExport* GameExport = SaveContext.GetHarvestedRealm(ESaveRealm::Game).GetExports().Find(It->Obj))
				{
					// Flag the export in the game context to generate it's public hash
					GameExport->bGeneratePublicHash = true;
					// Transform the export as an import
					OptionalContext.AddImport(It->Obj);
					// Flag the package itself to be an import
					bHasNonOptionalSelfReference = true;
				}
				// if not found in the game context and the reference directly came from an optional object, record an illegal reference
				else if (It->bFromOptionalReference)
				{
					SaveContext.RecordIllegalReference(nullptr, It->Obj, EIllegalRefReason::ReferenceFromOptionalToMissingGameExport);
				}
				It.RemoveCurrent();
			}
		}
		// Also add the current package itself as an import if we are referencing any non optional export
		if (bHasNonOptionalSelfReference)
		{
			OptionalContext.AddImport(SaveContext.GetPackage());
		}
	}
}
```