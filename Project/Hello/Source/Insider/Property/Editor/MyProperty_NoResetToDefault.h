// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProperty_NoResetToDefault.generated.h"

UCLASS(BlueprintType)
class INSIDER_API UMyProperty_NoResetToDefault :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category=ResetToDefaultTest)
	int32 MyInt_Default = 123;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category=ResetToDefaultTest, meta = (NoResetToDefault))
	int32 MyInt_NoResetToDefault = 123;
};

