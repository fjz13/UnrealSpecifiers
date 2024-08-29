// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject\ObjectMacros.h"
#include "MyFunction_Advanced.generated.h"

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyFunction_Advanced :public UBlueprintFunctionLibrary
{
public:
	GENERATED_BODY()
public:
	static bool AddPropertyFlags(FString functionPath,FString propertyName,EPropertyFlags flags);

	UFUNCTION(CallInEditor)
	static void RunTest();
};
