// Fill out your copyright notice in the Description page of Project Settings.

#include "InsiderEditor.h"
#include "Modules/ModuleManager.h"
#include "Customization/MyCommonObjectCustomization.h"
#include "Customization/MyCommonStructCustomization.h"
#include "Customization/MyAnimNode_MyCustomizePropertyCustomization.h"


#include "Common/CommonTypes.h"

void FInsiderEditorModule::StartupModule()
{
	//MyCustomAssetTypeActions = MakeShared<FMyCustomAssetTypeActions>();
	//FAssetToolsModule::GetModule().Get().RegisterAssetTypeActions(MyCustomAssetTypeActions.ToSharedRef());

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	//PropertyModule.RegisterCustomPropertyTypeLayout(TEXT("MyCommonObject"), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FMyCommonObjectCustomization::MakeInstance));
	//PropertyModule.RegisterCustomPropertyTypeLayout(TEXT("MyCommonStruct"), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FMyCommonStructCustomization::MakeInstance));


	//PropertyModule.RegisterCustomClassLayout(TEXT("AnimGraphNode_MyCustomizeProperty"), FOnGetDetailCustomizationInstance::CreateStatic(&FMyAnimNode_MyCustomizePropertyCustomization::MakeInstance));



	PropertyModule.NotifyCustomizationModuleChanged();
}

void FInsiderEditorModule::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
		//PropertyModule.UnregisterCustomPropertyTypeLayout(TEXT("MyCommonObject"));
		PropertyModule.UnregisterCustomPropertyTypeLayout(TEXT("MyCommonStruct"));


		PropertyModule.NotifyCustomizationModuleChanged();
	}

	//if (!FModuleManager::Get().IsModuleLoaded("AssetTools")) return;
	//FAssetToolsModule::GetModule().Get().UnregisterAssetTypeActions(MyCustomAssetTypeActions.ToSharedRef());

}


IMPLEMENT_MODULE(FInsiderEditorModule, Insider)

