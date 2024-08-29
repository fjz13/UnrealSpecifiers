// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyStruct_BlueprintType.generated.h"

//(BlueprintType = true, ModuleRelativePath = Struct/MyStruct_BlueprintType.h)
USTRUCT(BlueprintType)
struct INSIDER_API FMyStruct_BlueprintType
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float Score=0.f;
};

//(ModuleRelativePath = Struct/MyStruct_BlueprintType.h)
USTRUCT()
struct INSIDER_API FMyStruct_NoBlueprintType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float Score=0.f;
};
