// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataAsset.h"
#include "MyDataAsset.generated.h"


UCLASS(Blueprintable, Blueprintable)
class INSIDER_API UMyDataAsset :public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Score;

	UMyDataAsset(const FObjectInitializer& initializer);
public:
	virtual void PostLoad()override;
	virtual void PostInitProperties()override;
	static void CreateNewAsset(FString assetName, bool isTextFormat = false);
};
