// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MyPrimaryDataAsset.generated.h"

UCLASS(BlueprintType)
class INSIDER_API UMyPrimaryDataAsset :public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
		FText Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UTexture2D* Icon;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Price;
public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};

UCLASS(BlueprintType)
class INSIDER_API UMyPrimaryDataChildAsset :public UMyPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString MyString;
public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};