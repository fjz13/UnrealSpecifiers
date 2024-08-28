// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ShopItem.generated.h"

USTRUCT(BlueprintType)
struct FShopItem
{
	GENERATED_BODY();
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* Icon = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Price = 0.f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector MyVector={0.f,0.f,0.f};
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FRotator MyRotator={0.f,0.f,0.f};
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FTransform MyTransform;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<int32> IntArray;

};
