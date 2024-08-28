// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyTokenStreamStructObject.generated.h"

class UMyTokenStreamClass2;

USTRUCT(Blueprintable, Blueprintable)
struct LEARN_API FMyTokenStreamStructObject
{
	GENERATED_BODY()
public:
	FMyTokenStreamStructObject();

public:
	UPROPERTY(BlueprintReadWrite)
		UMyTokenStreamClass2* InnerObject;
};
