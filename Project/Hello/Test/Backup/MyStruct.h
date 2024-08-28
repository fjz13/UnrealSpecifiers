// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyEnum.h"
#include "MyStruct.generated.h"

UENUM(Blueprintable)
enum OhterEnum
{
	Ohter_First,
	Ohter_Second
};

USTRUCT(BlueprintType)
struct HELLO_API FMyStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	float Score;

	UPROPERTY(BlueprintReadWrite)
		uint8 bool1:1;

	UPROPERTY(BlueprintReadWrite)
		bool realbool;

	
};

//
//USTRUCT(BlueprintType)
//struct HELLO_API FMyDerivedStruct :public FMyStruct
//{
//	GENERATED_BODY()
//};
//
