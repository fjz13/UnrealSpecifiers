#include "InsiderSubsystem.h"
#include "UObject/Class.h"
#include "UObject/UnrealType.h"
#include "Utility/Log.h"
#include "UObject/Stack.h"
#include "PrivateAccess.h"
#include "Windows\WindowsPlatformApplicationMisc.h"
#include "InsiderPrinter.h"

#if WITH_METADATA
#include "UObject/MetaData.h"
#endif

#include <Kismet/KismetSystemLibrary.h>
#include <UnrealExporter.h>
#include <AssetRegistry/PackageReader.h>
#include <Misc/AssetRegistryInterface.h>

INSIDER_STEAL_PRIVATE_MEMBER(UEnum, EEnumFlags, EnumFlags);

INSIDER_STEAL_PRIVATE_MEMBER(UEnum, FEnumDisplayNameFn, EnumDisplayNameFn);



UInsiderSubsystem& UInsiderSubsystem::Get()
{
	return *(UInsiderSubsystem*)GEngine->GetEngineSubsystemBase(UInsiderSubsystem::StaticClass());

}

void UInsiderSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	PrintObjectCustomizedMap.Add(UMetaData::StaticClass()).BindUObject(this, &UInsiderSubsystem::PrintMetaDataObjectCustomized);

	if (UScriptStruct* guidStruct = FindStructWithName(TEXT("Guid")))
	{
		PrintStructCustomizedMap.Add(guidStruct).BindUObject(this, &UInsiderSubsystem::PrintGuidCustomized);
		IsStructPrintOnelineSupportedMap.Add(guidStruct, true);
	}

	if (UScriptStruct* guidStruct = FindStructWithName(TEXT("Vector")))
	{
		PrintStructCustomizedMap.Add(guidStruct).BindUObject(this, &UInsiderSubsystem::PrintCoreStructsCustomized);
		IsStructPrintOnelineSupportedMap.Add(guidStruct, true);
	}

	if (UScriptStruct* guidStruct = FindStructWithName(TEXT("Rotator")))
	{
		PrintStructCustomizedMap.Add(guidStruct).BindUObject(this, &UInsiderSubsystem::PrintCoreStructsCustomized);
		IsStructPrintOnelineSupportedMap.Add(guidStruct, true);
	}
}

void UInsiderSubsystem::Deinitialize()
{

}

//memory mirror of other one
class FPackageDependencyData
{
public:
	struct FPackageDependency
	{
		FName PackageName;
		UE::AssetRegistry::EDependencyProperty Property;
	};
	struct FSearchableNamesDependency
	{
		FName PackageName;
		FName ObjectName;
		TArray<FName> ValueNames;

	};

	/** The name of the package that dependency data is gathered from */
	FName PackageName;

	/** Asset Package data, gathered at the same time as dependency data */
	FAssetPackageData PackageData;

	// Dependency Data
	TArray<FPackageDependency> PackageDependencies;
	TArray<FSearchableNamesDependency> SearchableNameDependencies;

	// Transient Flags indicating which types of data have been gathered
	bool bHasPackageData = false;
	bool bHasDependencyData = false;
};

struct FPropertyOffsetAscending
{
	bool operator()(const FProperty& A, const FProperty& B)const
	{
		return A.GetOffset_ForInternal() < B.GetOffset_ForInternal();
	}
};



#pragma region Trace


FString UInsiderSubsystem::SetMetaData(const UObject* obj, FName key, FString value)
{
#if WITH_METADATA
	UMetaData* metaData = obj->GetOutermost()->GetMetaData();
	metaData->RemoveValue(obj, key);
	metaData->SetValue(obj, key, *value);

	FString result;
	result += FString::Printf(TEXT("SetMetaData %s = %s : \n"), *key.ToString(), *value);
	result += PrintMetaData(obj);
	return result;
#else
	return "Cannot SetMetaData in Runtime.\n";
#endif
}

FString UInsiderSubsystem::RemoveMetaData(const UObject* obj, FName key)
{
#if WITH_METADATA
	FString result;

	UMetaData* metaData = obj->GetOutermost()->GetMetaData();
	if (metaData->HasValue(obj, key))
	{
		FString value = metaData->GetValue(obj, key);
		metaData->RemoveValue(obj, key);
		result += FString::Printf(TEXT("RemoveMetaData %s = %s : \n"), *key.ToString(), *value);
	}
	else
	{
		result += FString::Printf(TEXT("RemoveMetaData NotFound: %s\n"), *key.ToString());
	}

	result += PrintMetaData(obj);
	return result;
#else
	return "Cannot RemoveMetaData in Runtime.\n";
#endif
}


bool UInsiderSubsystem::HasMetaData(const UObject* obj)
{
#if WITH_METADATA
	UMetaData* metaData = obj->GetOutermost()->GetMetaData();
	const TMap<FName, FString>* keyValues = metaData->GetMapForObject(obj);
	return keyValues != nullptr && keyValues->Num() > 0;
#else
	return false;
#endif
}

void UInsiderSubsystem::SetPropertyMetaData(FName typeName, FName propertyName, FName key, FString value)
{
	UObject* obj = UInsiderSubsystem::FindObjectWithNameSmart(typeName.ToString());
	if (UScriptStruct* ss = Cast<UScriptStruct>(obj))
	{
		if (FProperty* prop = ss->FindPropertyByName(propertyName))
		{
			prop->SetMetaData(key, MoveTemp(value));
		}
	}
}

void UInsiderSubsystem::RemovePropertyMetaData(FName typeName, FName propertyName, FName key)
{
	UObject* obj = UInsiderSubsystem::FindObjectWithNameSmart(typeName.ToString());
	if (UScriptStruct* ss = Cast<UScriptStruct>(obj))
	{
		if (FProperty* prop = ss->FindPropertyByName(propertyName))
		{
			prop->RemoveMetaData(key);

		}
	}
}

void UInsiderSubsystem::PrintStringEx(const UObject* WorldContextObject, FString value, bool bCopyToClipboard /*= false*/, bool bPrintToScreen /*= false*/, bool bPrintToLog /*= false*/, FLinearColor TextColor /*= FLinearColor(0.0f, 0.66f, 1.0f)*/, float Duration /*= 2.f*/)
{
	if (bPrintToScreen || bPrintToLog)
	{
		UKismetSystemLibrary::PrintString(WorldContextObject, value, bPrintToScreen, bPrintToLog, TextColor, Duration);
	}
	if (bCopyToClipboard)
	{
		FPlatformApplicationMisc::ClipboardCopy(*value);
	}
}



FString UInsiderSubsystem::K2_PrintObject(const UObject* WorldContextObject, const UObject* object, int32 flags /*= 4095*/, FString prefix /*= ""*/, bool bCopyToClipboard/*=true*/, bool bPrintToScreen /*= true*/, bool bPrintToLog /*= true*/, FLinearColor TextColor /*= FLinearColor(0.0f, 0.66f, 1.0f)*/, float Duration /*= 2.f */)
{
	FString str = PrintObject(object, (EInsiderPrintFlags)flags, prefix);
	PrintStringEx(WorldContextObject, str, bCopyToClipboard, bPrintToScreen, bPrintToLog, TextColor, Duration);
	return str;
}

FString UInsiderSubsystem::PrintObject(const UObject* object, EInsiderPrintFlags flags /*= EInsiderPrintFlags::All*/, FString prefix /*= ""*/)
{
	TSet<const UObject*> allObjects;
	return PrintObjectHelper(object, allObjects, flags, prefix);
}

FString UInsiderSubsystem::PrintObjectHelper(const UObject* object, TSet<const UObject*>& allObjects, EInsiderPrintFlags flags /*= EInsiderPrintFlags::All*/, FString prefix /*= ""*/)
{
	if (object == nullptr || IsObjectIgnored(object))
	{
		return "";
	}

	if (!allObjects.Contains(object))
	{
		allObjects.Add(object);
	}
	else
	{
		return "";
	}

	FString result;
	if (IsObjectCustomized(object))
	{
		result = PrintObjectHeader(object, EInsiderPrintFlags::WithHierarchy, prefix);	//force to print only object name
		//result += prefix + "{\n";
		result += PrintObjectCustomizedMap.FindChecked(object->GetClass()).Execute(object->GetClass(), object, allObjects, flags, prefix);
		result += "\n";

		//result += prefix + "};\n";
		return result;
	}

	result = PrintObjectHeader(object, flags, prefix);

	if (const UPackage* package = Cast<const UPackage>(object))
	{
		result += PrintPackage(package, flags, prefix);
	}
	else if (const UEnum* enumClass = Cast<const UEnum>(object))
	{
		result += PrintEnum(enumClass, flags, prefix);
	}
	else if (const UScriptStruct* structClass = Cast<const UScriptStruct>(object))
	{
		result += PrintStruct(structClass, nullptr, allObjects, flags, prefix);
	}
	else if (const UFunction* func = Cast<const UFunction>(object))
	{
		result += PrintFunctionHeader(func, flags, prefix + "\t");
		result += prefix + "{\n";
		result += PrintChildrenProperties(func, nullptr, allObjects, flags, prefix);
		result += prefix + "};\n";
	}
	else if (const UClass* classObj = Cast<const UClass>(object))
	{
		allObjects.Add(classObj);
		result += PrintClassHeader(classObj, flags, prefix);
		result += PrintClassInterfaces(classObj, flags, prefix);

		result += prefix + "{\n";
		result += PrintChildrenProperties(classObj, nullptr, allObjects, flags, prefix);
		result += PrintClassFunctions(classObj, flags, prefix);
		result += prefix + "};\n";

	}
	else
	{
		//just simple object
		UClass* otherClassObj = object->GetClass();

		if (!allObjects.Contains(otherClassObj))
		{
			allObjects.Add(otherClassObj);

			if (EnumHasAnyFlags(flags, EInsiderPrintFlags::Class))
			{
				result += PrintObjectHeader(otherClassObj, flags, prefix + "\t");
				result += PrintClassHeader(otherClassObj, flags, prefix + "\t");
			}

			result += prefix + "{\n";
			result += PrintChildrenProperties(otherClassObj, object, allObjects, flags, prefix);
			result += prefix + "};\n";
		}
	}


	//child objects
	if (EnumHasAnyFlags(flags, EInsiderPrintFlags::Recursive))
	{
		TArray<UObject*> childObjects;
		GetObjectsWithOuter(object, childObjects, false);
		for (const UObject* child : childObjects)
		{
			if (!child->IsA<UFunction>())
			{
				result += PrintObjectHelper(child, allObjects, flags, prefix + "\t");
			}
		}
	}

	return result;
}


