// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProperty_GetAssetFilter.h"
#include "Asset/MyDataAsset.h"


bool UMyProperty_GetAssetFilter::IsShouldFilterAsset(const FAssetData& AssetData)
{
	return !AssetData.IsInstanceOf<UDataAsset>();
}
