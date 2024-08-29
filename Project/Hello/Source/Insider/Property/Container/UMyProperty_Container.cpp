// Fill out your copyright notice in the Description page of Project Settings.

#include "UMyProperty_Container.h"

void UMyProperty_Container::ClearInnerObject()
{
	MyIntArray.Empty();
	MyIntArray_NoElementDuplicate.Empty();

	MyStructArray.Empty();
	MyStructArray_NoElementDuplicate.Empty();
	MyObjectArray.Empty();
	MyObjectArray_NoElementDuplicate.Empty();

	//////////////////////////////////////////////////////////////////////////
	MyIntArray_NoEditFixedOrder.Empty();
	MyIntArray_EditFixedOrder.Empty();
	MyIntSet_NoEditFixedOrder.Empty();
	MyIntSet_EditFixedOrder.Empty();
	MyIntMap_NoEditFixedOrder.Empty();
	MyIntMap_EditFixedOrder.Empty();

	MyStructArray_NoTitleProperty.Empty();
	MyStructArray_NoTitleProperty.Empty();

	MyIntMap_NoReadOnlyKeys.Empty();
	MyIntMap_ReadOnlyKeys.Empty();

	Modify();

	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyEditorModule.NotifyCustomizationModuleChanged();
}

void UMyProperty_Container::InitInnerObject()
{
	for (int i = 0; i < 3; ++i)
	{
		MyIntArray.Emplace(i);
		MyIntArray_NoElementDuplicate.Emplace(i);

		MyObjectArray.Emplace_GetRef() = NewObject<UMyCommonObject>(this);
		MyObjectArray_NoElementDuplicate.Emplace_GetRef() = NewObject<UMyCommonObject>(this);


		MyStructArray.Emplace(FMyCommonStruct(i));
		MyStructArray_NoElementDuplicate.Emplace(FMyCommonStruct(i));

		//////////////////////////////////////////////////////////////////////////
		MyIntArray_NoEditFixedOrder.Emplace(i);
		MyIntArray_EditFixedOrder.Emplace(i);

		MyIntSet_NoEditFixedOrder.Emplace(i);
		MyIntSet_EditFixedOrder.Emplace(i);
		MyIntMap_NoEditFixedOrder.Emplace(i, TEXT("Hello"));
		MyIntMap_EditFixedOrder.Emplace(i, TEXT("Hello"));

		MyStructArray_NoTitleProperty.Emplace(FMyArrayTitleStruct(i));
		MyStructArray_HasTitleProperty.Emplace(FMyArrayTitleStruct(i));


		MyIntMap_NoReadOnlyKeys.Emplace(i, TEXT("Hello"));
		MyIntMap_ReadOnlyKeys.Emplace(i, TEXT("Hello"));
	}



	Modify();

	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyEditorModule.NotifyCustomizationModuleChanged();
}