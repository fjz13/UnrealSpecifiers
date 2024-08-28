// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyStruct_DisableSplitPin.generated.h"

//(BlueprintType = true, DisableSplitPin = , ModuleRelativePath = Struct/MyStruct_DisableSplitPin.h)
USTRUCT(BlueprintType, meta = (DisableSplitPin))
struct INSIDER_API FMyStruct_DisableSplitPin
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MyFloat=0.f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString MyString;
};


USTRUCT(BlueprintType)
struct INSIDER_API FMyStruct_WithSplitPin
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MyFloat=0.f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString MyString;
};