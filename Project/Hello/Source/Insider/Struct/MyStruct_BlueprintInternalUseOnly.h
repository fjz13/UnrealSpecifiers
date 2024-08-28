// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyStruct_BlueprintInternalUseOnly.generated.h"

//(BlueprintInternalUseOnly = true, BlueprintType = true, ModuleRelativePath = Struct/MyStruct_BlueprintInternalUseOnly.h)
USTRUCT(BlueprintInternalUseOnly)
struct INSIDER_API FMyStruct_BlueprintInternalUseOnly
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float Score=0.f;
};

USTRUCT()
struct INSIDER_API FMyStruct_NoBlueprintInternalUseOnly
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float Score=0.f;
};


UCLASS(Blueprintable,BlueprintType)
class INSIDER_API UMyClass_BlueprintInternalUseOnlyTest :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FMyStruct_BlueprintInternalUseOnly MyInternalStruct;

	/*UPROPERTY(BlueprintReadWrite,EditAnywhere)	//no supported by BP
	FMyStruct_NoBlueprintInternalUseOnly MyStruct;*/
};

