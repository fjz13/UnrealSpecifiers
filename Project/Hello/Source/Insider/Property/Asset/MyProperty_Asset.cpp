// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "MyProperty_Asset.h"



FPrimaryAssetId UMyProperty_Asset_Item::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(TEXT("MyProperty_Asset_Item"), GetFName());
}
