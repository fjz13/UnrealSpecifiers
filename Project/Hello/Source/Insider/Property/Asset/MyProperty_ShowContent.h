// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProperty_ShowContent.generated.h"

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyProperty_ShowContent :public UDataAsset
{
public:
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Object)
	TObjectPtr<UObject> MyAsset_Default;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Object, meta = (ForceShowEngineContent))
	TObjectPtr<UObject> MyAsset_ForceShowEngineContent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Object, meta = (ForceShowPluginContent))
	TObjectPtr<UObject> MyAsset_ForceShowPluginContent;
};

