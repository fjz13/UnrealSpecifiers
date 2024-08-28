// Fill out your copyright notice in the Description page of Project Settings.

#include "MyFunction_Advanced.h"
#include "PackageHelperFunctions.h"

bool UMyFunction_Advanced::AddPropertyFlags(FString functionPath, FString propertyName, EPropertyFlags flags)
{
	if (UFunction* func = LoadObject<UFunction>(nullptr, *functionPath))
	{
		if (FProperty* prop = func->FindPropertyByName(*propertyName))
		{
			prop->SetPropertyFlags(flags);

			UPackage* package= func->GetOutermost();
			SavePackageHelper(package,package->GetPathName());
			return true;
		}

	}
	return false;
}

void UMyFunction_Advanced::RunTest()
{
	UMyFunction_Advanced::AddPropertyFlags(TEXT("/Game/Function/BP_AddMeta_Test.SKEL_BP_AddMeta_Test_C:MyFunc"),TEXT("Forth"),CPF_AdvancedDisplay);
}
