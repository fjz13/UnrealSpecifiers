// Fill out your copyright notice in the Description page of Project Settings.

#include "Insider.h"
#include "Modules/ModuleManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Misc/Paths.h"
#include "Utility/InsiderSubsystem.h"
#include "Class/MyClass_Default.h"
#include "Class/Display/MyClass_ShowFunction.h"
#include "Class/Blueprint/MyClass_Blueprintable.h"
#include "Class/Blueprint/MyClass_BlueprintType.h"
#include "Class/DllExport/MyClass_WithoutAPI.h"

#include "Class/UHT/MyClass_Intrinsic.h"
#include "Class/Blueprint/MyClass_Abstract.h"

#include "Class/Blueprint/MyClass_Const.h"
#include "Class/DllExport/MyClass_MinimalAPI.h"
#include "Class/Display/MyComponent_ClassGroup.h"

#include "Class/Instance/MyClass_Within.h"
#include "Class/Serialization/MyClass_Transient.h"
#include "UObject/SavePackage.h"


#include "Utility/Log.h"
#include "ObjectEditorUtils.h"
#include <Class/Display/MyClass_Deprecated.h>
#include <Class/Serialization/MyClass_Optional.h>
#include <Utility/SerializationLibrary.h>

#if WITH_EDITOR
#include "Kismet2/KismetEditorUtilities.h"
#endif

#include <Class/Config/MyClass_Config.h>

#include "AssetRegistry/IAssetRegistry.h"

#include "Class/Serialization/MyClass_MatchedSerializers.h"


#include "Function/Wildcard/MyFunction_Custom.h"
#include <Class/Behavior/MyClass_LoadBehavior.h>
#include "Property/Config/MyProperty_Config.h"
#include <Enum/MyEnum_Flags.h>


#if WITH_EDITOR
static int32 GetHiddenFunctions(uint32 Indent, UClass* Class, bool bShowFunLibs, FString& JsonOut)
{
	int32 HiddenFuncCount = 0;

	FString IndentString;
	JsonOut += IndentString + TEXT("\"HiddenFunctions\" : [");

	FString& OutputString = JsonOut;
	UClass* CallingClass = Class;
	auto FindHiddenFuncs = [&IndentString, &CallingClass, &HiddenFuncCount, &OutputString](UClass* FunctionClass)
		{
			for (TFieldIterator<UFunction> FunctionIt(FunctionClass, EFieldIteratorFlags::IncludeSuper); FunctionIt; ++FunctionIt)
			{
				UFunction* Function = *FunctionIt;
				if (FObjectEditorUtils::IsFunctionHiddenFromClass(Function, CallingClass))
				{
					++HiddenFuncCount;
					OutputString += TEXT("\n\t") + IndentString + TEXT("\"") + Function->GetPathName() + TEXT("\",");
				}
			}

			/*for (TFieldIterator<FObjectProperty> PropIt(FuncClass, EFieldIteratorFlags::IncludeSuper); PropIt; ++PropIt)
			{
				UClass* PropClass = PropIt->PropertyClass;
				for (TFieldIterator<UFunction> FunctionIt(PropClass, EFieldIteratorFlags::IncludeSuper); FunctionIt; ++FunctionIt)
				{
					if (FObjectEditorUtils::IsFunctionHiddenFromClass(*FunctionIt, ThisClass))
					{
						++HiddenFuncCount;
						OutputString += TEXT("\n\t\t\t\"") + FunctionIt->GetPathName() + TEXT("\",");
					}
				}
			}*/
		};

	FindHiddenFuncs(CallingClass); // find all this class's functions

	if (bShowFunLibs)
	{
		for (TObjectIterator<UClass> ClassIt; ClassIt; ++ClassIt) // find all functions in each function library
		{
			UClass* TestClass = *ClassIt;
			// if this is a skeleton class, don't bother
			if (FKismetEditorUtilities::IsClassABlueprintSkeleton(TestClass))
			{
				continue;
			}

			if (TestClass->IsChildOf(UBlueprintFunctionLibrary::StaticClass()))
			{
				FindHiddenFuncs(TestClass);
			}
		}
	}
	if (HiddenFuncCount > 0)
	{
		OutputString.RemoveAt(OutputString.Len() - 1); // remove the last comma
	}
	OutputString += TEXT("\n") + IndentString + TEXT("]");

	return HiddenFuncCount;
}
#endif