FString UInsiderSubsystem::PrintObjectHeader(const UObject* object, EInsiderPrintFlags flags /*= EInsiderPrintFlags::ObjectDefault*/, FString prefix /*= ""*/)
{
	if (object == nullptr)
	{
		return "";
	}
	FString typeToken = GetObjectTypeToken(object);

	bool isType = Cast<UField>(object) != nullptr;
	//FString tokenBegin = isType ? "[" : "(";
	//FString tokenEnd = isType ? "]" : ")";

	const FString tokenBegin = "[";
	const FString tokenEnd = "]";

	FString result;
	result += FString::Printf(L"%s%s%s %llx %s", *prefix, *tokenBegin, *typeToken, object, *object->GetName());

	if (EnumHasAnyFlags(flags, EInsiderPrintFlags::WithHierarchy))
	{
		result += "\t";
		result += GetClassHierarchyString(object->GetClass(), true, true);
		result += "\t";
		result += object->GetPathName();
	}
	else
	{

	}

	result += tokenEnd;
	result += "\n";

#if WITH_METADATA
	if (EnumHasAnyFlags(flags, EInsiderPrintFlags::WithMetaData))
	{
		result += PrintMetaData(object, prefix, "\n");
	}
#endif

	if (EnumHasAnyFlags(flags, EInsiderPrintFlags::WithDetails))
	{
		UObject* outer = object->GetOuter();
		FString outerName = outer != nullptr ? outer->GetFullName() : TEXT("nullptr");
		result += FString::Printf(L"%s\tObjectFlags:\t%s\n", *prefix, *Insider::ObjectFlagsToString(object->GetFlags()));
		result += FString::Printf(L"%s\tOuter:\t%s\n", *prefix, *outerName);
		//result += FString::Printf(L"%s\tPath:\t%s\n", *prefix, *object->GetPathName());
	}

	return result;
}

FString UInsiderSubsystem::GetObjectTypeToken(const UObject* object)
{
	if (const UEnum* enumClass = Cast<const UEnum>(object))
	{
		return "enum";
	}
	else if (const UScriptStruct* structClass = Cast<const UScriptStruct>(object))
	{
		return "struct";
	}
	else if (const UFunction* func = Cast<const UFunction>(object))
	{
		return "func";
	}
	else if (const UClass* classObj = Cast<const UClass>(object))
	{
		return "class";
	}
	else if (const UPackage* packageObj = Cast<const UPackage>(object))
	{
		return "package";
	}
	else
	{
		return "object";
	}
}

FString UInsiderSubsystem::PrintClassHeader(const UClass* classObj, EInsiderPrintFlags flags /*= EInsiderPrintFlags::ClassDefault*/, FString prefix /*= ""*/)
{
	FString result;

	if (EnumHasAnyFlags(flags, EInsiderPrintFlags::WithHierarchy))
	{
		FString hierarchy;
		const UClass* ParentClass = classObj;
		while (ParentClass)
		{
			hierarchy += FString::Printf(L":%s", *ParentClass->GetName());
			ParentClass = ParentClass->GetSuperClass();
		}

		result += FString::Printf(L"%s\tClassHierarchy:\t%s\n", *prefix, *hierarchy + 1);
	}


	if (EnumHasAnyFlags(flags, EInsiderPrintFlags::WithDetails))
	{
		result += FString::Printf(L"%s\tClassFlags:\t%s\n", *prefix, *Insider::ClassFlagsToString(classObj->GetClassFlags()));
		result += FString::Printf(L"%s\tSize:\t%d\n", *prefix, classObj->PropertiesSize);

		if (classObj->ClassWithin != nullptr)
		{
			result += FString::Printf(L"%s\tWithin:\t%s\n", *prefix, *classObj->ClassWithin->GetName());
		}
#if WITH_EDITORONLY_DATA
		if (classObj->ClassGeneratedBy != nullptr)
		{
			result += FString::Printf(L"%s\tClassGeneratedBy:\t%s\n", *prefix, *classObj->ClassGeneratedBy->GetName());
		}
#endif

		if (!classObj->ClassConfigName.IsNone())
		{
			result += FString::Printf(L"%s\tClassConfigName:\t%s\n", *prefix, *classObj->ClassConfigName.ToString());
		}
	}

	return result;
}


FString UInsiderSubsystem::PrintProperty(const FProperty* property, const void* object, TSet<const UObject*>& allObjects, EInsiderPrintFlags flags /*= EInsiderPrintFlags::PropertyDefault*/, FString prefix /*= ""*/)
{
	const FProperty* ownerProperty = property->GetOwnerProperty();
	bool isInContainer = IsContainerProperty(ownerProperty) && ownerProperty != property;

	FString propTypeString = GetPropertyCPPTypeString(property);

	FString result;
	bool isParam = (property->PropertyFlags & CPF_Parm) != 0;

#if WITH_METADATA
	if (EnumHasAnyFlags(flags, EInsiderPrintFlags::WithMetaData))
	{
		result += PrintMetaDataMapInline(TEXT(""), property->GetMetaDataMap(), prefix, "\n");
	}
#endif

	result += PrintPropertyDeclaration(property, object, allObjects, flags, prefix);

	if (EnumHasAnyFlags(flags, EInsiderPrintFlags::WithDetails) && !isInContainer)
	{
		result += FString::Printf(L"%s\tPropertyFlags:\t%s\n", *prefix, *Insider::PropertyFlagsToString(property->GetPropertyFlags()));
		if (!property->RepNotifyFunc.IsNone())
		{
			result += FString::Printf(L"%s\tRepNotifyFunc:\t%s\n", *prefix, *property->RepNotifyFunc.ToString());
		}

		if (property->HasGetter())
		{
			//GetterFunc is stored in TPropertyWithSetterAndGetter<PropertyType>
			result += FString::Printf(L"%s\tGetterFunc:\tHas Native Getter\n", *prefix);
		}

		if (property->HasSetter())
		{
			//SetterFunc is stored in TPropertyWithSetterAndGetter<PropertyType>
			result += FString::Printf(L"%s\tSetterFunc:\tHas Native Setter\n", *prefix);
		}

		result += PrintPropertyHeader(property, flags, prefix);
	}



	if (HasPropertySubObject(property, object, allObjects, flags, prefix))
	{
		result += ExpandPropertyObjectValue(property, object, allObjects, flags, prefix);
		result += "\n";
	}

	return result;
}

FString UInsiderSubsystem::PrintPropertyDeclaration(const FProperty* property, const void* object, TSet<const UObject*>& allObjects, EInsiderPrintFlags flags /*= EInsiderPrintFlags::PropertyDefault*/, FString prefix /*= ""*/)
{
	const FProperty* ownerProperty = property->GetOwnerProperty();
	FString propTypeString = GetPropertyCPPTypeString(property);

	FString result;

	//type name
	if (EnumHasAnyFlags(flags, EInsiderPrintFlags::Declaration))
	{
		result += FString::Printf(L"%s%d-[%d] ", *prefix, property->GetOffset_ForInternal(), property->GetSize());
		result += propTypeString;
		result += " ";
		result += property->GetFName().ToString();
	}
	else
	{
		result += prefix;
		result += propTypeString;
		result += " ";
		result += property->GetFName().ToString();
	}

	if (object != nullptr)
	{
		FString str = PrintPropertyValueInline(property, object, allObjects, flags, prefix);
		if (!str.IsEmpty())
		{
			result += " = " + str;
		}
	}

	result += ";\n";


	return result;
}

FString UInsiderSubsystem::ExpandPropertyObjectValue(const FProperty* property, const void* object, TSet<const UObject*>& allObjects, EInsiderPrintFlags flags /*= EInsiderPrintFlags::PropertyDefault*/, FString prefix /*= ""*/)
{
	FString result;
	if (object == nullptr)
	{
		return result;
	}
	//sub object / container expanding

	if (const FStructProperty* structProperty = CastField<const FStructProperty>(property))
	{
		if (EnumHasAnyFlags(flags, EInsiderPrintFlags::Recursive))
		{
			const UScriptStruct* structClass = structProperty->Struct;
			const void* propertyValuePtr = property->ContainerPtrToValuePtr<const void*>(object);

			if (IsStructCustomized(structClass, propertyValuePtr))
			{
				result += PrintStructCustomizedMap.FindChecked(structClass).Execute(structClass, propertyValuePtr, allObjects, flags, prefix);
			}
			else
			{
				FString innerStr = PrintChildrenProperties(structClass, propertyValuePtr, allObjects, flags, prefix);
				if (!innerStr.IsEmpty())
				{
					result += prefix + "{\n";
					result += innerStr;
					result += prefix + "};";
				}
			}
		}
	}
	else if (const FObjectPropertyBase* objectPropertyBase = CastField<const FObjectPropertyBase>(property))
	{
		UObject* subObject = nullptr;
		if (objectPropertyBase->HasAnyPropertyFlags(CPF_TObjectPtr))
		{
			if (const FObjectProperty* objectProperty = CastField<const FObjectProperty>(objectPropertyBase))
			{
				const TObjectPtr<UObject>* subObjectPtr = objectPropertyBase->ContainerPtrToValuePtr<TObjectPtr<UObject>>(object);
				if (subObjectPtr != nullptr)
				{
					if (subObjectPtr->IsResolved())
					{
						subObject = subObjectPtr->Get();
					}
					else
					{
						UPTRINT objRef = subObjectPtr->GetHandle().PointerOrRef;
						result += FString::Printf(TEXT("NotResolvedRef:%s"), *LexToString(objRef));
					}

				}

			}
		}
		else
		{
			subObject = objectPropertyBase->GetObjectPropertyValue_InContainer(object);
		}

		if (subObject != nullptr && !allObjects.Contains(subObject) && EnumHasAnyFlags(flags, EInsiderPrintFlags::WithSubObjects))
		{
			if (IsObjectCustomized(subObject))
			{
				result += PrintObjectCustomizedMap.FindChecked(subObject->GetClass()).Execute(subObject->GetClass(), subObject, allObjects, flags, prefix);
			}
			else
			{
				FString innerStr = PrintChildrenProperties(subObject->GetClass(), subObject, allObjects, flags, prefix);

				if (!innerStr.IsEmpty())
				{
					result += prefix + "{\n";
					result += innerStr;
					result += prefix + "};";
				}
			}
		}
	}
	else if (const FArrayProperty* arrayProperty = CastField<const FArrayProperty>(property))
	{
		FScriptArrayHelper_InContainer helper(arrayProperty, object);
		int num = helper.Num();
		if (num > 0)
		{
			result += prefix + "[\n";
			const FProperty* itemProperty = arrayProperty->Inner;
			EInsiderPrintFlags itemFlags = EInsiderPrintFlags::DataOnly | EInsiderPrintFlags::Properties | EInsiderPrintFlags::Recursive | EInsiderPrintFlags::WithSubObjects;
			//subContent += prefix + "\t";
			for (int i = 0; i < num; ++i)
			{
				uint8* itemData = helper.GetElementPtr(i);
				result += ExpandPropertyObjectValue(itemProperty, itemData, allObjects, itemFlags, prefix + "\t");
				if (i != helper.Num() - 1)
				{
					result += TEXT(",\n");
				}
				else
				{
					result += TEXT("\n");
				}
			}
			result += prefix + "]";
		}

	}
	else if (const FSetProperty* setProperty = CastField<const FSetProperty>(property))
	{

		FScriptSetHelper_InContainer helper(setProperty, object);
		int num = helper.Num();
		if (num > 0)
		{
			result += prefix + "[\n";
			EInsiderPrintFlags itemFlags = EInsiderPrintFlags::DataOnly | EInsiderPrintFlags::Properties | EInsiderPrintFlags::Recursive | EInsiderPrintFlags::WithSubObjects;
			const FProperty* itemProperty = helper.GetElementProperty();
			for (auto i = helper.CreateIterator(); i; ++i)
			{
				uint8* itemData = helper.GetElementPtr(i);
				result += ExpandPropertyObjectValue(itemProperty, itemData, allObjects, itemFlags, prefix + "\t");
			}
			result += prefix + "];";
		}


	}
	else if (const FMapProperty* mapProperty = CastField<const FMapProperty>(property))
	{
		FScriptMapHelper_InContainer helper(mapProperty, object);
		int num = helper.Num();
		if (num > 0)
		{
			result += prefix + "[\n";
			const FProperty* keyProperty = helper.GetKeyProperty();
			const FProperty* valueProperty = helper.GetValueProperty();
			EInsiderPrintFlags itemFlags = EInsiderPrintFlags::DataOnly | EInsiderPrintFlags::Properties | EInsiderPrintFlags::Recursive | EInsiderPrintFlags::WithSubObjects;
			for (auto i = helper.CreateIterator(); i; ++i)
			{
				uint8* keyData = helper.GetKeyPtr(i);
				uint8* valueData = helper.GetValuePtr(i);
				result += ExpandPropertyObjectValue(keyProperty, keyData, allObjects, itemFlags, prefix + "\t");
				result += ExpandPropertyObjectValue(valueProperty, valueData, allObjects, itemFlags, prefix + "\t");
			}
			result += prefix + "];";
		}
	}
	else
	{
		result += prefix;

		FString propertyValueString;
		const void* propertyValuePtr = property->ContainerPtrToValuePtr<const void*>(object);
		property->ExportTextItem_Direct(propertyValueString, propertyValuePtr, nullptr, (UObject*)object, PPF_None);

		if (const FNameProperty* nameProperty = CastField<const FNameProperty>(property))
		{
			propertyValueString = "\"" + propertyValueString + "\"";
		}
		else if (const FStrProperty* strProperty = CastField<const FStrProperty>(property))
		{
			propertyValueString = "\"" + propertyValueString + "\"";
		}
		else if (const FTextProperty* textProperty = CastField<const FTextProperty>(property))
		{
			propertyValueString = "\"" + propertyValueString + "\"";
		}

		result += propertyValueString.IsEmpty() ? "\"\"" : propertyValueString;
	}


	return result;
}

