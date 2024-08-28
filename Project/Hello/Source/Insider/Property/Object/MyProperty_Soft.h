// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProperty_Soft.generated.h"

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyProperty_Soft :public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UStaticMesh> MyStaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Untracked))
	TSoftObjectPtr<UStaticMesh> MyStaticMeshUntracked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSoftObjectPath MySoftMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Untracked))
	FSoftObjectPath MySoftMeshUntracked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient)
	TSoftObjectPtr<UStaticMesh> MyStaticMeshTransient;
};

