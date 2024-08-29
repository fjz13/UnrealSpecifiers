// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyFunction_Unsafe.generated.h"


UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyFunction_Unsafe :public UBlueprintFunctionLibrary
{
public:
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	static void MySafeFunction();
	UFUNCTION(BlueprintCallable, meta=(UnsafeDuringActorConstruction = "true"))
	static void MyUnsafeFunction();
};


