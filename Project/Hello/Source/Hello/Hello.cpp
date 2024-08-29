// Fill out your copyright notice in the Description page of Project Settings.

#include "Hello.h"
#include "Modules/ModuleManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Misc/Paths.h"
//#include "Struct/MyStruct_NoExport.h"
//#include "Class/MyClass_CustomConstructor.h"
//#include "Class/MyClass_Within.h"
//#include "Class/MyClass_ModuleAPI.h"
//#include "Class/MyClass_CollapseCategories.h"
#include "Interfaces/IPluginManager.h"
#include "Struct/MyStruct_ModuleAPI.h"
#include "Struct/MyStruct_NoExport.h"
#include "Struct/MyStruct_Atomic.h"


#include "Utility/SerializationLibrary.h"
#include "Utility/InsiderSubsystem.h"
#include "HelloLog.h"

#include "Templates/IsEnumClass.h"
#include "Enum/MyEnum.h"


void FHelloModule::StartupModule()
{

	//auto ss1 = FMyStruct_NoExport::StaticStruct();

	//TArray<uint8> testMemory;
	//FMyStruct_Atomic ttt;
	//USerializationLibrary::SaveStructToMemory(ttt,testMemory,EInsiderSerializationFlags::CheckDefaults);


	FMyStruct_NoAtomic NoAtomicStruct;
	NoAtomicStruct.Item.A = 3;

	FMyStruct_Atomic AtomicStruct;
	AtomicStruct.Item.A = 3;


	//TArray<uint8> MemoryOriginal;
	//USerializationLibrary::SaveStructToMemory(testStruct,MemoryOriginal,EInsiderSerializationFlags::CheckDefaults);	//9 bytes

	//FString str1= USerializationLibrary::ToString(testStruct);
	TArray<uint8> NoAtomicMemoryChanged;
	USerializationLibrary::SaveStructToMemory(NoAtomicStruct, NoAtomicMemoryChanged, EInsiderSerializationFlags::CheckDefaults);

	TArray<uint8> AtomicMemoryChanged;
	USerializationLibrary::SaveStructToMemory(AtomicStruct, AtomicMemoryChanged, EInsiderSerializationFlags::CheckDefaults);
	//FString str2= USerializationLibrary::ToString(testStruct);



	return;
	/*int actorSize=sizeof(AActor);
	int componentSize = sizeof(USceneComponent);


	auto& myType= typeid(AActor);
	FString str= UInsiderSubsystem::PrintObject(AActor::StaticClass(),EInsiderPrintFlags::Properties| EInsiderPrintFlags::WithSuper);
	FString str2 = UInsiderSubsystem::PrintObject(USceneComponent::StaticClass(), EInsiderPrintFlags::Properties | EInsiderPrintFlags::WithSuper);*/

	//TArray<int32> items = { 1,2,3 };

	//TSet<FVector> items;

	//for (TObjectIterator<UStruct> StructIt; StructIt; ++StructIt)
	//{
	//	UStruct* ss=*StructIt;
	//	//if (ss->GetPropertiesSize()!=ss->GetStructureSize())
	//	{
	//		UE_LOG(LogHello,Warning,TEXT("%s %d-%d=%d"),*ss->GetName(),ss->GetPropertiesSize(),ss->GetMinAlignment(),ss->GetStructureSize());
	//	}
	//	
	//}
	//TMap<int32,FVector> items;


	//FVector myVector1(5.f, 6.f, 7.f);
	//FVector myVector2(15.f, 16.f, 17.f);
	//FVector myVector3(25.f, 26.f, 27.f);

	//items.Add(10,myVector1);
	//items.Add(9,myVector2);
	//items.Add(8,myVector3);

	//FString str= USerializationLibrary::ToString(123);
	//FString str1 = USerializationLibrary::ToString(items);
	//FString str = USerializationLibrary::ToString(items);

	//FString str = TEXT("((X = 5.000000, Y = 6.000000, Z = 7.000000), (X = 15.000000, Y = 16.000000, Z = 17.000000), (X = 25.000000, Y = 26.000000, Z = 27.000000))");
	//items.Reset();
	//FString parseResult= USerializationLibrary::TryParse(str1, items);
	/*FString CPPName= typeid(FVector).raw_name();

	UScriptStruct* ss1=LoadObject<UScriptStruct>(nullptr, TEXT("Vector"));
	UPackage* corePackge= LoadPackage(nullptr,TEXT("/Script/CoreUObject"), LOAD_None);
	UScriptStruct* ss = Cast<UScriptStruct>(StaticFindObjectFast(UScriptStruct::StaticClass(), nullptr, TEXT("Vector"),true,true));
	FString fullName= ss->GetFullName();*/

	//FString path= FPaths::Combine(FPaths::ProjectPluginsDir(),TEXT("MyPlugin/MyPlugin.uplugin"));
	//IPluginManager::Get().AddToPluginsList(path);
	//IPluginManager::Get().MountExplicitlyLoadedPlugin(TEXT("MyPlugin"));

	//UObject* bpAsset = LoadObject<UObject>(NULL, TEXT("/Game/BP_MyGameInstanceSubsystem.BP_MyGameInstanceSubsystem"));
	//UObject* bpAsset = LoadObject<UObject>(NULL, TEXT("/Game/BP_MyGameInstanceSubsystem"));



	//auto* mod = FModuleManager::Get().LoadModule(TEXT("MyPlugin"));
	//auto* mod2 = FModuleManager::Get().LoadModule(TEXT("Insider"));


	//UScriptStruct* ss = FMyStruct_NoExport::StaticStruct();
	//UScriptStruct* ss2 = StaticStruct<FMyStruct_NoExport>();

	/*UClass* cc= StaticClass<UMyClass_DontCollapseCategories>();
	cc->ClassFlags &= ~CLASS_CollapseCategories;
	{
		auto* outer = NewObject<UMyClass_ModuleAPI>();
		auto* a = NewObject<UMyClass_Within>(outer);
		a->MyFunc();
		a->MyProperty++;
	}*/

	//Insider::PrintAllObjects();
	//Insider::PrintAllObjects();
	//Insider::PrintAllObjects2();
	//Insider::PrintAllObjects3();

	/*UPackage* pack= GetTransientPackage();
	UClass* uclass= UPackage::StaticClass();
	UMyClass* my = NewObject<UMyClass>();
	UClass* myClass=UMyClass::StaticClass();


	UEnum* enmClass = FindObject<UEnum>(ANY_PACKAGE,TEXT("MyEnum"));
	TMap<FName, int32> newItems;
	for (int i=0;i<100;++i)
	{
		newItems.Add(FName(*FString::Printf(TEXT("MyTest%d"), i)), i);
	}*/

	//UReflectionLibrary::AddEnumItem(enmClass, "MyDynamic", 123);
	//UReflectionLibrary::AddEnumItems(enmClass, newItems);

	//Insider::PrintObject(myClass);

	//TArray<UFunction*> funcs;
	//funcs.Add(myClass->FindFunctionByName("Func"));
	//funcs.Add(myClass->FindFunctionByName("ImplementableFunc"));
	//funcs.Add(myClass->FindFunctionByName("NativeFunc"));
	//funcs.Sort();


	/*UMyClass* my = NewObject<UMyClass>();
	UClass* myClass = my->GetClass();

	int32 myAlign=alignof(UMyClass);
	int32 size0 = sizeof(UObject);
	int32 size1 = sizeof(UMyClass);
	int32 size2 = myClass->GetPropertiesSize();
	int32 size3 = myClass->GetStructureSize();*/


	//Insider::PrintObject(my);


	/*UClass* objClass= UObject::StaticClass();
	UClass* theClass= UClass::StaticClass();
	UClass* packageClass = UPackage::StaticClass();


	UMyObject* myObject = NewObject<UMyObject>();
	UClass* myClass = myObject->GetClass();*/


	//UMyObjectWithSubobject* myObjectWithSubobject = NewObject<UMyObjectWithSubobject>();
	//AMyActor* myClassObject = NewObject<AMyActor>();
	//UMyClass* myClassObject = NewObject<UMyClass>();

	//AMyActor* copyObj=DuplicateObject(myClassObject,nullptr);

	/*FString path = TEXT("/Game/MyDataAssetRes.MyDataAssetRes");
	UMyDataAsset* my = ConstructorHelpersInternal::FindOrLoadObject<UMyDataAsset>(path);
	LOG_INSIDER("%f", my->Score);

	my->Score = 555;
	UPackage* pack=Cast<UPackage>(my->GetOutermost());

	FString fileName= pack->FileName.ToString();
	fileName=FPaths::ConvertRelativePathToFull(fileName);
	pack->Save(pack, nullptr, RF_Standalone, *fileName);*/

	//UMyDataAsset::CreateNewAsset("MyTest",true);



}

void FHelloModule::ShutdownModule()
{
}



IMPLEMENT_PRIMARY_GAME_MODULE(FHelloModule, Hello, "Hello");


