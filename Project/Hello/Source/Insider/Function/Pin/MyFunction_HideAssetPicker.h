// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyFunction_HideAssetPicker.generated.h"

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyFunction_HideAssetPicker :public UBlueprintFunctionLibrary
{
public:
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	static void MyFunc_NoHideAssetPicker(UObject* ObjectClass) {}

	UFUNCTION(BlueprintCallable, meta = (HideAssetPicker = "ObjectClass"))
	static void MyFunc_HideAssetPicker(UObject* ObjectClass) {}
};


