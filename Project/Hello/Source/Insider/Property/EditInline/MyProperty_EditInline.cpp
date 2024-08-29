// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProperty_EditInline.h"
#include "Utility/InsiderSubsystem.h"


void UMyProperty_EditInline::ClearInnerObject()
{
	MyObject = nullptr;
	MyObject_EditInline = nullptr;
	MyObject_NoEditInline = nullptr;

	MyObjectArray.Empty();
	MyObjectArray_EditInline.Empty();
	MyObjectArray_NoEditInline.Empty();

	MyStructMap.Empty();
	MyStructMap_ForceInlineRow.Empty();
	MyStructMap2.Empty();
	MyStructMap_ForceInlineRow2.Empty();

	MyStructArray.Empty();
	MyStructArray_ForceInlineRow.Empty();

	

	Modify();

	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyEditorModule.NotifyCustomizationModuleChanged();
}

void UMyProperty_EditInline::InitInnerObject()
{
	MyObject = NewObject<UMyProperty_EditInline_Sub>(this);
	MyObject_EditInline = NewObject<UMyProperty_EditInline_Sub>(this);
	MyObject_NoEditInline = NewObject<UMyProperty_EditInline_Sub>(this);

	for (int i = 0; i < 3; ++i)
	{
		MyObjectArray.Emplace_GetRef() = NewObject<UMyProperty_EditInline_Sub>(this);
		MyObjectArray_EditInline.Emplace_GetRef() = NewObject<UMyProperty_EditInline_Sub>(this);
		MyObjectArray_NoEditInline.Emplace_GetRef() = NewObject<UMyProperty_EditInline_Sub>(this);


		MyStructMap.Emplace(FMyCommonStruct(i), i);
		MyStructMap_ForceInlineRow.Emplace(FMyCommonStruct(i), i);

		MyStructMap2.Emplace(i,FMyCommonStruct(i));
		MyStructMap_ForceInlineRow2.Emplace(i,FMyCommonStruct(i));

		MyStructArray.Emplace(FMyCommonStruct(i));
		MyStructArray_ForceInlineRow.Emplace(FMyCommonStruct(i));

	}



	Modify();

	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyEditorModule.NotifyCustomizationModuleChanged();
}

void UMyProperty_EditInline::AddMeta()
{

	//UInsiderSubsystem::SetPropertyMetaData(TEXT("RuntimePartitionDesc"), TEXT("HLODSetups"), TEXT("ForceInlineRow"));
	//	UObject* obj = UInsiderSubsystem::FindObjectWithNameSmart(TEXT("MovieSceneBindingPropertyInfo"));
	//	UScriptStruct* ss = Cast<UScriptStruct>(obj);
	//	if (ss==nullptr)
	//	{
	//		return;
	//	}
	//
	//	FProperty* prop = ss->FindPropertyByName(TEXT("CustomBinding"));
	//	prop->SetMetaData(TEXT("AllowEditInlineCustomization"), TEXT(""));

}

void UMyProperty_EditInline::RemoveMeta()
{
	//	UObject* obj = UInsiderSubsystem::FindObjectWithNameSmart(TEXT("MovieSceneBindingPropertyInfo"));
	//	UScriptStruct* ss = Cast<UScriptStruct>(obj);
	//	if (ss==nullptr)
	//	{
	//		return;
	//	}
	//
	//	FProperty* prop = ss->FindPropertyByName(TEXT("CustomBinding"));
	//	prop->RemoveMetaData(TEXT("AllowEditInlineCustomization"));

	//UInsiderSubsystem::RemovePropertyMetaData(TEXT("RuntimePartitionDesc"), TEXT("HLODSetups"), TEXT("ForceInlineRow"));

}

