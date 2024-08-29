// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProperty_MaxPropertyDepth.generated.h"


USTRUCT(BlueprintType)
struct INSIDER_API FMyStructDepth1
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MyInt1 = 123;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString MyString1;
};


USTRUCT(BlueprintType)
struct INSIDER_API FMyStructDepth2
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FMyStructDepth1 MyStruct1;
};

USTRUCT(BlueprintType)
struct INSIDER_API FMyStructDepth3
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FMyStructDepth2 MyStruct2;
};


USTRUCT(BlueprintType)
struct INSIDER_API FMyStructDepth4
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FMyStructDepth3 MyStruct3;
};



UCLASS(BlueprintType)
class INSIDER_API UMyProperty_MaxPropertyDepth :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FMyStructDepth4 MyStruct;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta=(MaxPropertyDepth=2))
	FMyStructDepth4 MyStruct_Depth;
};

