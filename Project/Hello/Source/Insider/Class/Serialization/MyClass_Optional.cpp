#include "MyClass_Optional.h"
#include "Utility/InsiderSubsystem.h"
#include "UObject/SavePackage.h"

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


void UMyClass_Optional_Test::RunTest()
{
	//CreatePackageAndSave();
	LoadPackageAndTest();
}