FString UInsiderSubsystem::PrintPropertyValueInline(const FProperty* property, const void* object, TSet<const UObject*>& allObjects, EInsiderPrintFlags flags /*= EInsiderPrintFlags::PropertyDefault*/, FString prefix /*= ""*/)
{
	FString result;
	if (object == nullptr)
	{
		return result;
	}
	//sub object / container expanding

	if (const FStructProperty* structProperty = CastField<const FStructProperty>(property))
	{
		if (EnumHasAnyFlags(flags, EInsiderPrintFlags::Recursive))
		{
			const UScriptStruct* structClass = structProperty->Struct;
			const void* propertyValuePtr = property->ContainerPtrToValuePtr<const void*>(object);

			if (IsStructPrintOnelineSupported(structClass, object))
			{
				result += PrintStructCustomizedMap.FindChecked(structClass).Execute(structClass, object, allObjects, flags, prefix);

			}
		}
	}
	else if (const FObjectPropertyBase* objectPropertyBase = CastField<const FObjectPropertyBase>(property))
	{
		UObject* subObject = nullptr;
		if (objectPropertyBase->HasAnyPropertyFlags(CPF_TObjectPtr))
		{
			if (const FObjectProperty* objectProperty = CastField<const FObjectProperty>(objectPropertyBase))
			{
				const TObjectPtr<UObject>* subObjectPtr = objectPropertyBase->ContainerPtrToValuePtr<TObjectPtr<UObject>>(object);
				if (subObjectPtr != nullptr)
				{
					if (subObjectPtr->IsResolved())
					{
						subObject = subObjectPtr->Get();
					}
					else
					{
						UPTRINT objPackedRef = subObjectPtr->GetHandle().PointerOrRef;
						FObjectRef objRef = UE::CoreUObject::Private::MakeObjectRef(UE::CoreUObject::Private::FPackedObjectRef{ objPackedRef });
						result += FString::Printf(TEXT("[NotResolvedRef: %s %s]"), *LexToString(objPackedRef), *objRef.GetExportTextName());
					}
				}
			}
		}
		else
		{
			subObject = objectPropertyBase->GetObjectPropertyValue_InContainer(object);
		}

		if (subObject != nullptr)
		{
			FString subObjectName = subObject->GetFName().ToString();

			if (subObjectName.IsEmpty())
			{
				result += "\"\"";
			}
			else
			{
				result += "[" + subObjectName + "]";
			}
		}
		else if (result.IsEmpty())
		{
			result += "nullptr";
		}
	}
	else if (const FArrayProperty* arrayProperty = CastField<const FArrayProperty>(property))
	{
		FScriptArrayHelper_InContainer helper(arrayProperty, object);
		result += "[" + FString::FromInt(helper.Num()) + "]";
	}
	else if (const FSetProperty* setProperty = CastField<const FSetProperty>(property))
	{
		FScriptSetHelper_InContainer helper(setProperty, object);
		result += "[" + FString::FromInt(helper.Num()) + "]";

	}
	else if (const FMapProperty* mapProperty = CastField<const FMapProperty>(property))
	{
		FScriptMapHelper_InContainer helper(mapProperty, object);
		result += "[" + FString::FromInt(helper.Num()) + "]";
	}
	else
	{
		FString propertyValueString;
		const void* propertyValuePtr = property->ContainerPtrToValuePtr<const void*>(object);
		property->ExportTextItem_Direct(propertyValueString, propertyValuePtr, nullptr, (UObject*)object, PPF_None);

		if (const FNameProperty* nameProperty = CastField<const FNameProperty>(property))
		{
			propertyValueString = "\"" + propertyValueString + "\"";
		}
		else if (const FStrProperty* strProperty = CastField<const FStrProperty>(property))
		{
			propertyValueString = "\"" + propertyValueString + "\"";
		}
		else if (const FTextProperty* textProperty = CastField<const FTextProperty>(property))
		{
			const FText* text = (const FText*)propertyValuePtr;
			propertyValueString = text->ToString();
			propertyValueString = "\"" + propertyValueString + "\"";
		}

		result += propertyValueString.IsEmpty() ? "\"\"" : propertyValueString;
	}


	return result;
}

