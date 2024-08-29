// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProperty_AssetRegistrySearchable.h"
#include "UObject/AssetRegistryTagsContext.h"

void UMyProperty_AssetRegistrySearchable::GetAssetRegistryTags(FAssetRegistryTagsContext Context) const
{
	//called on CDO and instances
	Super::GetAssetRegistryTags(Context);
	Context.AddTag(FAssetRegistryTag(TEXT("MyOtherId"),MyOtherIdForSearch, UObject::FAssetRegistryTag::TT_Alphabetical));
}
