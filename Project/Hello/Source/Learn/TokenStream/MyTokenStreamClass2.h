// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyTokenStreamClass2.generated.h"

UCLASS(Blueprintable,Blueprintable)
class LEARN_API UMyTokenStreamClass2 :public UObject
{
	GENERATED_BODY()
public:
	UMyTokenStreamClass2();
public:
	UPROPERTY(BlueprintReadWrite)
	float Score;


};
