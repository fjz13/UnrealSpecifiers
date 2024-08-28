// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyFunction_DefaultValue.generated.h"

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyFunction_DefaultValue :public UBlueprintFunctionLibrary
{
public:
	GENERATED_BODY()
public:
	// (ModuleRelativePath = Function/MyFunction_DefaultValue.h, MyValue = 456)
	UFUNCTION(BlueprintCallable,meta=(MyValue=456))
	static void MyFunc_HasDefaultValue(int32 MyValue);
};


