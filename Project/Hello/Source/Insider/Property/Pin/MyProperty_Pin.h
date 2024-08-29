// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MyProperty_Pin.generated.h"

USTRUCT(BlueprintType)
struct FMyPinHiddenTestStruct
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category=PinHiddenByDefaultTest)
	int32 MyInt_NotHidden = 123;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category=PinHiddenByDefaultTest, meta = (PinHiddenByDefault))
	int32 MyInt_PinHiddenByDefault = 123;
};

UCLASS(BlueprintType)
class INSIDER_API UMyProperty_Pin :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category=PinHiddenByDefaultTest)
	FMyPinHiddenTestStruct MyPinTestStruct;

	UFUNCTION(BlueprintCallable)
	static FMyPinHiddenTestStruct MyHiddenPinTestFunc(FMyPinHiddenTestStruct Input);
};


