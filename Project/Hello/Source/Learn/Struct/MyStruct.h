// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyStruct.generated.h"

USTRUCT()
struct LEARN_API FMyStruct
{
	GENERATED_BODY()

	/*
	Error: Cannot expose property to blueprints in a struct that is not a BlueprintType. MyStruct.ReadWriteValue
	*/
	/*UPROPERTY(BlueprintReadWrite)
	float ReadWriteValue;*/

	/*
	Error: Cannot expose property to blueprints in a struct that is not a BlueprintType. MyStruct.ReadOnlyValue
	*/
	//UPROPERTY(BlueprintReadOnly)
	//float ReadOnlyValue;
};
