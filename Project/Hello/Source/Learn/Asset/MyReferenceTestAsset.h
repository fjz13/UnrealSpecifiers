// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "MyReferenceTestAsset.generated.h"

UCLASS(BlueprintType)
class LEARN_API UMyReferenceTestAsset :public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UTexture2D* HardReferenceObject;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<AActor> HardReferenceClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(MetaClass ="/Script/Insider.Texture2D"))
		FSoftObjectPath SoftReferenceObject;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(MetaClass = "/Script/Insider.Actor"))
		FSoftClassPath SoftReferenceClass;


	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FPrimaryAssetType AssetType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FPrimaryAssetId AssetId;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSoftObjectPtr<UObject> SoftAsset;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSoftClassPtr<UObject> SoftAssetClass;
};