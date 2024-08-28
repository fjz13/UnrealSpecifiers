// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyFunction_Misc.generated.h"

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyFunction_Misc :public UBlueprintFunctionLibrary
{
public:
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, meta = (DevelopmentOnly))
	static void MyFunc_DevelopmentOnly() {}

	UFUNCTION(BlueprintCallable, meta = ())
	static void MyFunc_NotDevelopmentOnly() {}
};