bool UInsiderSubsystem::HasPropertySubObject(const FProperty* property, const void* object, TSet<const UObject*>& allObjects, EInsiderPrintFlags flags /*= EInsiderPrintFlags::PropertyDefault*/, FString prefix /*= ""*/)
{
	if (object == nullptr)
	{
		return false;
	}
	if (const FStructProperty* structProperty = CastField<const FStructProperty>(property))
	{

		const UScriptStruct* structClass = structProperty->Struct;
		const void* propertyValuePtr = property->ContainerPtrToValuePtr<const void*>(object);

		if (IsStructPrintOnelineSupported(structClass, propertyValuePtr))
		{
			return false;
		}

		if (EnumHasAnyFlags(flags, EInsiderPrintFlags::Recursive))
		{
			auto properties = GetProperties(structClass, flags, false);
			if (properties.IsEmpty())
			{
				return false;
			}


			return true;
		}
	}
	else if (const FObjectPropertyBase* objectPropertyBase = CastField<const FObjectPropertyBase>(property))
	{
		UObject* subObject = nullptr;
		if (objectPropertyBase->HasAnyPropertyFlags(CPF_TObjectPtr))
		{
			if (const FObjectProperty* objectProperty = CastField<const FObjectProperty>(objectPropertyBase))
			{
				const TObjectPtr<UObject>* subObjectPtr = objectPropertyBase->ContainerPtrToValuePtr<TObjectPtr<UObject>>(object);
				if (subObjectPtr != nullptr)
				{
					if (!subObjectPtr->IsResolved())
					{
						return false;
					}
					subObject = subObjectPtr->Get();
					if (subObject == nullptr)
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}

		if (subObject == nullptr)
		{
			subObject = objectPropertyBase->GetObjectPropertyValue_InContainer(object);
		}
		if (subObject != nullptr && !allObjects.Contains(subObject) && EnumHasAnyFlags(flags, EInsiderPrintFlags::WithSubObjects))
		{
			auto properties = GetProperties(subObject->GetClass(), flags, false);
			if (properties.IsEmpty())
			{
				return false;
			}

			return true;
		}

	}
	else if (const FArrayProperty* arrayProperty = CastField<const FArrayProperty>(property))
	{
		FScriptArrayHelper_InContainer helper(arrayProperty, object);

		return helper.Num() > 0;

	}
	else if (const FSetProperty* setProperty = CastField<const FSetProperty>(property))
	{
		FScriptSetHelper_InContainer helper(setProperty, object);

		return helper.Num() > 0;

	}
	else if (const FMapProperty* mapProperty = CastField<const FMapProperty>(property))
	{
		FScriptMapHelper_InContainer helper(mapProperty, object);

		return helper.Num() > 0;

	}
	return false;
}

FString UInsiderSubsystem::PrintFunctionParameter(const FProperty* property, const void* object, TSet<const UObject*>& allObjects, EInsiderPrintFlags flags /*= EInsiderPrintFlags::PropertyDefault*/, FString prefix /*= ""*/)
{
	const FProperty* ownerProperty = property->GetOwnerProperty();
	bool isInContainer = IsContainerProperty(ownerProperty) && ownerProperty != property;

	FString propTypeString = GetPropertyCPPTypeString(property);

	FString result;
	bool isParam = (property->PropertyFlags & CPF_Parm) != 0;

	if (isParam)
	{
		bool isOutParam = (property->PropertyFlags & CPF_OutParm) != 0;
		bool isReturnParam = (property->PropertyFlags & CPF_ReturnParm) != 0;

		if (isReturnParam)
		{
			result += prefix + propTypeString;
		}
		else
		{
			if (isOutParam)
			{
				result += FString::Printf(TEXT("%s%s& %s"), *prefix, *propTypeString, *property->GetFName().ToString());
			}
			else //if (isParam)
			{
				result += FString::Printf(TEXT("%s%s %s"), *prefix, *propTypeString, *property->GetFName().ToString());
			}
		}
	}
	return result;
}

FString UInsiderSubsystem::PrintFunctionHeader(const UFunction* func, EInsiderPrintFlags flags /*= EInsiderPrintFlags::FunctionDefault*/, FString prefix/*=""*/)
{
	TSet<const UObject*> allObjects;

	FString result;

	if (EnumHasAnyFlags(flags, EInsiderPrintFlags::WithDetails))
	{
		if (UFunction* superFunc = func->GetSuperFunction())
		{
			result += FString::Printf(L"%s\tSuperFunction:\t%s\n", *prefix, *superFunc->GetFName().ToString());
		}
		result += FString::Printf(L"%sFunctionFlags:\t%s\n", *prefix, *Insider::FunctionFlagsToString(func->FunctionFlags));
		result += FString::Printf(L"%sNumParms:\t%d\n", *prefix, func->NumParms);
		result += FString::Printf(L"%sParmsSize:\t%d\n", *prefix, func->ParmsSize);
		result += FString::Printf(L"%sReturnValueOffset:\t%d\n", *prefix, func->ReturnValueOffset);
		result += FString::Printf(L"%sRPCId:\t%d\n", *prefix, func->RPCId);
		result += FString::Printf(L"%sRPCResponseId:\t%d\n", *prefix, func->RPCResponseId);
	}


	if (EnumHasAnyFlags(flags, EInsiderPrintFlags::Declaration))
	{
		result += prefix;
		if (func->HasAnyFunctionFlags(FUNC_Public))
		{
			result += "public ";
		}
		if (func->HasAnyFunctionFlags(FUNC_Protected))
		{
			result += "protected ";
		}
		if (func->HasAnyFunctionFlags(FUNC_Private))
		{
			result += "private ";
		}

		if (func->HasAnyFunctionFlags(FUNC_Static))
		{
			result += "static ";
		}

		if (func->GetReturnProperty() != nullptr)
		{
			result += GetPropertyCPPTypeString(func->GetReturnProperty());
		}
		else
		{
			result += "void";
		}
		result += FString::Printf(L" %s(", *func->GetFName().ToString());
		bool hasParam = false;
		for (TFieldIterator<FProperty> i(func); i && (i->PropertyFlags & CPF_Parm); ++i)
		{
			if (i->PropertyFlags & CPF_ReturnParm)
			{
				continue;
			}
			result += PrintFunctionParameter(*i, nullptr, allObjects, EInsiderPrintFlags::Parameters);
			result += ", ";
			hasParam = true;
		}

		if (hasParam)
		{
			result.RemoveAt(result.Len() - 2, 2); //remove last ", "
		}
		result += ")";

		bool hasLast = false;
		if (func->HasAnyFunctionFlags(FUNC_Const))
		{
			result += "const ";
			hasLast = true;
		}
		if (func->HasAnyFunctionFlags(FUNC_Final))
		{
			result += "final ";
			hasLast = true;
		}

		if (func->GetSuperFunction() != nullptr)
		{
			result += "override ";
			hasLast = true;
		}
		if (hasLast)
		{
			result.RemoveAt(result.Len() - 1); //remove last " "
		}
		result += ";\n";
	}

	return result;
}

FString UInsiderSubsystem::PrintEnum(const UEnum* enumClass, EInsiderPrintFlags flags /*= EInsiderPrintFlags::EnumDefault*/, FString prefix /*= ""*/)
{
	FString result;

	if (EnumHasAnyFlags(flags, EInsiderPrintFlags::WithDetails))
	{
		INSIDER_VAR_PRIVATE_MEMBER(enumFlags, enumClass, UEnum, EnumFlags);
		result += FString::Printf(L"%s\tEnumFlags:\t%s\n", *prefix, *Insider::EnumFlagsToString(enumFlags));

		INSIDER_VAR_PRIVATE_MEMBER(displayNameFn, enumClass, UEnum, EnumDisplayNameFn);
		result += FString::Printf(L"%s\tEnumDisplayNameFn:\t%x\n", *prefix, displayNameFn);

		result += FString::Printf(L"%s\tCppType:\t%s\n", *prefix, *enumClass->CppType);
		result += FString::Printf(L"%s\tCppForm:\t%s\n", *prefix, *Insider::CppFormToString(enumClass->GetCppForm()));
	}

	if (EnumHasAnyFlags(flags, EInsiderPrintFlags::Properties))
	{
		result += prefix + "{\n";
		for (int i = 0; i < enumClass->NumEnums(); ++i)
		{
			FString name = enumClass->GetNameStringByIndex(i);
			int value = enumClass->GetValueByIndex(i);
			result += FString::Printf(L"%s\t%s = %d,\n", *prefix, *name, value);
		}
		result.RemoveAt(result.Len() - 2, 1);
		result += prefix + "};\n";
	}

	return result;
}

FString UInsiderSubsystem::PrintStruct(const UScriptStruct* structClass, const void* object /*= nullptr*/, TSet<const UObject*>& allObjects, EInsiderPrintFlags flags /*= EInsiderPrintFlags::StructDefault*/, FString prefix /*= ""*/)
{
	FString result;

	if (IsStructCustomized(structClass, object))
	{
		result += PrintStructCustomizedMap.FindChecked(structClass).Execute(structClass, object, allObjects, flags, prefix);
		return result;
	}

	result += PrintStructHeader(structClass, nullptr, flags, prefix);
	result += prefix + "{\n";
	result += PrintChildrenProperties(structClass, nullptr, allObjects, flags, prefix);
	result += prefix + "};\n";
	return result;
}

FString UInsiderSubsystem::PrintStructHeader(const UScriptStruct* structClass, const void* object /*= nullptr*/, EInsiderPrintFlags flags /*= EInsiderPrintFlags::StructDefault*/, FString prefix /*= ""*/)
{
	FString result;
	if (EnumHasAnyFlags(flags, EInsiderPrintFlags::WithDetails))
	{
		result += FString::Printf(L"%sStructFlags:\t%s\n", *prefix, *Insider::StructFlagsToString(structClass->StructFlags));
		result += FString::Printf(L"%sSize:\t%d\n", *prefix, structClass->PropertiesSize);
	}

	return result;
}

FString UInsiderSubsystem::PrintChildrenProperties(const UStruct* structObj, const void* object, TSet<const UObject*>& allObjects, EInsiderPrintFlags flags /*= EInsiderPrintFlags::ClassDefault*/, FString prefix /*= ""*/, bool sortProperties/*=true*/)
{
	FString result;
	//result += prefix + "{\n";

	if (EnumHasAnyFlags(flags, EInsiderPrintFlags::Properties))
	{
		TArray<const FProperty*> properties = GetProperties(structObj, flags, sortProperties);
		for (const FProperty* prop : properties)
		{
			result += PrintProperty(prop, object, allObjects, flags, prefix + "\t");
		}
	}
	//result += prefix + "};\n";

	return result;
}

FString UInsiderSubsystem::PrintClassInterfaces(const UClass* classObj, EInsiderPrintFlags flags /*= EInsiderPrintFlags::ClassDefault*/, FString prefix /*= ""*/)
{

	FString result;
	if (EnumHasAnyFlags(flags, EInsiderPrintFlags::Interfaces))
	{
		if (EnumHasAnyFlags(flags, EInsiderPrintFlags::WithDetails))
		{
			for (const FImplementedInterface& ii : classObj->Interfaces)
			{
				UClass* interfaceClass = ii.Class;
				result += FString::Printf(L"%s\tInterface:\t%s\n", *prefix, *interfaceClass->GetFullName());
				result += prefix + "\t{\n";
				for (TFieldIterator<const UFunction> i(interfaceClass, EFieldIteratorFlags::ExcludeSuper); i; ++i)
				{
					result += PrintObject(*i, flags, prefix + "\t\t");
				}
				result += prefix + "\t};\n";
			}
		}
		else
		{
			result += FString::Printf(L"%s\tInterface:\t", *prefix);
			for (const FImplementedInterface& ii : classObj->Interfaces)
			{
				UClass* interfaceClass = ii.Class;
				result += interfaceClass->GetFName().ToString();
				result += ", ";
			}

			if (classObj->Interfaces.Num() > 0)
			{
				result.RemoveAt(result.Len() - 2, 2);
			}
			result += "\n";
		}
	}
	return result;
}

FString UInsiderSubsystem::PrintClassFunctions(const UClass* classObj, EInsiderPrintFlags flags /*= EInsiderPrintFlags::ClassDefault*/, FString prefix /*= ""*/)
{

	FString result;
	if (EnumHasAnyFlags(flags, EInsiderPrintFlags::Functions))
	{
		EFieldIterationFlags fieldFlags = EnumHasAnyFlags(flags, EInsiderPrintFlags::WithSuper) ? EFieldIterationFlags::IncludeSuper : EFieldIterationFlags::None;

		for (TFieldIterator<const UFunction> i(classObj, fieldFlags); i; ++i)
		{
			if (IsObjectIgnored(i->GetOwnerClass()))
			{
				continue;
			}
			//result += PrintFunction(*i, flags, prefix + "\t\t");
			result += PrintObject(*i, flags, prefix + "\t");
		}
	}
	return result;
}


FString UInsiderSubsystem::PrintPackage(const UPackage* package, EInsiderPrintFlags flags /*= EInsiderPrintFlags::All*/, FString prefix /*= ""*/)
{

	FInsiderPrinter printer(prefix);

	const TArray<int32>& chunkIds = package->GetChunkIDs();


	const FPackagePath& packagePath = package->GetLoadedPath();
	FString path = packagePath.GetLocalFullPath();

	if (EnumHasAnyFlags(flags, EInsiderPrintFlags::WithDetails))
	{
		FInsiderPrinterScope scope(printer);

		uint32 packageFlags = package->GetPackageFlags();
		//FGuid guid = package->GetGuid();
		FGuid persistentGuid = package->GetPersistentGuid();
		uint64 fileSize = package->GetFileSize();
		float loadTime = package->GetLoadTime();
		FPackageFileVersion LinkerPackageVersion = package->GetLinkerPackageVersion();
		int32 LinkerLicenseeVersion = package->GetLinkerLicenseeVersion();

		FCustomVersionContainer LinkerCustomVersion = package->GetLinkerCustomVersions();

		printer += FString::Printf(L"%sLoadedPath:\t%s [%.3fKB]-%.3fms\n", *printer.Prefix, *path, fileSize / 1024.f, loadTime * 1000.f);
		printer.PrintNamedValue(TEXT("PackageFlags"), Insider::PackageFlagsToString((EPackageFlags)packageFlags));
		printer.PrintNamedValue(TEXT("Guid"), LexToString(((UPackage*)package)->GetSavedHash()));
		printer.PrintNamedValue(TEXT("PersistentGuid"), persistentGuid.ToString(EGuidFormats::DigitsWithHyphensLower).ToUpper());

		printer += FString::Printf(L"%sLinkerPackageVersion:\t[FileVersionUE4:%d,FileVersionUE5:%d]\n", *printer.Prefix, LinkerPackageVersion.FileVersionUE4, LinkerPackageVersion.FileVersionUE5);
		printer.PrintNamedValue(TEXT("LinkerLicenseeVersion"), LinkerLicenseeVersion);

		FString indent;
		printer.PrintNamedValue(TEXT("LinkerCustomVersion"), LinkerCustomVersion.ToString(indent));

	}


	FPackageReader reader;
	FPackageReader::EOpenPackageResult ErrorCode;

	if (!reader.OpenPackageFile(FStringView(path), &ErrorCode))
	{
		return printer.ToString();
	}

	FString longPackageName = reader.GetLongPackageName();

	TBitArray<> OutImportUsedInGame;
	TBitArray<> OutSoftPackageUsedInGame;
	reader.ReadEditorOnlyFlags(OutImportUsedInGame, OutSoftPackageUsedInGame);

	{
		//print summary
		FInsiderPrinterScope scope(printer);

		const FPackageFileSummary& summary = reader.GetPackageFileSummary();
		printer.PrintStructHeader(TEXT("Summary"));

		{
			FInsiderPrinterScope scope2(printer);

			printer += FString::Printf(L"%sTag:\t%x\n", *printer.Prefix, summary.Tag);
			printer.PrintNamedValue(TEXT("PackageFlags"), Insider::PackageFlagsToString((EPackageFlags)summary.GetPackageFlags()));

			PRINT_STRUCT_PROPERTY(printer, summary, TotalHeaderSize);
			PRINT_STRUCT_PROPERTY(printer, summary, PackageName);

			PRINT_STRUCT_PROPERTY(printer, summary, NameCount);
			PRINT_STRUCT_PROPERTY(printer, summary, NameOffset);

			PRINT_STRUCT_PROPERTY(printer, summary, SoftObjectPathsCount);
			PRINT_STRUCT_PROPERTY(printer, summary, SoftObjectPathsOffset);
			PRINT_STRUCT_PROPERTY(printer, summary, LocalizationId);

			PRINT_STRUCT_PROPERTY(printer, summary, GatherableTextDataCount);
			PRINT_STRUCT_PROPERTY(printer, summary, GatherableTextDataOffset);

			PRINT_STRUCT_PROPERTY(printer, summary, ExportCount);
			PRINT_STRUCT_PROPERTY(printer, summary, ExportOffset);

			PRINT_STRUCT_PROPERTY(printer, summary, ImportCount);
			PRINT_STRUCT_PROPERTY(printer, summary, ImportOffset);

			PRINT_STRUCT_PROPERTY(printer, summary, DependsOffset);

			PRINT_STRUCT_PROPERTY(printer, summary, SoftPackageReferencesCount);
			PRINT_STRUCT_PROPERTY(printer, summary, SoftPackageReferencesOffset);

			PRINT_STRUCT_PROPERTY(printer, summary, SearchableNamesOffset);
			PRINT_STRUCT_PROPERTY(printer, summary, ThumbnailTableOffset);

			printer.PrintNamedValue(TEXT("PersistentGuid"), summary.PersistentGuid.ToString(EGuidFormats::DigitsWithHyphensLower).ToUpper());
			printer.PrintNamedValue(TEXT("Guid"), LexToString(summary.GetSavedHash()));

			//generations
			{
				FInsiderPrinter_EnterArray GenerationsArray(printer, TEXT("Generations"), summary.Generations.Num());

				for (int i = 0; i < summary.Generations.Num(); ++i)
				{
					FInsiderPrinter_EnterArray_Item GenerationsArrayItem(printer, i);

					const FGenerationInfo& info = summary.Generations[i];
					printer.PrintNamedValue(TEXT("ExportCount"), info.ExportCount);
					printer.PrintNamedValue(TEXT("NameCount"), info.NameCount);
				}
			}

			printer.PrintNamedValue(TEXT("SavedByEngineVersion"), summary.SavedByEngineVersion.ToString());
			printer.PrintNamedValue(TEXT("CompatibleWithEngineVersion"), summary.CompatibleWithEngineVersion.ToString());

			printer.PrintNamedValue(TEXT("CompressionFlags"), Insider::CompressionFlagsToString((ECompressionFlags)summary.CompressionFlags));

			PRINT_STRUCT_PROPERTY(printer, summary, PackageSource);
			PRINT_STRUCT_PROPERTY(printer, summary, bUnversioned);
			PRINT_STRUCT_PROPERTY(printer, summary, AssetRegistryDataOffset);
			PRINT_STRUCT_PROPERTY(printer, summary, BulkDataStartOffset);
			PRINT_STRUCT_PROPERTY(printer, summary, WorldTileInfoDataOffset);

			//ChunkIDs
			{
				FInsiderPrinter_EnterArray ChunkIDsArray(printer, TEXT("ChunkIDs"), summary.ChunkIDs.Num());
				printer.Join(summary.ChunkIDs, TEXT(","));
			}
			PRINT_STRUCT_PROPERTY(printer, summary, PreloadDependencyCount);
			PRINT_STRUCT_PROPERTY(printer, summary, PreloadDependencyOffset);
			PRINT_STRUCT_PROPERTY(printer, summary, NamesReferencedFromExportDataCount);
			PRINT_STRUCT_PROPERTY(printer, summary, PayloadTocOffset);
			PRINT_STRUCT_PROPERTY(printer, summary, DataResourceOffset);

		}
	}


	{

		TArray<FName> NameMap;
		reader.GetNames(NameMap);

		FInsiderPrinterScope scope(printer);
		FInsiderPrinter_EnterArray NameMapArray(printer, TEXT("Names"), NameMap.Num());

		for (int i = 0; i < NameMap.Num(); ++i)
		{
			FInsiderPrinterScope scope2(printer);
			printer += FString::Printf(L"%s[%d]\t%s\n", *printer.Prefix, i, *NameMap[i].ToString());
		}
	}

	{

		TArray<FGatherableTextData> GatherableTextDataMap;
		reader.GetGatherableTextData(GatherableTextDataMap);

		FInsiderPrinterScope scope(printer);
		FInsiderPrinter_EnterArray NameMapArray(printer, TEXT("GatherableTextDataMap"), GatherableTextDataMap.Num());


		for (int i = 0; i < GatherableTextDataMap.Num(); ++i)
		{
			FInsiderPrinter_EnterArray_Item GatherableTextDataMapItem(printer, i);


			const FGatherableTextData& data = GatherableTextDataMap[i];
			printer.PrintNamedValue(TEXT("NamespaceName"), data.NamespaceName);
			printer.PrintStructHeader(TEXT("SourceData"));
			{
				FInsiderPrinterScope scope3(printer);
				printer.PrintNamedValue(TEXT("SourceString"), data.SourceData.SourceString);
				printer.PrintNamedValue(TEXT("SourceStringMetaData"), data.SourceData.SourceStringMetaData.ToString());
			}

			FInsiderPrinter_EnterArray SourceSiteContextsArray(printer, TEXT("SourceSiteContexts"), data.SourceSiteContexts.Num());

			for (int j = 0; j < data.SourceSiteContexts.Num(); ++j)
			{
				FInsiderPrinter_EnterArray_Item SourceSiteContextsArray_Item(printer, j);

				const FTextSourceSiteContext& context = data.SourceSiteContexts[i];
				printer.PrintNamedValue(TEXT("KeyName"), context.KeyName);
				printer.PrintNamedValue(TEXT("SiteDescription"), context.SiteDescription);
				printer.PrintNamedValue(TEXT("IsEditorOnly"), context.IsEditorOnly);
				printer.PrintNamedValue(TEXT("IsOptional"), context.IsOptional);
				printer.PrintNamedValue(TEXT("InfoMetaData"), context.InfoMetaData.ToString());
				printer.PrintNamedValue(TEXT("KeyMetaData"), context.KeyMetaData.ToString());
			}
		}
	}

	{
		TArray<FObjectImport> ImportMap;
		reader.GetImports(ImportMap);

		FInsiderPrinterScope scope(printer);
		FInsiderPrinter_EnterArray ImportMapArray(printer, TEXT("ImportMap"), ImportMap.Num());

		for (int i = 0; i < ImportMap.Num(); ++i)
		{
			FInsiderPrinter_EnterArray_Item ImportMap_Item(printer, i);

			const FObjectImport& item = ImportMap[i];

			printer.PrintNamedValue(TEXT("ClassPackage"), item.ClassPackage);
			printer.PrintNamedValue(TEXT("PackageName"), item.PackageName);
			printer.PrintNamedValue(TEXT("OuterIndex"), LexToString(item.OuterIndex));
			printer.PrintNamedValue(TEXT("ClassName"), item.ClassName);
			printer.PrintNamedValue(TEXT("ObjectName"), item.ObjectName);
			printer.PrintNamedValue(TEXT("bImportOptional"), item.bImportOptional);


			if (!OutImportUsedInGame.IsEmpty() && OutImportUsedInGame.IsValidIndex(i))
			{
				printer.PrintNamedValue(TEXT("IsUsedInGame"), (bool)OutImportUsedInGame[i]);
			}

		}
	}


	{
		FInsiderPrinterScope scope(printer);

		TArray<FObjectExport> ExportMap;
		reader.GetExports(ExportMap);

		FInsiderPrinter_EnterArray ExportMapArray(printer, TEXT("ExportMap"), ExportMap.Num());
		for (int i = 0; i < ExportMap.Num(); ++i)
		{
			FInsiderPrinter_EnterArray_Item ExportMap_Item(printer, i);

			const FObjectExport& item = ExportMap[i];

			printer.PrintNamedValue(TEXT("ObjectName"), item.ObjectName);
			printer.PrintNamedValue(TEXT("ObjectFlags"), Insider::ObjectFlagsToString(item.ObjectFlags));
			printer.PrintNamedValue(TEXT("PackageFlags"), Insider::PackageFlagsToString((EPackageFlags)item.PackageFlags));

			printer.PrintNamedValue(TEXT("ClassIndex"), LexToString(item.ClassIndex));
			printer.PrintNamedValue(TEXT("SuperIndex"), LexToString(item.SuperIndex));
			printer.PrintNamedValue(TEXT("TemplateIndex"), LexToString(item.TemplateIndex));
			printer.PrintNamedValue(TEXT("OuterIndex"), LexToString(item.OuterIndex));

			printer.PrintNamedValue(TEXT("SerialSize"), item.SerialSize);
			printer.PrintNamedValue(TEXT("SerialOffset"), item.SerialOffset);

			printer.PrintNamedValue(TEXT("bForcedExport"), item.bForcedExport);
			printer.PrintNamedValue(TEXT("bNotForClient"), item.bNotForClient);
			printer.PrintNamedValue(TEXT("bNotForServer"), item.bNotForServer);
			printer.PrintNamedValue(TEXT("bIsInheritedInstance"), item.bIsInheritedInstance);
			printer.PrintNamedValue(TEXT("bNotAlwaysLoadedForEditorGame"), item.bNotAlwaysLoadedForEditorGame);

			printer.PrintNamedValue(TEXT("bIsAsset"), item.bIsAsset);
			printer.PrintNamedValue(TEXT("bGeneratePublicHash"), item.bGeneratePublicHash);
			printer.PrintNamedValue(TEXT("FirstExportDependency"), item.FirstExportDependency);
			printer.PrintNamedValue(TEXT("SerializationBeforeSerializationDependencies"), item.SerializationBeforeSerializationDependencies);
			printer.PrintNamedValue(TEXT("CreateBeforeSerializationDependencies"), item.CreateBeforeSerializationDependencies);
			printer.PrintNamedValue(TEXT("SerializationBeforeCreateDependencies"), item.SerializationBeforeCreateDependencies);
			printer.PrintNamedValue(TEXT("CreateBeforeCreateDependencies"), item.CreateBeforeCreateDependencies);
			printer.PrintNamedValue(TEXT("ScriptSerializationStartOffset"), item.ScriptSerializationStartOffset);
			printer.PrintNamedValue(TEXT("ScriptSerializationEndOffset"), item.ScriptSerializationEndOffset);

		}
	}


	{

		TArray<FName> SoftPackageReferenceList;
		reader.GetSoftPackageReferenceList(SoftPackageReferenceList);

		FInsiderPrinterScope scope(printer);
		FInsiderPrinter_EnterArray myArray(printer, TEXT("SoftPackageReferenceList"), SoftPackageReferenceList.Num());

		for (int i = 0; i < SoftPackageReferenceList.Num(); ++i)
		{
			FInsiderPrinter_EnterArray_Item SoftPackageReferenceList_Item(printer, i);

			printer.PrintNamedValue(TEXT("SoftPackageReference"), SoftPackageReferenceList[i].ToString());
			if (!OutSoftPackageUsedInGame.IsEmpty() && OutSoftPackageUsedInGame.IsValidIndex(i))
			{
				printer.PrintNamedValue(TEXT("IsUsedInGame"), (bool)OutSoftPackageUsedInGame[i]);
			}
		}
	}

	{

		TArray<FSoftObjectPath> SoftObjectPathMap;
		reader.GetSoftObjectPaths(SoftObjectPathMap);

		FInsiderPrinterScope scope(printer);
		FInsiderPrinter_EnterArray myArray(printer, TEXT("SoftObjectPathMap"), SoftObjectPathMap.Num());

		for (int i = 0; i < SoftObjectPathMap.Num(); ++i)
		{
			FInsiderPrinterScope scope2(printer);
			printer += FString::Printf(L"%s[%d]\t%s\n", *printer.Prefix, i, *SoftObjectPathMap[i].ToString());
		}
	}


	{
		//export-depend packages

		TArray<TArray<FPackageIndex>> DependsMap;
		reader.GetDependsMap(DependsMap);

		FInsiderPrinterScope scope(printer);
		FInsiderPrinter_EnterArray myArray(printer, TEXT("DependsMap"), DependsMap.Num());

		for (int i = 0; i < DependsMap.Num(); ++i)
		{
			FInsiderPrinter_EnterArray_Item DependsMap_Item(printer, i);
			TArray<int32>* intArray = (TArray<int32>*) & DependsMap[i];
			printer.Join(*intArray, TEXT(","));
		}
	}


	FPackageDependencyData OutDependencyData;
	reader.ReadDependencyData(OutDependencyData, FPackageReader::EReadOptions::Default);
	if (OutDependencyData.bHasDependencyData)
	{
		{
			FInsiderPrinterScope scope(printer);
			FInsiderPrinter_EnterArray myArray(printer, TEXT("PackageDependencies"), OutDependencyData.PackageDependencies.Num());

			for (int i = 0; i < OutDependencyData.PackageDependencies.Num(); ++i)
			{
				FInsiderPrinter_EnterArray_Item PackageDependencies_Item(printer, i);

				const FPackageDependencyData::FPackageDependency& item = OutDependencyData.PackageDependencies[i];
				printer.PrintNamedValue(TEXT("PackageName"), item.PackageName);
				printer.PrintNamedValue(TEXT("Property"), Insider::DependencyPropertyToString(item.Property));
			}

		}

		{
			FInsiderPrinterScope scope(printer);
			FInsiderPrinter_EnterArray myArray(printer, TEXT("SearchableNameDependencies"), OutDependencyData.SearchableNameDependencies.Num());

			for (int i = 0; i < OutDependencyData.SearchableNameDependencies.Num(); ++i)
			{
				FInsiderPrinter_EnterArray_Item SearchableNameDependencies_Item(printer, i);

				const FPackageDependencyData::FSearchableNamesDependency& item = OutDependencyData.SearchableNameDependencies[i];
				printer.PrintNamedValue(TEXT("PackageName"), item.PackageName);
				printer.PrintNamedValue(TEXT("ObjectName"), item.ObjectName);

				{
					FInsiderPrinter_EnterArray ValueNamesArray(printer, TEXT("ValueNames"), item.ValueNames.Num());
					printer.Join(item.ValueNames, TEXT(","));
				}

			}
		}

	}


	{
		TArray<FObjectFullNameAndThumbnail> RawThumbnailMap;
		reader.GetThumbnails(RawThumbnailMap);
		if (package->HasThumbnailMap() && RawThumbnailMap.IsEmpty())
		{
			const FThumbnailMap& ThumbnailMap = package->GetThumbnailMap();
			for (const auto& kv : ThumbnailMap)
			{
				RawThumbnailMap.Emplace(kv.Key, &kv.Value);
			}
		}

		FInsiderPrinterScope scope(printer);
		FInsiderPrinter_EnterArray myArray(printer, TEXT("ThumbnailMap"), RawThumbnailMap.Num());

		for (int i = 0; i < RawThumbnailMap.Num(); ++i)
		{
			FInsiderPrinter_EnterArray_Item RawThumbnailMap_Item(printer, i);

			const FObjectFullNameAndThumbnail& item = RawThumbnailMap[i];
			printer.PrintNamedValue(TEXT("ObjectFullName"), item.ObjectFullName);
			if (item.ObjectThumbnail != nullptr)
			{
				printer.PrintStructHeader(TEXT("ObjectThumbnail"));
				printer.PrintNamedValue(TEXT("ImageWidth"), item.ObjectThumbnail->GetImageWidth());
				printer.PrintNamedValue(TEXT("ImageHeight"), item.ObjectThumbnail->GetImageHeight());
				printer.PrintNamedValue(TEXT("CompressedDataSize"), item.ObjectThumbnail->GetCompressedDataSize());
			}
			else
			{
				printer.PrintNamedValue(TEXT("ObjectThumbnail"), TEXT("nullptr"));
			}
		}
	}

	//Tile information used by WorldComposition.Defines properties necessary for tile positioning in the world. Stored with package summary
	if (FWorldTileInfo* WorldTileInfo = package->GetWorldTileInfo())
	{
		{
			FInsiderPrinterScope scope(printer);
			printer.PrintStructHeader(TEXT("WorldTileInfo"));

			printer.PrintNamedValue(TEXT("ParentTilePackageName"), WorldTileInfo->ParentTilePackageName);
			printer.PrintNamedValue(TEXT("ZOrder"), WorldTileInfo->ZOrder);

			printer.PrintNamedValue(TEXT("Position"), WorldTileInfo->Position.ToString());
			printer.PrintNamedValue(TEXT("AbsolutePosition"), WorldTileInfo->AbsolutePosition.ToString());
			printer.PrintNamedValue(TEXT("Bounds"), WorldTileInfo->Bounds.ToString());
			//printer.PrintNamedValue(TEXT("Layer"), WorldTileInfo->Layer);

			{
				printer.PrintStructHeader(TEXT("Layer"));
				FInsiderPrinterScope scope2(printer);
				printer.PrintNamedValue(TEXT("Name"), WorldTileInfo->Layer.Name);
				printer.PrintNamedValue(TEXT("StreamingDistance"), WorldTileInfo->Layer.StreamingDistance);
				printer.PrintNamedValue(TEXT("DistanceStreamingEnabled"), WorldTileInfo->Layer.DistanceStreamingEnabled);
			}

			{
				FInsiderPrinter_EnterArray myArray(printer, TEXT("LODList"), WorldTileInfo->LODList.Num());
				TArray<int32> lodValues;
				for (const auto& i : WorldTileInfo->LODList)
				{
					lodValues.Add(i.RelativeStreamingDistance);
				}

				printer.Join(lodValues, TEXT(","));

			}

		}
	}
	else
	{
		FInsiderPrinterScope scope(printer);
		printer.PrintNamedValue(TEXT("WorldTileInfo"), TEXT("nullptr"));
	}


	//TArray<FAssetData*> AssetDataList;
	//bool bOutIsCookedWithoutAssetData;
	//reader.ReadAssetRegistryData(AssetDataList, bOutIsCookedWithoutAssetData);

	//TMap<FSoftObjectPath, FPackageReader::FObjectData> OutExports;
	//TMap<FSoftObjectPath, FPackageReader::FObjectData> OutImports;
	//TMap<FName, bool> OutSoftPackageReferences;
	//reader.ReadLinkerObjects(OutExports, OutImports, OutSoftPackageReferences);


	//FPackageReader

	return printer.ToString();
}

TArray<const FProperty*> UInsiderSubsystem::GetProperties(const UStruct* outer, EInsiderPrintFlags flags /*= EInsiderPrintFlags::ClassDefault*/, bool sort/*=true*/)
{
	EInsiderPrintFlags propertyFlags = flags;
	/*if (EnumHasAnyFlags(propertyFlags, EInsiderPrintFlags::Class))
	{
		EnumRemoveFlags(propertyFlags, EInsiderPrintFlags::Parameters);
	}*/

	EFieldIterationFlags fieldFlags = EnumHasAnyFlags(flags, EInsiderPrintFlags::WithSuper) ? EFieldIterationFlags::IncludeSuper : EFieldIterationFlags::None;

	TArray<const FProperty*> properties;
	for (TFieldIterator<const FProperty> i(outer, fieldFlags); i; ++i)
	{
		if (IsObjectIgnored(i->GetOwnerClass()))
		{
			continue;
		}
		properties.Add(*i);
	}

	if (sort)
	{
		properties.Sort(FPropertyOffsetAscending());
	}

	return properties;
}

bool UInsiderSubsystem::IsContainerProperty(const FProperty* property)
{
	if (const FArrayProperty* arrayProperty = CastField<const FArrayProperty>(property))
	{
		return true;

	}
	else if (const FSetProperty* setProperty = CastField<const FSetProperty>(property))
	{
		return true;

	}
	else if (const FMapProperty* mapProperty = CastField<const FMapProperty>(property))
	{
		return true;
	}
	return false;
}

FString UInsiderSubsystem::GetPropertyCPPTypeString(const FProperty* property)
{
	FString result = property->GetCPPType();
	FString extendedText;

	if (const FArrayProperty* arrayProperty = CastField<const FArrayProperty>(property))
	{
		//const FProperty* itemProperty = arrayProperty->Inner;
		//FString innerTypeString = itemProperty->GetCPPType();
		arrayProperty->GetCPPType(&extendedText, 0);
	}
	else if (const FSetProperty* setProperty = CastField<const FSetProperty>(property))
	{
		//const FProperty* itemProperty = setProperty->GetElementProperty();
		//FString innerTypeString = itemProperty->GetCPPType();
		//result = setProperty->GetCPPType(&innerTypeString, 0);
		setProperty->GetCPPType(&extendedText, 0);

	}
	else if (const FMapProperty* mapProperty = CastField<const FMapProperty>(property))
	{
		const FProperty* keyProperty = mapProperty->GetKeyProperty();
		const FProperty* valueProperty = mapProperty->GetValueProperty();

		mapProperty->GetCPPType(&extendedText, 0);
	}
	else
	{

	}

	result += extendedText;
	return result;
}

FString UInsiderSubsystem::PrintPropertyHeader(const FProperty* prop, EInsiderPrintFlags flags /*= EInsiderPrintFlags::PropertyDefault*/, FString prefix /*= ""*/)
{
	if (prop == nullptr)
	{
		return "";
	}

	FString result;
	if (EnumHasAnyFlags(flags, EInsiderPrintFlags::Header))
	{
		UObject* outer = prop->GetOwnerUObject();

		FString outerName = outer != nullptr ? outer->GetFullName() : TEXT("nullptr");
		result += FString::Printf(L"%s\tObjectFlags:\t%s\n", *prefix, *Insider::ObjectFlagsToString(prop->GetFlags()));
		result += FString::Printf(L"%s\tOuter:\t%s\n", *prefix, *outerName);
		result += FString::Printf(L"%s\tPath:\t%s\n", *prefix, *prop->GetFullName());

	}
	return result;
}


FString UInsiderSubsystem::GetClassHierarchyString(const UStruct* classObj, bool includeSelf/*=true*/, bool includeChildren/*=true*/)
{
	//FString result = classObj->GetFName().ToString();
	//result += ":";

	TArray<FString> classNames;
	if (includeSelf)
	{
		classNames.Add(classObj->GetName());
	}
	if (includeChildren)
	{
		UStruct* superClass = classObj->GetSuperStruct();
		while (superClass)
		{
			classNames.Add(superClass->GetName());
			superClass = superClass->GetSuperStruct();
		}
	}

	//result += FString::Join(classNames, TEXT("->"));
	//return result;
	return FString::Join(classNames, TEXT("->"));
}


#pragma endregion Trace

#pragma region Store

UObject* UInsiderSubsystem::K2_NewObject(UClass* objClass, FName objName)
{
	FStaticConstructObjectParameters p(objClass);
	p.Name = objName;


	UObject* obj = StaticConstructObject_Internal(p);
	if (obj != nullptr)
	{
		obj->AddToRoot();
	}
	return obj;
}


FString UInsiderSubsystem::PrintAllPackages()
{
	TArray<UObject*> result;
	GetObjectsOfClass(UPackage::StaticClass(), result);

	FString str;
	str += FString::Printf(L"\nPackage[%d]\n", result.Num());
	for (UObject* obj : result)
	{
		str += FString::Printf(L"Package:\t%s\n", *obj->GetFullName());
	}
	return str;
}

FString UInsiderSubsystem::PrintAllUClasses()
{
	TArray<UObject*> result;
	GetObjectsOfClass(UClass::StaticClass(), result);

	FString str;
	str += FString::Printf(L"\nClass[%d]\n", result.Num());
	for (UObject* obj : result)
	{
		str += FString::Printf(L"Class:\t%s\n", *obj->GetFullName());
	}
	return str;
}

FString UInsiderSubsystem::PrintAllEnums()
{
	TArray<UObject*> result;
	GetObjectsOfClass(UEnum::StaticClass(), result);

	FString str;
	str += FString::Printf(L"\nEnum[%d]\n", result.Num());
	for (UObject* obj : result)
	{
		str += FString::Printf(L"Enum:\t%s\n", *obj->GetFullName());
	}
	return str;
}

FString UInsiderSubsystem::PrintAllStructs()
{
	TArray<UObject*> result;
	GetObjectsOfClass(UScriptStruct::StaticClass(), result);

	FString str;
	str += FString::Printf(L"\nStruct[%d]\n", result.Num());
	for (UObject* obj : result)
	{
		str += FString::Printf(L"Struct:\t%s\n", *obj->GetFullName());
	}
	return str;
}


FString UInsiderSubsystem::PrintObjectsWithOuter(UObject* outer)
{
	TArray<UObject*> result;
	GetObjectsWithOuter(outer, result);
	FString str;
	str += FString::Printf(L"\nObject[%d]\n", result.Num());
	for (UObject* obj : result)
	{
		str += FString::Printf(L"Object:\t%s\n", *obj->GetFullName());
	}
	return str;
}

FString UInsiderSubsystem::PrintAllObjectsWithRawObjectIterator()
{
	auto begin = FPlatformTime::Cycles64();
	TArray<UObject*> allObjects;
	for (FRawObjectIterator It(false); It; ++It)
	{
		FUObjectItem* ObjectItem = *It;
		UObject* obj = (UObject*)ObjectItem->Object;
		if (obj->IsA<UClass>())
		{
			allObjects.Add(obj);
		}
	}
	auto elpsed = FPlatformTime::Cycles64() - begin;
	FString str;
	str += FString::Printf(L"Cost: %f", FPlatformTime::ToMilliseconds(elpsed));
	return str;
}

FString UInsiderSubsystem::PrintAllObjectsFObjectIterator()
{
	auto begin = FPlatformTime::Cycles64();
	TArray<UObject*> allObjects;
	for (FThreadSafeObjectIterator It(UClass::StaticClass()); It; ++It)
	{
		UObject* obj = *It;
		allObjects.Add(obj);
	}

	auto elpsed = FPlatformTime::Cycles64() - begin;
	FString str;
	str += FString::Printf(L"Cost: %f", FPlatformTime::ToMilliseconds(elpsed));
	return str;
}

FString UInsiderSubsystem::PrintAllObjectsTObjectIterator()
{
	auto begin = FPlatformTime::Cycles64();
	TArray<UObject*> allObjects;
	for (TObjectIterator<UClass> It; It; ++It)
	{
		UObject* obj = *It;
		allObjects.Add(obj);
	}

	auto elpsed = FPlatformTime::Cycles64() - begin;
	FString str;
	str += FString::Printf(L"Cost: %f", FPlatformTime::ToMilliseconds(elpsed));
	return str;
}

struct FMetaDataInfo
{
public:
	FMetaDataInfo() = default;
	FMetaDataInfo(FString str, UObject* obj) :Key(str), OuterObject(obj) {}

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Key;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UObject* OuterObject;

	friend uint32 GetTypeHash(const FMetaDataInfo& item) { return GetTypeHashHelper(item.Key); }
	bool operator==(const FMetaDataInfo& other)const { return Key == other.Key; }

	FString ToString()const
	{
		return FString::Printf(TEXT("%s: %s"), *Key, *OuterObject->GetFullName());
	}
};


FString UInsiderSubsystem::PrintAllMetaDataKeys()
{
	TSortedMap<FString, FMetaDataInfo> AllKeys;

	auto AddKey = [&AllKeys](FName key, UObject* outerObject)->bool
		{
			FString keyString = key.ToString();
			int32 dotIndex = -1;
			if (keyString.FindChar('.', dotIndex))
			{
				keyString = keyString.RightChop(dotIndex + 1);
			}

			if (keyString.StartsWith(TEXT("CPP_Default_")))
			{
				return false;
			}

			if (!AllKeys.Contains(keyString))
			{
				AllKeys.Add(keyString) = FMetaDataInfo(keyString, outerObject);
				return true;
			}
			return false;
		};

	for (TObjectIterator<UMetaData> It; It; ++It)
	{
		UMetaData* MetaData = *It;

		for (TMap< FWeakObjectPtr, TMap<FName, FString> >::TIterator j(MetaData->ObjectMetaDataMap); j; ++j)
		{
			TMap<FName, FString>& MetaDataValues = j.Value();

			for (TMap<FName, FString>::TIterator MetaDataIt(MetaDataValues); MetaDataIt; ++MetaDataIt)
			{
				FName Key = MetaDataIt.Key();
				AddKey(Key, j.Key().Get());
			}
		}

		for (TMap<FName, FString>::TIterator MetaDataIt(MetaData->RootMetaDataMap); MetaDataIt; ++MetaDataIt)
		{
			FName Key = MetaDataIt.Key();
			AddKey(Key, MetaData->GetOuter());
		}
	}

	FString str;
	str += FString::Printf(TEXT("Keys:%d\n"), AllKeys.Num());
	for (auto& kv : AllKeys)
	{
		str += FString::Printf(TEXT("%s\n"), *kv.Value.ToString());
	}
	return str;
}

#pragma endregion Store

#pragma region Reflection


FString UInsiderSubsystem::PrintDerivedClasses(UClass* objClass, bool recursive)
{
	TArray<UClass*> result;
	GetDerivedClasses(objClass, result, false);
	FString str;
	str += FString::Printf(L"\nClass:%s\n", *objClass->GetName());
	for (UClass* obj : result)
	{
		str += FString::Printf(L"\t%s\n", *obj->GetFullName());
		if (recursive)
		{
			PrintDerivedClassesHelper(obj, str, 2);
		}
	}

	return str;
}


FString UInsiderSubsystem::PrintSuperClasses(UClass* objClass)
{
	FString str;
	TArray<FString> classNames;
	classNames.Add(objClass->GetName());
	UClass* superClass = objClass->GetSuperClass();
	while (superClass)
	{
		classNames.Add(superClass->GetName());
		superClass = superClass->GetSuperClass();
	}
	str += "\t";
	str += FString::Join(classNames, TEXT("->"));
	str += "\n";

	return str;
}

FString UInsiderSubsystem::PrintInterfacesWithClass(UClass* objClass)
{
	//objClass->ImplementsInterface()
	FString str;
	for (FImplementedInterface& ii : objClass->Interfaces)
	{
		UClass* interfaceClass = ii.Class;
		str += FString::Printf(TEXT("\t%s\n"), *interfaceClass->GetFullName());
	}
	return str;
}

FString UInsiderSubsystem::PrintClassesWithInterface(UClass* interfaceClass)
{
	TArray<UObject*> result;
	GetObjectsOfClass(UClass::StaticClass(), result);

	TArray<UClass*> classes;
	for (UObject* obj : result)
	{
		UClass* classObj = Cast<UClass>(obj);
		if (classObj->ImplementsInterface(interfaceClass))
		{
			classes.Add(classObj);
		}
	}

	FString str;
	str += FString::Printf(TEXT("\nClass[%d]\n"), classes.Num());
	for (UClass* classObj : classes)
	{
		str += FString::Printf(TEXT("Class:\t%s\n"), *classObj->GetFullName());
	}
	return str;
}

FString UInsiderSubsystem::K2_PrintProperty(UObject* obj, FName propertyName)
{
	FString str;
	UClass* classObj = obj->GetClass();
	if (FProperty* prop = classObj->FindPropertyByName(propertyName))
	{
		FString valueStr;
		prop->ExportTextItem_Direct(valueStr, prop->ContainerPtrToValuePtr<const void*>(obj), nullptr, obj, PPF_None);
		FString defaultValueStr;
		prop->ExportTextItem_Direct(defaultValueStr, prop->ContainerPtrToValuePtr<const void*>(classObj->GetDefaultObject()), nullptr, classObj->GetDefaultObject(), PPF_None);

		str += FString::Printf(TEXT("\t%s=%s. Default:%s\n"), *propertyName.ToString(), *valueStr, *defaultValueStr);
	}
	else
	{
		str += FString::Printf(TEXT("\tCannot find Property:\t%s\n"), *propertyName.ToString());
	}
	return str;
}

FString UInsiderSubsystem::SetPropertyValue(UObject* obj, FName propertyName, FString valueStr)
{
	FString str;
	UClass* classObj = obj->GetClass();
	if (FProperty* prop = classObj->FindPropertyByName(propertyName))
	{
		prop->ImportText_Direct(*valueStr, prop->ContainerPtrToValuePtr<const void*>(obj), obj, PPF_None);
		str += FString::Printf(TEXT("\tSet %s=%s\n"), *propertyName.ToString(), *valueStr);
	}
	else
	{
		str += FString::Printf(TEXT("\tCannot find Property:\t%s\n"), *propertyName.ToString());
	}
	return str;
}


void UInsiderSubsystem::PrintDerivedClassesHelper(UClass* objClass, FString& str, int depth)
{
	TArray<UClass*> result;
	GetDerivedClasses(objClass, result, false);
	for (UClass* obj : result)
	{
		for (int i = 0; i < depth; ++i)
		{
			str.AppendChar('\t');
		}
		str += FString::Printf(TEXT("%s\n"), *obj->GetFullName());
		PrintDerivedClassesHelper(obj, str, depth + 1);
	}
}


UObject* UInsiderSubsystem::FindObjectWithName(FString objName, UObject* parent/*=nullptr*/)
{
	if ((!parent) && !FPackageName::IsValidObjectPath(objName))
	{
		// Try to find first object matching the provided name
		return StaticFindFirstObject(nullptr, *objName, EFindFirstObjectOptions::EnsureIfAmbiguous);
	}
	else
	{
		return StaticFindObject(nullptr, parent, *objName);
	}
}

UObject* UInsiderSubsystem::FindObjectWithNameSmart(FString objName, UObject* parent/*=nullptr*/)
{
	if (UObject* obj = FindObjectWithName(objName, parent))
	{
		return obj;
	}
	//try again with smart name
	if (objName.StartsWith(TEXT("U")) || objName.StartsWith(TEXT("F")) || objName.StartsWith(TEXT("A")))
	{
		objName.RemoveAt(0);
	}
	//search again
	if (UObject* obj = FindObjectWithName(objName, parent))
	{
		return obj;
	}

	return nullptr;
}


UScriptStruct* UInsiderSubsystem::FindStructWithName(FName structName)
{
	TArray<UObject*> result;
	GetObjectsOfClass(UScriptStruct::StaticClass(), result);

	FString str;
	int32 count = 0;
	for (UObject* obj : result)
	{
		UScriptStruct* ss = Cast<UScriptStruct>(obj);
		if (ss->GetFName() == structName)
		{
			return ss;
		}
	}

	return nullptr;
}

FString UInsiderSubsystem::FindAllStructsWithFlag(EStructFlags structFlags)
{
	TArray<UObject*> result;
	GetObjectsOfClass(UScriptStruct::StaticClass(), result);

	FString str;
	int32 count = 0;
	for (UObject* obj : result)
	{
		UScriptStruct* ss = Cast<UScriptStruct>(obj);
		if ((ss->StructFlags & structFlags) != 0)
		{
			++count;
			str += FString::Printf(L"Struct:\t%s\n", *obj->GetFullName());
		}
	}

	FString header = FString::Printf(L"\nStruct[%d] WithFlags:%s\n", count, *Insider::StructFlagsToString(structFlags));
	str = header + str;

	return str;
}

FString UInsiderSubsystem::FindAllClassesWithFlag(EClassFlags flags)
{
	TArray<UObject*> result;
	GetObjectsOfClass(UClass::StaticClass(), result);

	FString str;
	int32 count = 0;
	for (UObject* obj : result)
	{
		UClass* ss = Cast<UClass>(obj);
		if ((ss->ClassFlags & flags) != 0)
		{
			++count;
			str += FString::Printf(L"%s\n", *obj->GetFullName());
		}
	}

	FString header = FString::Printf(L"\nClass[%d] WithFlags:%s\n", count, *Insider::ClassFlagsToString(flags));
	str = header + str;

	return str;
}

FString UInsiderSubsystem::FindAllClassesWithoutFlag(EClassFlags flags)
{
	TArray<UObject*> result;
	GetObjectsOfClass(UClass::StaticClass(), result);

	FString str;
	int32 count = 0;
	for (UObject* obj : result)
	{
		UClass* ss = Cast<UClass>(obj);
		if ((ss->ClassFlags & flags) == 0)
		{
			++count;
			str += FString::Printf(L"%s\n", *obj->GetFullName());
		}
	}

	FString header = FString::Printf(L"\nClass[%d] WithoutFlags:%s\n", count, *Insider::ClassFlagsToString(flags));
	str = header + str;

	return str;
}

bool UInsiderSubsystem::IsObjectIgnored(const UObject* obj)
{
	if (obj == nullptr)
	{
		return false;
	}
	FString objName = obj->GetName();

	const static TSet<FString> ignoredObjNames{ TEXT("ExecuteUbergraph"), "Actor" };

	return ignoredObjNames.Contains(objName);
}

bool UInsiderSubsystem::IsObjectCustomized(const UObject* obj)
{
	if (obj == nullptr)
	{
		return false;
	}

	UClass* objClass = obj->GetClass();
	return PrintObjectCustomizedMap.Contains(objClass);
}

bool UInsiderSubsystem::IsStructCustomized(const UScriptStruct* structClass, const void* object)
{
	if (object == nullptr)
	{
		return false;
	}

	return PrintStructCustomizedMap.Contains(structClass);

}

bool UInsiderSubsystem::IsStructPrintOnelineSupported(const UScriptStruct* structClass, const void* object)
{
	if (object == nullptr)
	{
		return false;
	}

	return IsStructPrintOnelineSupportedMap.Contains(structClass);
}

FString UInsiderSubsystem::AddQuoteToStringIfSuitable(const FString& InString)
{
	int32 charIndex = InString.FindLastCharByPredicate([](TCHAR c)
	{
		return c==' '||c=='\r'||c=='\n'||c=='\t'||c==','||c=='|';
	});

	if (charIndex==INDEX_NONE)
	{
		return InString;
	}

	FString result=TEXT("\"");
	result+=InString;
	result+=TEXT("\"");
	return result;
}

#pragma endregion Reflection


void UInsiderSubsystem::PrintFuncStatus(AActor* actor, FString funcName)
{
	if (actor == nullptr)
		return;

	FString ownerShip;
	{
		AActor* owner = actor;
		for (owner; owner != nullptr; owner = owner->Owner)
		{
			ownerShip += owner->GetName();
			ownerShip += " -> ";
		}
		if (ownerShip.IsEmpty())
		{
			ownerShip = TEXT("NoOwner");
		}
		else
		{
			ownerShip.RemoveAt(ownerShip.Len() - 4, 4);
		}
	}

	FString actorName = actor->GetName();

	FString localRoleStr;
	UEnum::GetValueAsString(actor->GetLocalRole(), localRoleStr);

	FString remoteRoleStr;
	UEnum::GetValueAsString(actor->GetRemoteRole(), remoteRoleStr);

	FString netModeStr = Insider::NetModeToString(actor->GetNetMode());


	FString str = FString::Printf(TEXT("%x\t%s\t%s\t%s\tLocal:%s\tRemote:%s"), (void*)actor, *funcName, *ownerShip, *netModeStr, *localRoleStr, *remoteRoleStr);
	GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red, str);

	UE_LOG(LogInsider, Display, TEXT("%s"), *str);
}

//used to steal private class member from ue source code
//struct UClass_FuncMap
//{
//	typedef TMap<FName, UFunction*> UClass::*type;
//	friend type get(UClass_FuncMap);
//};
//
//template<typename Tag, typename Tag::type M>
//struct Rob
//{
//	friend typename Tag::type get(Tag) { return M; }
//};
//
//
//template struct Rob<UClass_FuncMap, &UClass::FuncMap>;


FString UInsiderSubsystem::PrintMetaData(const UObject* obj, FString prefix, FString suffix)
{
#if WITH_METADATA
	UMetaData* metaData = obj->GetOutermost()->GetMetaData();
	const TMap<FName, FString>* keyValues = nullptr;
	if (const UPackage* package = Cast<const UPackage>(obj))
	{
		keyValues = &metaData->RootMetaDataMap;

		FString result;
		result += PrintMetaDataMapInline(TEXT("ROOT"), keyValues, prefix, suffix);
		if (!metaData->ObjectMetaDataMap.IsEmpty())
		{
			result += "\n";
			for (const auto& kv : metaData->ObjectMetaDataMap)
			{
				UObject* innerObj = kv.Key.Get();
				FString innerObjName = innerObj != nullptr ? innerObj->GetName() : TEXT("nullptr");
				keyValues = &kv.Value;
				result += PrintMetaDataMapInline(innerObjName, keyValues, prefix, suffix);
				result += "\n";
			}
			result.RemoveAt(result.Len() - 1);	//remove last \n
		}
		return result;
	}
	else
	{
		keyValues = metaData->GetMapForObject(obj);
		return PrintMetaDataMapInline(TEXT(""), keyValues, prefix, suffix);
	}

#else
	return "";
#endif
}


FString UInsiderSubsystem::PrintMetaDataMapInline(FString objName, const TMap<FName, FString>* keyValues, FString prefix /*= ""*/, FString suffix /*= "\n"*/)
{
#if WITH_METADATA
	if (keyValues != nullptr && keyValues->Num() > 0)
	{
		FString result = prefix;
		result += "(";
		if (!objName.IsEmpty())
		{
			result += objName;
			result += ":\t";
		}

		for (const auto& i : *keyValues)
		{
			FName name = i.Key;
			if (IgnoreCommentAndToolTip && (name == TEXT("Comment") || name == TEXT("ToolTip")))	//skip comment and tooltip
			{
				continue;
			}
			FString value = AddQuoteToStringIfSuitable(i.Value);
			result += FString::Printf(TEXT("%s = %s, "), *i.Key.ToString(), *value);
		}
		result.RemoveAt(result.Len() - 2, 2);
		result += ")";
		result += suffix;
		return result;
	}
	else
	{
		return "";
	}
#else
	return "";
#endif
}


FString UInsiderSubsystem::PrintMetaDataMapKeyValues(FString objName, const TMap<FName, FString>& keyValues, FString prefix /*= ""*/)
{
	FString result;
	result += FString::Printf(TEXT("%s%s:\n"), *prefix, *objName);
	for (const auto& i : keyValues)
	{
		FName name = i.Key;
		if (name == TEXT("Comment") || name == TEXT("ToolTip"))	//skip comment and tooltip
		{
			continue;
		}
		result += FString::Printf(TEXT("%s\t%s\t=\t%s\n"), *prefix, *i.Key.ToString(), *i.Value);
	}

	return result;
}

FString UInsiderSubsystem::PrintMetaDataObjectCustomized(const UClass* classObj, const UObject* object, TSet<const UObject*>& allObjects, EInsiderPrintFlags flags /*= EInsiderPrintFlags::ClassDefault*/, FString prefix /*= ""*/)
{
	FString result;
#if WITH_METADATA
	const UMetaData* metaData = Cast<UMetaData>(object);

	const TMap<FName, FString>* keyValues = &metaData->RootMetaDataMap;

	result += PrintMetaDataMapKeyValues(TEXT("ROOT"), metaData->RootMetaDataMap, prefix + "\t");
	if (!metaData->ObjectMetaDataMap.IsEmpty())
	{
		//result += "\n";
		for (const auto& kv : metaData->ObjectMetaDataMap)
		{
			UObject* innerObj = kv.Key.Get();
			FString innerObjName = innerObj != nullptr ? innerObj->GetName() : TEXT("nullptr");
			keyValues = &kv.Value;
			result += PrintMetaDataMapKeyValues(innerObjName, kv.Value, prefix + "\t");
			//result += "\n";
		}
		result.RemoveAt(result.Len() - 1);	//remove last \n
	}
	return result;
#else
	return "";
#endif
}

FString UInsiderSubsystem::PrintGuidCustomized(const UScriptStruct* structClass, const void* object, TSet<const UObject*>& allObjects, EInsiderPrintFlags flags /*= EInsiderPrintFlags::ClassDefault*/, FString prefix /*= ""*/)
{
	FString result;;
	const FGuid* guid = (const FGuid*)object;
	result += guid->ToString(EGuidFormats::DigitsWithHyphensLower).ToUpper();
	return result;
}

FString UInsiderSubsystem::PrintCoreStructsCustomized(const UScriptStruct* structClass, const void* object, TSet<const UObject*>& allObjects, EInsiderPrintFlags flags /*= EInsiderPrintFlags::ClassDefault*/, FString prefix /*= ""*/)
{
	FString result;
	FString objectValue;
	structClass->ExportText(objectValue, object, nullptr, nullptr, PPF_None, nullptr);
	result += objectValue;
	return result;
}