void FInsiderModule::StartupModule()
{

	//UMyActor_EnumBitFlags_Test::TestFlags();
	//UMyProperty_Config_Test::TestConfigLoad();

	//UMyProperty_Config_Test::TestConfigLoad();


	//UMyClass_LoadBehaviorTest::RegisterObjectHandleCallback();

	//UMyClass_Abstract* obj=NewObject<UMyClass_Abstract>();

	//UClass* classObj=UMyClass_NoUCLASS::StaticClass();
	//UMyClass_NoUCLASS* obj=NewObject<UMyClass_NoUCLASS>();


	//UMyClass_Within_Outer* objOuter = NewObject<UMyClass_Within_Outer>();
	//UMyClass_Within* obj=NewObject<UMyClass_Within>(objOuter);

	/*TMultiMap<FName,FString> tagValues;
	tagValues.Add(TEXT("MyIdForSearch"),TEXT("MyId456"));
	TArray<FAssetData> outAssets;
	IAssetRegistry::Get()->GetAssetsByTagValues(tagValues,outAssets);*/
	//UMyClass_MatchedSerializers_Test::RunExportTest();
	//UMyClass_MatchedSerializers_Test::PrintFlagClasses();

	//UMyProperty_SerializationText_Test::RunExportTest();
	//UMyProperty_Serialization_Test::RunTest();
	//UMyClass_Transient_Test::RunTest();
	//UMyClass_EditorConfig_Test::RunTest();
	//FString str1= UInsiderSubsystem::FindAllStructsWithFlag(STRUCT_Atomic);
	//FString str2= UInsiderSubsystem::FindAllStructsWithFlag(STRUCT_NoExport);
	//FString str1= UInsiderSubsystem::FindAllStructsWithFlag(STRUCT_Immutable);



	//UMyClass_Transient_Test* newTestObject=LoadObject<UMyClass_Transient_Test>(loadedPackage, TEXT("testObject"),*assetPath);

	//TArray<uint8> testArray;
	//USerializationLibrary::SaveObjectToMemory(testObject, testArray);
	//UMyClass_Transient_Test* newTestObject= USerializationLibrary::LoadObjectFromMemory<UMyClass_Transient_Test>(testArray);


	FString outStr;
	//GetHiddenFunctions(0,UMyClass_HideFunctions::StaticClass(),false,outStr);

	//FString str= UInsiderSubsystem::PrintObject(UMyClass_Default::StaticClass(),EInsiderPrintFlags::All);
	//FString str = UInsiderSubsystem::PrintObject(UMyClass_NoUCLASS::StaticClass(), EInsiderPrintFlags::All);
	FString str;
	//str+= UInsiderSubsystem::PrintObject(UMyComponent_ClassGroup::StaticClass(), EInsiderPrintFlags::All);
	//str += UInsiderSubsystem::PrintObject(UMyClass_Deprecated_Test::StaticClass(), EInsiderPrintFlags::All);

	//str += UInsiderSubsystem::PrintObject(UMyClass_BlueprintType_Child::StaticClass(), EInsiderPrintFlags::All);

	//str += UInsiderSubsystem::PrintObject(UMyClass_NotBlueprintType::StaticClass(), EInsiderPrintFlags::All);
	//str += UInsiderSubsystem::PrintObject(UMyClass_NotBlueprintType_To_BlueprintType::StaticClass(), EInsiderPrintFlags::All);
	//str += UInsiderSubsystem::PrintObject(UMyClass_BlueprintType_To_NotBlueprintType::StaticClass(), EInsiderPrintFlags::All);




	//INSIDER_REMOVE_CLASS_FLAGS(UMyClass_NoUCLASS,CLASS_Abstract);

	//FString str= UInsiderSubsystem::PrintDerivedClasses(USubsystem::StaticClass());

	//auto* obj= NewObject< UMyClass_NoUCLASS>();
	//FString str0 = UInsiderSubsystem::PrintObject(obj);

	//FString str= UInsiderSubsystem::PrintObject(UMyClass_Default::StaticClass());
	////FString str2 = UInsiderSubsystem::PrintObject(UMyClass_NotBlueprintType::StaticClass());

	//UPackage* pack1= LoadPackage(nullptr,TEXT("/Game/BP_MyActor"),LOAD_None);
	//UPackage* pack2 = LoadPackage(nullptr, TEXT("/Game/DA_MyReferenceTest"), LOAD_None);
	//UPackage* pack3 = LoadPackage(nullptr, TEXT("/Game/DT_MyTable"), LOAD_None);


	//FString str1= UInsiderSubsystem::PrintObject(pack1,EInsiderPrintFlags::PackageDefault);
	//FString str2 = UInsiderSubsystem::PrintObject(pack2, EInsiderPrintFlags::PackageDefault);
	//FString str3 = UInsiderSubsystem::PrintObject(pack3, EInsiderPrintFlags::PackageDefault);


	//UE_LOG(LogInsider, Display,TEXT("%s\n"), *str1);
	//UE_LOG(LogInsider, Display, TEXT("%s\n"), *str2);
	//UE_LOG(LogInsider, Display, TEXT("%s\n"), *str3);




	

}

void FInsiderModule::ShutdownModule()
{
}


IMPLEMENT_MODULE(FInsiderModule, Insider)
