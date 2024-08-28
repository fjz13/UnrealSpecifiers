// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyVector.generated.h"

USTRUCT(Blueprintable)
struct LEARN_API FMyVector
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float X=0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Y=0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Z=0.f;

};
