// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MyProperty_Asset.generated.h"

UCLASS(BlueprintType)
class INSIDER_API UMyProperty_Asset_ChildObject :public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AssetBundles = "Client"))
	TSoftObjectPtr<UTexture2D> ChildIcon;
};


UCLASS(BlueprintType)
class INSIDER_API UMyProperty_Asset_Item :public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AssetBundles = "UI,Game"))
	TSoftObjectPtr<UTexture2D> Icon;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AssetBundles = "Game"))
	TSoftObjectPtr<UStaticMesh> Mesh;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UMyProperty_Asset_ChildObject> MyChildObject_NotIncludeAssetBundles;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (IncludeAssetBundles))
	TObjectPtr<UMyProperty_Asset_ChildObject> MyChildObject_IncludeAssetBundles;
public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};


UCLASS(BlueprintType)
class INSIDER_API UMyProperty_PrimaryAsset :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PrimaryAsset")
	FPrimaryAssetId MyPrimaryAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PrimaryAsset",meta=(AllowedTypes="MyAsset"))
	FPrimaryAssetId MyPrimaryAsset_Allowed;
};

