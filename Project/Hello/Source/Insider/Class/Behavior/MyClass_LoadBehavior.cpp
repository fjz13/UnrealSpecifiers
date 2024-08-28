// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "MyClass_LoadBehavior.h"


void OnMyHandleReadCallback(const TArrayView<const UObject* const>& Objects)
{
	for (const UObject* const obj : Objects)
	{
		if (obj==nullptr)
		{
			continue;
		}
		if (!obj->IsTemplate()&&(obj->IsA<UMyDataAsset_Eager>() || obj->IsA<UMyDataAsset_LazyOnDemand>()))
		{
			FString objectName = obj->GetName();
			objectName+="\n";
		}
	}
}

void OnMyObjectHandleReferenceLoadedCallback(const FObjectRef& SourceRef, UPackage* ObjectPackage, UObject* Object)
{
	if (SourceRef.ClassName == TEXT("MyDataAsset_Eager") || SourceRef.ClassName == TEXT("MyDataAsset_LazyOnDemand"))
	{
		FString objectName = Object->GetName();
	}
}

void OnMyObjectHandleReferenceResolvedCallback(const FObjectRef& SourceRef, UPackage* ObjectPackage, UObject* Object)
{
	if (SourceRef.ClassName == TEXT("MyDataAsset_Eager") || SourceRef.ClassName == TEXT("MyDataAsset_LazyOnDemand"))
	{
		FString objectName = Object->GetName();
	}
}


void UMyClass_LoadBehaviorTest::RegisterObjectHandleCallback()
{
	UE::CoreUObject::AddObjectHandleReferenceLoadedCallback(OnMyObjectHandleReferenceLoadedCallback);
	UE::CoreUObject::AddObjectHandleReferenceResolvedCallback(OnMyObjectHandleReferenceResolvedCallback);
	UE::CoreUObject::AddObjectHandleReadCallback(OnMyHandleReadCallback);
}

void UMyClass_LoadBehaviorTest::LoadBehaviorTest()
{
	UPackage* pk = LoadPackage(nullptr, TEXT("/Game/Class/Behavior/LoadBehavior/DA_LoadBehaviorTest"), 0);
	UMyClass_LoadBehaviorTest* obj = LoadObject<UMyClass_LoadBehaviorTest>(pk, TEXT("DA_LoadBehaviorTest"));
}
