// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyFunction_Template.generated.h"

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyFunction_Template :public UBlueprintFunctionLibrary
{
public:
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	static void MyFunc_Template(){}

	UFUNCTION(BlueprintCallable)
	const FString& MyFunc(){return Str;}

	FString Str;
};


