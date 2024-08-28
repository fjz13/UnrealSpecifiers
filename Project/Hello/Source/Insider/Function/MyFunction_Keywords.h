// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyFunction_Keywords.generated.h"

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyFunction_Keywords :public UBlueprintFunctionLibrary
{
public:
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable,meta=(Keywords="This is a SuperFunc,OtherFunc"))
	static void MyFunc_HasKeyworlds();

	UFUNCTION(BlueprintCallable)
	static void MyFunc_NoKeyworlds();
};


