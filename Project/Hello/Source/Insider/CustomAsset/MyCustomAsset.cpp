// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCustomAsset.h"

void UMyCustomAsset::ClearInnerObject()
{
	MyCommonObject = nullptr;
	MyCommonObject_Customization = nullptr;

	Modify();

	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyEditorModule.NotifyCustomizationModuleChanged();
}

void UMyCustomAsset::InitInnerObject()
{
	MyCommonObject = NewObject<UMyCommonObject>(this);
	MyCommonObject_Customization = NewObject<UMyCommonObject>(this);

	Modify();

	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyEditorModule.NotifyCustomizationModuleChanged();
}
