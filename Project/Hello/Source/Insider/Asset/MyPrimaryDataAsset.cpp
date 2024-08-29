// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "MyPrimaryDataAsset.h"


FPrimaryAssetId UMyPrimaryDataAsset::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(TEXT("MyAsset"),GetFName());
}


FPrimaryAssetId UMyPrimaryDataChildAsset::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(TEXT("MyAssetChild"),GetFName());
}
