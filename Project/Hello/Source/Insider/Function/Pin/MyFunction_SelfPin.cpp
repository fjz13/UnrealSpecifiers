// Fill out your copyright notice in the Description page of Project Settings.

#include "MyFunction_SelfPin.h"

FString UMyFunctionLibrary_SelfPinTest::PrintProperty_HasDefaultToSelf(UObject* myOwner, FName propertyName)
{
	FString result;
	if (myOwner == nullptr)
	{
		result = TEXT("None");
		return result;
	}
	UClass* classObj = myOwner->GetClass();
	FProperty* prop = classObj->FindPropertyByName(propertyName);
	if (prop)
	{
		prop->ExportTextItem_Direct(result, prop->ContainerPtrToValuePtr<const void*>(myOwner), nullptr, myOwner, PPF_None);
	}
	else
	{
		result = TEXT("None");
	}
	return result;
}

FString UMyFunctionLibrary_SelfPinTest::PrintProperty_Default(UObject* myOwner, FName propertyName)
{
	return PrintProperty_HasDefaultToSelf(myOwner,propertyName);
}

FString UMyFunctionLibrary_SelfPinTest::PrintProperty_HasDefaultToSelf_ButHide(UObject* myOwner, FName propertyName)
{
	return PrintProperty_HasDefaultToSelf(myOwner,propertyName);
}

FString UMyFunctionLibrary_SelfPinTest::PrintProperty_HasDefaultToSelf_AndHideSelf(UObject* myOwner, FName propertyName)
{
	return PrintProperty_HasDefaultToSelf(myOwner,propertyName);
}

FString UMyFunctionLibrary_SelfPinTest::PrintProperty_HasDefaultToSelf_ButInternal(UObject* myOwner, FName propertyName)
{
	return PrintProperty_HasDefaultToSelf(myOwner,propertyName);
}
