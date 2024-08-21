# Optional

- **功能描述：** 标记该类的对象是可选的，在Cooking的时候可以选择是否要忽略保存它们。

- **引擎模块：** Serialization
- **作用机制：** 在ClassFlags中添加[CLASS_Optional](../../../../Flags/EClassFlags/CLASS_Optional.md)
- **常用程度：** ★

标记该类的对象是可选的，在Cooking的时候可以选择是否要忽略保存它们。

- 一般为EditorOnly的数据，如MetaData等，在游戏运行时不存在，保存在其他的特定文件中。
- Optional的对象一般也包在WITH_EDITORONLY_DATA宏里，只在编辑器下使用。
- 引擎在cook的时候，会根据EDITOROPTIONAL的配置来加上SAVE_Optional，从而选择是否一起序列化该对象值，比如metadata。

## 示例代码：

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

## 示例效果：

正常的SavePackage发现是没有作用的，依然会序列化保存。特殊的保存方式在Cook阶段，本例就没有专门测试了。

![Untitled](Untitled.png)

在源码里搜索Optional，可以看到一般是EditorOnlyData和CookedMetaData类在使用。

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

引擎里也有一些验证：

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

通过源码发现：

//SAVE_Optional = 0x00008000,	///< Indicate that we to save optional exports. This flag is only valid while cooking. Optional exports are filtered if not specified during cooking.

这个SAVE_Optional 作用于UUserDefinedEnum，UUserDefinedStruct，UBlueprintGeneratedClass的MetaData对象上。

```cpp
void UUserDefinedStruct::PreSaveRoot(FObjectPreSaveRootContext ObjectSaveContext)
{
	Super::PreSaveRoot(ObjectSaveContext);

	if (ObjectSaveContext.IsCooking() && (ObjectSaveContext.GetSaveFlags() & SAVE_Optional))
	{
	//这个对象是以this为Outer的，标记RF_Standalone | RF_Public，会造成该子对象被序列化下来
			UStructCookedMetaData* CookedMetaData = NewCookedMetaData();
			CookedMetaData->CacheMetaData(this);

		if (!CookedMetaData->HasMetaData())
		{
				PurgeCookedMetaData();//清理掉这个CookedMetaData对象
		}
	}
	else
	{
		PurgeCookedMetaData();
	}
}
```

另外，在cook的时候，如果指定

bCookEditorOptional = Switches.Contains(TEXT("EDITOROPTIONAL")); // Produce the optional editor package data alongside the cooked data.

则会加上CookEditorOptional 的标识

CookFlags |= bCookEditorOptional ? ECookInitializationFlags::CookEditorOptional : ECookInitializationFlags::None;

再之后则会传达SAVE_Optional 给Package的SaveFlags

SaveFlags |= COTFS.IsCookFlagSet(ECookInitializationFlags::CookEditorOptional) ? SAVE_Optional : SAVE_None;

从而在包括Package的时候，IsSaveOptional()的判断会造成是否创建Optional的Realm，

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

还有如果发现Object有CLASS_Optional，则不把它当做Export(子对象)，而是当做Import(引用的对象)，Optional对象有可能放在外部独立的文件中。

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