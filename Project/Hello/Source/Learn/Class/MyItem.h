// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyItem.generated.h"

UCLASS(BlueprintType)
class LEARN_API UMyItem :public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere,meta=(ExposeOnSpawn))
		int32 Id;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn))
		float Weight;
};
