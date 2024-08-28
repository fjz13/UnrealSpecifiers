// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomAsset/MyCustomAssetTypeActions.h"


class FInsiderEditorModule :public IModuleInterface
{
public:
	virtual void StartupModule()override;
	virtual void ShutdownModule()override;
private:
	TSharedPtr<FMyCustomAssetTypeActions> MyCustomAssetTypeActions;
};