// Fill out your copyright notice in the Description page of Project Settings.

#include "InsiderTypes.h"

#define TEST_FLAG(Result, Flags, Flag) \
{\
	if ( Flags & Flag ) \
	{ \
		Result += TEXT(#Flag); \
		Result += TEXT(" | "); \
	} \
}

#define TEST_ENUM_FLAG(Result, Flags, Flag) \
{\
	if (EnumHasAnyFlags(flags,Flag)) \
	{ \
		Result += TEXT(#Flag); \
		Result += TEXT(" | "); \
	} \
}

#define TEST_ENUM_FLAG_NAME(Result, Flags, FlagValue,FlagName) \
{\
	if (EnumHasAnyFlags(flags,FlagValue)) \
	{ \
		Result += FlagName; \
		Result += TEXT(" | "); \
	} \
}


FString Insider::ObjectFlagsToString(EObjectFlags ObjectFlags)
{
	FString Result;

	// This first group of flags mostly has to do with what kind of object it is. Other than transient, these are the persistent object flags.
	// The garbage collector also tends to look at these.
	TEST_FLAG(Result, ObjectFlags, RF_Public); ///< Object is visible outside its package.
	TEST_FLAG(Result, ObjectFlags, RF_Standalone); ///< Keep object around for editing even if unreferenced.
	TEST_FLAG(Result, ObjectFlags, RF_MarkAsNative); ///< Object (UField) will be marked as native on construction (DO NOT USE THIS FLAG in HasAnyFlags() etc)
	TEST_FLAG(Result, ObjectFlags, RF_Transactional); ///< Object is transactional.
	TEST_FLAG(Result, ObjectFlags, RF_ClassDefaultObject); ///< This object is its class's default object
	TEST_FLAG(Result, ObjectFlags, RF_ArchetypeObject); ///< This object is a template for another object - treat like a class default object
	TEST_FLAG(Result, ObjectFlags, RF_Transient); ///< Don't save object.

	// This group of flags is primarily concerned with garbage collection.
	TEST_FLAG(Result, ObjectFlags, RF_MarkAsRootSet); ///< Object will be marked as root set on construction and not be garbage collected, even if unreferenced (DO NOT USE THIS FLAG in HasAnyFlags() etc)
	TEST_FLAG(Result, ObjectFlags, RF_TagGarbageTemp); ///< This is a temp user flag for various utilities that need to use the garbage collector. The garbage collector itself does not interpret it.

	// The group of flags tracks the stages of the lifetime of a uobject
	TEST_FLAG(Result, ObjectFlags, RF_NeedInitialization); ///< This object has not completed its initialization process. Cleared when ~FObjectInitializer completes
	TEST_FLAG(Result, ObjectFlags, RF_NeedLoad); ///< During load, indicates object needs loading.
	TEST_FLAG(Result, ObjectFlags, RF_KeepForCooker); ///< Keep this object during garbage collection because it's still being used by the cooker
	TEST_FLAG(Result, ObjectFlags, RF_NeedPostLoad); ///< Object needs to be postloaded.
	TEST_FLAG(Result, ObjectFlags, RF_NeedPostLoadSubobjects); ///< During load, indicates that the object still needs to instance subobjects and fixup serialized component references
	TEST_FLAG(Result, ObjectFlags, RF_NewerVersionExists); ///< Object has been consigned to oblivion due to its owner package being reloaded, and a newer version currently exists
	TEST_FLAG(Result, ObjectFlags, RF_BeginDestroyed); ///< BeginDestroy has been called on the object.
	TEST_FLAG(Result, ObjectFlags, RF_FinishDestroyed); ///< FinishDestroy has been called on the object.

	// Misc. Flags
	TEST_FLAG(Result, ObjectFlags, RF_BeingRegenerated); ///< Flagged on UObjects that are used to create UClasses (e.g. Blueprints) while they are regenerating their UClass on load (See FLinkerLoad::CreateExport())
	TEST_FLAG(Result, ObjectFlags, RF_DefaultSubObject); ///< Flagged on subobjects that are defaults
	TEST_FLAG(Result, ObjectFlags, RF_WasLoaded); ///< Flagged on UObjects that were loaded
	TEST_FLAG(Result, ObjectFlags, RF_TextExportTransient); ///< Do not export object to text form (e.g. copy/paste). Generally used for sub-objects that can be regenerated from data in their parent object.
	TEST_FLAG(Result, ObjectFlags, RF_LoadCompleted); ///< Object has been completely serialized by linkerload at least once. DO NOT USE THIS FLAG, It should be replaced with RF_WasLoaded.
	TEST_FLAG(Result, ObjectFlags, RF_InheritableComponentTemplate); ///< Archetype of the object can be in its super class
	TEST_FLAG(Result, ObjectFlags, RF_DuplicateTransient); ///< Object should not be included in any type of duplication (copy/paste, binary duplication, etc.)
	TEST_FLAG(Result, ObjectFlags, RF_StrongRefOnFrame); ///< References to this object from persistent function frame are handled as strong ones.
	TEST_FLAG(Result, ObjectFlags, RF_NonPIEDuplicateTransient); ///< Object should not be included for duplication unless it's being duplicated for a PIE session
	TEST_FLAG(Result, ObjectFlags, RF_WillBeLoaded); ///< This object was constructed during load and will be loaded shortly
	TEST_FLAG(Result, ObjectFlags, RF_HasExternalPackage); ///< This object has an external package assigned and should look it up when getting the outermost package
	//TEST_FLAG(Result, ObjectFlags, RF_PendingKill); ///< Objects that are pending destruction (invalid for gameplay but valid objects). This flag is mirrored in EInternalObjectFlags as PendingKill for performance
	//TEST_FLAG(Result, ObjectFlags, RF_Garbage); ///< Garbage from logical point of view and should not be referenced. This flag is mirrored in EInternalObjectFlags as Garbage for performance
	TEST_FLAG(Result, ObjectFlags, RF_AllocatedInSharedPage); ///< Allocated from a ref-counted page shared with other UObjects


	//TEST_FLAG(Result, ObjectFlags, RF_Dynamic); //< Field Only. Dynamic field - doesn't get constructed during static initialization, can be constructed multiple times

	if (!Result.IsEmpty())
	{
		Result.RemoveAt(Result.Len() - 2, 2);
	}
	else
	{
		return "RF_NoFlags";
	}

	return Result;
}

FString Insider::ClassFlagsToString(uint32 ClassFlags)
{
	FString Result;

	/** Class is abstract and can't be instantiated directly. */
	TEST_FLAG(Result, ClassFlags, CLASS_Abstract);
	/** Save object configuration only to Default INIs, never to local INIs. Must be combined with CLASS_Config */
	TEST_FLAG(Result, ClassFlags, CLASS_DefaultConfig);
	/** Load object configuration at construction time. */
	TEST_FLAG(Result, ClassFlags, CLASS_Config);
	/** This object type can't be saved; null it out at save time. */
	TEST_FLAG(Result, ClassFlags, CLASS_Transient);

	TEST_FLAG(Result, ClassFlags, CLASS_Optional);
	TEST_FLAG(Result, ClassFlags, CLASS_MatchedSerializers);
	TEST_FLAG(Result, ClassFlags, CLASS_ProjectUserConfig);



	/** Successfully parsed. */
	//TEST_FLAG(Result, ClassFlags, CLASS_Parsed);
	/** */
	//CLASS_                  = 0x00000020,
	/** All the properties on the class are shown in the advanced section (which is hidden by default) unless SimpleDisplay is specified on the property */
	//TEST_FLAG(Result, ClassFlags, CLASS_AdvancedDisplay);
	/** Class is a native class - native interfaces will have CLASS_Native set, but not RF_MarkAsNative */
	TEST_FLAG(Result, ClassFlags, CLASS_Native);
	/** Do not allow users to create in the editor. */
	TEST_FLAG(Result, ClassFlags, CLASS_NotPlaceable);
	/** Handle object configuration on a per-object basis, rather than per-class. */
	TEST_FLAG(Result, ClassFlags, CLASS_PerObjectConfig);

	TEST_FLAG(Result, ClassFlags, CLASS_ReplicationDataIsSetUp);


	/** pointers to this class default to weak. */
	//TEST_FLAG(Result, ClassFlags, CLASS_PointersDefaultToWeak);

	/** Class can be constructed from editinline New button. */
	TEST_FLAG(Result, ClassFlags, CLASS_EditInlineNew);
	/** Display properties in the editor without using categories. */
	TEST_FLAG(Result, ClassFlags, CLASS_CollapseCategories);
	/** Class is an interface **/
	TEST_FLAG(Result, ClassFlags, CLASS_Interface);
	/** all properties and functions in this class are const and should be exported as const */
	TEST_FLAG(Result, ClassFlags, CLASS_Const);

	TEST_FLAG(Result, ClassFlags, CLASS_NeedsDeferredDependencyLoading);


	/** pointers to this class default to weak. */
	//TEST_FLAG(Result, ClassFlags, CLASS_PointersDefaultToAutoWeak);

	/** Indicates that the class was created from blueprint source material */
	TEST_FLAG(Result, ClassFlags, CLASS_CompiledFromBlueprint);

	/** Indicates that only the bare minimum bits of this class should be DLL exported/imported */
	TEST_FLAG(Result, ClassFlags, CLASS_MinimalAPI);

	/** Indicates this class must be DLL exported/imported (along with all of it's members) */
	TEST_FLAG(Result, ClassFlags, CLASS_RequiredAPI);

	/** Indicates that references to this class default to instanced. Used to be subclasses of UComponent, but now can be any UObject */
	TEST_FLAG(Result, ClassFlags, CLASS_DefaultToInstanced);

	/** Indicates that the parent token stream has been merged with ours. */
	TEST_FLAG(Result, ClassFlags, CLASS_TokenStreamAssembled);
	/** Class has component properties. */
	TEST_FLAG(Result, ClassFlags, CLASS_HasInstancedReference);
	/** Don't show this class in the editor class browser or edit inline new menus. */
	TEST_FLAG(Result, ClassFlags, CLASS_Hidden);
	/** Don't save objects of this class when serializing */
	TEST_FLAG(Result, ClassFlags, CLASS_Deprecated);
	/** Class not shown in editor drop down for class selection */
	TEST_FLAG(Result, ClassFlags, CLASS_HideDropDown);
	/** Class settings are saved to <AppData>/..../Blah.ini (as opposed to CLASS_DefaultConfig) */
	TEST_FLAG(Result, ClassFlags, CLASS_GlobalUserConfig);
	/** Class was declared directly in C++ and has no boilerplate generated by UnrealHeaderTool */
	TEST_FLAG(Result, ClassFlags, CLASS_Intrinsic);
	/** Class has already been constructed (maybe in a previous DLL version before hot-reload). */
	TEST_FLAG(Result, ClassFlags, CLASS_Constructed);
	/** Indicates that object configuration will not check against ini base/defaults when serialized */
	TEST_FLAG(Result, ClassFlags, CLASS_ConfigDoNotCheckDefaults);
	/** Class has been consigned to oblivion as part of a blueprint recompile, and a newer version currently exists. */
	TEST_FLAG(Result, ClassFlags, CLASS_NewerVersionExists);


	if (!Result.IsEmpty())
	{
		Result.RemoveAt(Result.Len() - 2, 2);
	}
	else
	{
		return "CLASS_None";
	}
	return Result;
}

FString Insider::PropertyFlagsToString(uint64 PropertyFlags)
{
	FString Result;
	TEST_FLAG(Result, PropertyFlags, CPF_Edit);
	TEST_FLAG(Result, PropertyFlags, CPF_ConstParm);
	TEST_FLAG(Result, PropertyFlags, CPF_BlueprintVisible);
	TEST_FLAG(Result, PropertyFlags, CPF_ExportObject);
	TEST_FLAG(Result, PropertyFlags, CPF_BlueprintReadOnly);
	TEST_FLAG(Result, PropertyFlags, CPF_Net);
	TEST_FLAG(Result, PropertyFlags, CPF_EditFixedSize);
	TEST_FLAG(Result, PropertyFlags, CPF_Parm);
	TEST_FLAG(Result, PropertyFlags, CPF_OutParm);
	TEST_FLAG(Result, PropertyFlags, CPF_ZeroConstructor);
	TEST_FLAG(Result, PropertyFlags, CPF_ReturnParm);
	TEST_FLAG(Result, PropertyFlags, CPF_DisableEditOnTemplate);
	TEST_FLAG(Result, PropertyFlags, CPF_Transient);
	TEST_FLAG(Result, PropertyFlags, CPF_Config);
	TEST_FLAG(Result, PropertyFlags, CPF_RequiredParm);
	TEST_FLAG(Result, PropertyFlags, CPF_DisableEditOnInstance);
	TEST_FLAG(Result, PropertyFlags, CPF_EditConst);
	TEST_FLAG(Result, PropertyFlags, CPF_GlobalConfig);
	TEST_FLAG(Result, PropertyFlags, CPF_InstancedReference);
	TEST_FLAG(Result, PropertyFlags, CPF_DuplicateTransient);
	//TEST_FLAG(Result, PropertyFlags, CPF_SubobjectReference);
	TEST_FLAG(Result, PropertyFlags, CPF_SaveGame);
	TEST_FLAG(Result, PropertyFlags, CPF_NoClear);
	TEST_FLAG(Result, PropertyFlags, CPF_ReferenceParm);
	TEST_FLAG(Result, PropertyFlags, CPF_BlueprintAssignable);
	TEST_FLAG(Result, PropertyFlags, CPF_Deprecated);
	TEST_FLAG(Result, PropertyFlags, CPF_IsPlainOldData);
	TEST_FLAG(Result, PropertyFlags, CPF_RepSkip);
	TEST_FLAG(Result, PropertyFlags, CPF_RepNotify);
	TEST_FLAG(Result, PropertyFlags, CPF_Interp);
	TEST_FLAG(Result, PropertyFlags, CPF_NonTransactional);
	TEST_FLAG(Result, PropertyFlags, CPF_EditorOnly);
	TEST_FLAG(Result, PropertyFlags, CPF_NoDestructor);
	TEST_FLAG(Result, PropertyFlags, CPF_AutoWeak);
	TEST_FLAG(Result, PropertyFlags, CPF_ContainsInstancedReference);
	TEST_FLAG(Result, PropertyFlags, CPF_AssetRegistrySearchable);
	TEST_FLAG(Result, PropertyFlags, CPF_SimpleDisplay);
	TEST_FLAG(Result, PropertyFlags, CPF_AdvancedDisplay);
	TEST_FLAG(Result, PropertyFlags, CPF_Protected);
	TEST_FLAG(Result, PropertyFlags, CPF_BlueprintCallable);
	TEST_FLAG(Result, PropertyFlags, CPF_BlueprintAuthorityOnly);
	TEST_FLAG(Result, PropertyFlags, CPF_TextExportTransient);
	TEST_FLAG(Result, PropertyFlags, CPF_NonPIEDuplicateTransient);
	TEST_FLAG(Result, PropertyFlags, CPF_ExposeOnSpawn);
	TEST_FLAG(Result, PropertyFlags, CPF_PersistentInstance);
	TEST_FLAG(Result, PropertyFlags, CPF_UObjectWrapper);
	TEST_FLAG(Result, PropertyFlags, CPF_HasGetValueTypeHash);
	TEST_FLAG(Result, PropertyFlags, CPF_NativeAccessSpecifierPublic);
	TEST_FLAG(Result, PropertyFlags, CPF_NativeAccessSpecifierProtected);
	TEST_FLAG(Result, PropertyFlags, CPF_NativeAccessSpecifierPrivate);
	TEST_FLAG(Result, PropertyFlags, CPF_SkipSerialization);

	if (!Result.IsEmpty())
	{
		Result.RemoveAt(Result.Len() - 2, 2);
	}
	else
	{
		return "CPF_None";
	}
	return Result;
}

FString Insider::FunctionFlagsToString(EFunctionFlags functionFlags)
{
	FString Result;
	TEST_FLAG(Result, functionFlags, FUNC_Final);
	TEST_FLAG(Result, functionFlags, FUNC_RequiredAPI);
	TEST_FLAG(Result, functionFlags, FUNC_BlueprintAuthorityOnly);
	TEST_FLAG(Result, functionFlags, FUNC_BlueprintCosmetic);
	TEST_FLAG(Result, functionFlags, FUNC_Net);
	TEST_FLAG(Result, functionFlags, FUNC_NetReliable);
	TEST_FLAG(Result, functionFlags, FUNC_NetRequest);
	TEST_FLAG(Result, functionFlags, FUNC_Exec);
	TEST_FLAG(Result, functionFlags, FUNC_Native);
	TEST_FLAG(Result, functionFlags, FUNC_Event);
	TEST_FLAG(Result, functionFlags, FUNC_NetResponse);
	TEST_FLAG(Result, functionFlags, FUNC_Static);
	TEST_FLAG(Result, functionFlags, FUNC_NetMulticast);

	TEST_FLAG(Result, functionFlags, FUNC_UbergraphFunction);
	TEST_FLAG(Result, functionFlags, FUNC_MulticastDelegate);
	TEST_FLAG(Result, functionFlags, FUNC_Public);
	TEST_FLAG(Result, functionFlags, FUNC_Private);
	TEST_FLAG(Result, functionFlags, FUNC_Protected);
	TEST_FLAG(Result, functionFlags, FUNC_Delegate);
	TEST_FLAG(Result, functionFlags, FUNC_NetServer);
	TEST_FLAG(Result, functionFlags, FUNC_HasOutParms);
	TEST_FLAG(Result, functionFlags, FUNC_HasDefaults);
	TEST_FLAG(Result, functionFlags, FUNC_NetClient);
	TEST_FLAG(Result, functionFlags, FUNC_DLLImport);
	TEST_FLAG(Result, functionFlags, FUNC_BlueprintCallable);
	TEST_FLAG(Result, functionFlags, FUNC_BlueprintEvent);
	TEST_FLAG(Result, functionFlags, FUNC_BlueprintPure);
	TEST_FLAG(Result, functionFlags, FUNC_EditorOnly);
	TEST_FLAG(Result, functionFlags, FUNC_Const);
	TEST_FLAG(Result, functionFlags, FUNC_NetValidate);
	if (!Result.IsEmpty())
	{
		Result.RemoveAt(Result.Len() - 2, 2);
	}
	else
	{
		return "FUNC_None";
	}
	return Result;
}

FString Insider::CppFormToString(UEnum::ECppForm cppForm)
{
	switch (cppForm)
	{
	case UEnum::ECppForm::Regular:
		return "Regular";
	case UEnum::ECppForm::Namespaced:
		return "Namespaced";
	case UEnum::ECppForm::EnumClass:
		return "EnumClass";
	default:
		break;
	}
	return "";
}

FString Insider::StructFlagsToString(EStructFlags flags)
{
	FString Result;
	TEST_FLAG(Result, flags, STRUCT_Native);
	TEST_FLAG(Result, flags, STRUCT_IdenticalNative);
	TEST_FLAG(Result, flags, STRUCT_HasInstancedReference);
	TEST_FLAG(Result, flags, STRUCT_NoExport);
	TEST_FLAG(Result, flags, STRUCT_Atomic);
	TEST_FLAG(Result, flags, STRUCT_Immutable);
	TEST_FLAG(Result, flags, STRUCT_AddStructReferencedObjects);
	TEST_FLAG(Result, flags, STRUCT_RequiredAPI);
	TEST_FLAG(Result, flags, STRUCT_NetSerializeNative);
	TEST_FLAG(Result, flags, STRUCT_SerializeNative);
	TEST_FLAG(Result, flags, STRUCT_CopyNative);
	TEST_FLAG(Result, flags, STRUCT_IsPlainOldData);
	TEST_FLAG(Result, flags, STRUCT_NoDestructor);
	TEST_FLAG(Result, flags, STRUCT_ZeroConstructor);
	TEST_FLAG(Result, flags, STRUCT_ExportTextItemNative);
	TEST_FLAG(Result, flags, STRUCT_ImportTextItemNative);
	TEST_FLAG(Result, flags, STRUCT_PostSerializeNative);
	TEST_FLAG(Result, flags, STRUCT_SerializeFromMismatchedTag);
	TEST_FLAG(Result, flags, STRUCT_NetDeltaSerializeNative);
	TEST_FLAG(Result, flags, STRUCT_PostScriptConstruct);
	TEST_FLAG(Result, flags, STRUCT_NetSharedSerialization);
	TEST_FLAG(Result, flags, STRUCT_Trashed);
	TEST_FLAG(Result, flags, STRUCT_NewerVersionExists);
	TEST_FLAG(Result, flags, STRUCT_CanEditChange);


	if (!Result.IsEmpty())
	{
		Result.RemoveAt(Result.Len() - 2, 2);
	}
	else
	{
		return "STRUCT_NoFlags";
	}
	return Result;
}


FString Insider::EnumFlagsToString(EEnumFlags flags)
{
	FString Result;

	TEST_ENUM_FLAG_NAME(Result, flags, EEnumFlags::Flags,TEXT("Flags"));
	TEST_ENUM_FLAG_NAME(Result, flags, EEnumFlags::NewerVersionExists,TEXT("NewerVersionExists"));

	if (!Result.IsEmpty())
	{
		Result.RemoveAt(Result.Len() - 2, 2);
	}
	else
	{
		return "None";
	}
	return Result;
}

FString Insider::PackageFlagsToString(EPackageFlags flags)
{
	FString Result;
	TEST_ENUM_FLAG(Result, flags, PKG_NewlyCreated);
	TEST_ENUM_FLAG(Result, flags, PKG_ClientOptional);
	TEST_ENUM_FLAG(Result, flags, PKG_ServerSideOnly);
	TEST_ENUM_FLAG(Result, flags, PKG_CompiledIn);
	TEST_ENUM_FLAG(Result, flags, PKG_ForDiffing);
	TEST_ENUM_FLAG(Result, flags, PKG_EditorOnly);
	TEST_ENUM_FLAG(Result, flags, PKG_Developer);
	TEST_ENUM_FLAG(Result, flags, PKG_UncookedOnly);
	TEST_ENUM_FLAG(Result, flags, PKG_Cooked);
	TEST_ENUM_FLAG(Result, flags, PKG_ContainsNoAsset);
	TEST_ENUM_FLAG(Result, flags, PKG_NotExternallyReferenceable);
	TEST_ENUM_FLAG(Result, flags, PKG_UnversionedProperties);
	TEST_ENUM_FLAG(Result, flags, PKG_ContainsMapData);
	TEST_ENUM_FLAG(Result, flags, PKG_IsSaving);
	TEST_ENUM_FLAG(Result, flags, PKG_Compiling);
	TEST_ENUM_FLAG(Result, flags, PKG_ContainsMap);
	TEST_ENUM_FLAG(Result, flags, PKG_RequiresLocalizationGather);
	TEST_ENUM_FLAG(Result, flags, PKG_PlayInEditor);
	TEST_ENUM_FLAG(Result, flags, PKG_ContainsScript);
	TEST_ENUM_FLAG(Result, flags, PKG_DisallowExport);
	TEST_ENUM_FLAG(Result, flags, PKG_CookGenerated);
	TEST_ENUM_FLAG(Result, flags, PKG_DynamicImports);
	TEST_ENUM_FLAG(Result, flags, PKG_RuntimeGenerated);
	TEST_ENUM_FLAG(Result, flags, PKG_ReloadingForCooker);
	TEST_ENUM_FLAG(Result, flags, PKG_FilterEditorOnly);


	if (!Result.IsEmpty())
	{
		Result.RemoveAt(Result.Len() - 2, 2);
	}
	else
	{
		return "PKG_None";
	}
	return Result;
}

FString Insider::CompressionFlagsToString(ECompressionFlags flags)
{
	FString Result;
	TEST_ENUM_FLAG(Result, flags, COMPRESS_BiasMemory);
	TEST_ENUM_FLAG(Result, flags, COMPRESS_BiasSpeed);
	TEST_ENUM_FLAG(Result, flags, COMPRESS_SourceIsPadded);
	TEST_ENUM_FLAG(Result, flags, COMPRESS_OptionsFlagsMask);
	TEST_ENUM_FLAG(Result, flags, COMPRESS_ForPackaging);
	TEST_ENUM_FLAG(Result, flags, COMPRESS_ForPurposeMask);

	if (!Result.IsEmpty())
	{
		Result.RemoveAt(Result.Len() - 2, 2);
	}
	else
	{
		return "COMPRESS_None";
	}
	return Result;
}

FString Insider::NetModeToString(ENetMode netmode)
{
	switch (netmode)
	{
	case ENetMode::NM_Standalone:
		return TEXT("NM_Standalone");
	case ENetMode::NM_DedicatedServer:
		return TEXT("NM_DedicatedServer");
	case ENetMode::NM_ListenServer:
		return TEXT("NM_ListenServer");
	case ENetMode::NM_Client:
		return TEXT("NM_Client");
	default:
		return TEXT("NM_None");
	}
}

FString Insider::DependencyPropertyToString(UE::AssetRegistry::EDependencyProperty flags)
{
	FString Result;
	TEST_ENUM_FLAG_NAME(Result, flags, UE::AssetRegistry::EDependencyProperty::Hard,TEXT("Package_Hard"));
	TEST_ENUM_FLAG_NAME(Result, flags, UE::AssetRegistry::EDependencyProperty::Game,TEXT("Package_Game"));
	TEST_ENUM_FLAG_NAME(Result, flags, UE::AssetRegistry::EDependencyProperty::Build,TEXT("Package_Build"));
	TEST_ENUM_FLAG_NAME(Result, flags, UE::AssetRegistry::EDependencyProperty::Direct,TEXT("Manage_Direct"));

	if (!Result.IsEmpty())
	{
		Result.RemoveAt(Result.Len() - 2, 2);
	}
	else
	{
		return "None";
	}
	return Result;
}

#undef TEST_FLAG
#undef TEST_ENUM_FLAG
