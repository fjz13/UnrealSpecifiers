// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProperty_Inner.h"

void UMyProperty_Inner::ClearInnerObject()
{
	InnerObject = nullptr;
	InnerObject_ShowInnerProperties = nullptr;
	InnerObject_EditInline = nullptr;
	InnerObject_Instanced = nullptr;

	InnerObject_EditInlineNewClass = nullptr;
	InnerObject_EditInlineNewClass_EditInline = nullptr;
	InnerObject_EditInlineNewClass_Instanced = nullptr;

	Modify();

	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyEditorModule.NotifyCustomizationModuleChanged();
}

void UMyProperty_Inner::InitInnerObject()
{
	InnerObject = NewObject<UMyProperty_InnerSub>(this);
	InnerObject_ShowInnerProperties = NewObject<UMyProperty_InnerSub>(this);
	InnerObject_EditInline = NewObject<UMyProperty_InnerSub>(this);
	InnerObject_Instanced = NewObject<UMyProperty_InnerSub>(this);



	InnerObject_EditInlineNewClass = NewObject<UMyProperty_InnerSub_EditInlineNew>(this);
	InnerObject_EditInlineNewClass_EditInline = NewObject<UMyProperty_InnerSub_EditInlineNew>(this);
	//InnerObject_EditInlineNewClass_Instanced = NewObject<UMyProperty_InnerSub_EditInlineNew>(this);


	Modify();

	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyEditorModule.NotifyCustomizationModuleChanged();
}

void UMyProperty_Inner::RemoveActorMeta()
{
	FProperty* prop = UChildActorComponent::StaticClass()->FindPropertyByName(TEXT("ChildActorTemplate"));
	prop->RemoveMetaData(TEXT("ShowInnerProperties"));
}

void UMyProperty_Inner::AddActorMeta()
{
	FProperty* prop = UChildActorComponent::StaticClass()->FindPropertyByName(TEXT("ChildActorTemplate"));
	prop->SetMetaData(TEXT("ShowInnerProperties"), TEXT(""));
}
