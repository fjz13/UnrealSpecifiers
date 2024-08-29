// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyStruct_ModuleAPI.generated.h"


USTRUCT(BlueprintType)
struct INSIDER_API FMyStruct_ModuleAPI
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float Score=0.f;

};
