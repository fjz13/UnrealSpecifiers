// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyTokenStreamStructCycle.h"
#include "MyTokenStreamClass3.generated.h"

UCLASS(Blueprintable,Blueprintable)
class LEARN_API UMyTokenStreamClass3 :public UObject
{
	GENERATED_BODY()
public:
	UMyTokenStreamClass3();
public:
	UPROPERTY()
		FMyTokenStreamStructCycle CycleStructValue;

};
