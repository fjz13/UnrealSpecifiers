#include "MyClass_Transient.h"
#include "Utility/InsiderSubsystem.h"
#include "UObject/SavePackage.h"

void UMyClass_Transient_Test::CreatePackageAndSave()
{
	FString packageName = TEXT("/Game/MyTestPackage");
	FString assetPath = FPackageName::LongPackageNameToFilename(packageName, FPackageName::GetAssetPackageExtension());

	IFileManager::Get().Delete(*assetPath, false, true);


	UPackage* package = CreatePackage(*packageName);
	FSavePackageArgs saveArgs{};
	//saveArgs.TopLevelFlags = EObjectFlags::RF_Public | EObjectFlags::RF_Standalone;
	saveArgs.Error = GError;
	//saveArgs.SaveFlags=SAVE_NoError;

	UMyClass_Transient_Test* testObject = NewObject<UMyClass_Transient_Test>(package, TEXT("testObject"));	//ObjectFlags:	RF_NoFlags
	testObject->MyTransientObject = NewObject<UMyClass_Transient>(testObject, TEXT("MyTransientObject"));	//ObjectFlags:	RF_Transient 
	testObject->MyNonTransientObject = NewObject<UMyClass_NonTransient>(testObject, TEXT("MyNonTransientObject"));	//ObjectFlags:	RF_NoFlags

	testObject->MyTransientObject->MyProperty = 456;
	testObject->MyNonTransientObject->MyProperty = 456;
	testObject->MyInt_Normal = 456;
	testObject->MyInt_Transient = 456;



	FString str = UInsiderSubsystem::Get().PrintObject(package, EInsiderPrintFlags::All);
	FString str2 = UInsiderSubsystem::Get().PrintObject(testObject, EInsiderPrintFlags::All);
	FString str3 = UInsiderSubsystem::Get().PrintObject(UMyClass_Transient::StaticClass(), EInsiderPrintFlags::All);
	FString str4 = UInsiderSubsystem::Get().PrintObject(UMyClass_NonTransient::StaticClass(), EInsiderPrintFlags::All);

	bool result = UPackage::SavePackage(package, testObject, *assetPath, saveArgs);


}

void UMyClass_Transient_Test::LoadPackageAndTest()
{
	FString packageName = TEXT("/Game/MyTestPackage");
	FString assetPath = FPackageName::LongPackageNameToFilename(packageName, FPackageName::GetAssetPackageExtension());

	UPackage* package = LoadPackage(nullptr, *assetPath, LOAD_None);
	package->FullyLoad();


	UMyClass_Transient_Test* newTestObject = LoadObject<UMyClass_Transient_Test>(package, TEXT("testObject"), *assetPath);
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

void UMyClass_Transient_Test::RunTest()
{
	CreatePackageAndSave();
	//LoadPackageAndTest();
}
