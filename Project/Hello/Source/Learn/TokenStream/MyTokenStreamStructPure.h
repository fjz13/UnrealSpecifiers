// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyTokenStreamStructPure.generated.h"

USTRUCT(Blueprintable, Blueprintable)
struct LEARN_API FMyTokenStreamStructPure
{
	GENERATED_BODY()
public:
	FMyTokenStreamStructPure();

public:
	UPROPERTY(BlueprintReadWrite)
		float Score;
};
