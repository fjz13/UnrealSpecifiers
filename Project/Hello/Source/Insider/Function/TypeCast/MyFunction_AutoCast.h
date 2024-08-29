// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyFunction_AutoCast.generated.h"


USTRUCT(BlueprintType)
struct FAutoCastFrom
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 X = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Y = 0;
};


USTRUCT(BlueprintType)
struct FAutoCastTo
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Sum = 0;
};

USTRUCT(BlueprintType)
struct FNoAutoCastTo
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Sum = 0;
};


UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyFunction_AutoCast :public UBlueprintFunctionLibrary
{
public:
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, meta = (BlueprintAutocast))
	static FAutoCastTo Conv_MyTestAutoCast(const FAutoCastFrom& InValue);
};


