// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MyClass_LoadBehavior.generated.h"


//(BlueprintType = true, IncludePath = Property/MyProperty_Asset.h, IsBlueprintBase = true, LoadBehavior = Eager, ModuleRelativePath = Property/MyProperty_Asset.h)
UCLASS(Blueprintable, Blueprintable, meta = (LoadBehavior = "Eager"))
class INSIDER_API UMyDataAsset_Eager :public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Score;
};

//(BlueprintType = true, IncludePath = Property/MyProperty_Asset.h, IsBlueprintBase = true, LoadBehavior = LazyOnDemand, ModuleRelativePath = Property/MyProperty_Asset.h)
UCLASS(Blueprintable, Blueprintable, meta = (LoadBehavior = "LazyOnDemand"))
class INSIDER_API UMyDataAsset_LazyOnDemand :public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Score;
};


UCLASS(BlueprintType)
class INSIDER_API UMyClass_LoadBehaviorTest :public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UMyDataAsset_LazyOnDemand> MyLazyOnDemand_AssetPtr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UMyDataAsset_Eager> MyEager_AssetPtr;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere,meta = (LoadBehavior = "Eager"))
	TObjectPtr<UMyDataAsset_LazyOnDemand> MyLazyOnDemand_AssetPtr_EagerOnProperty;

	UPROPERTY(BlueprintReadWrite, EditAnywhere,meta = (LoadBehavior = "LazyOnDemand"))
	TObjectPtr<UMyDataAsset_Eager> MyEager_AssetPtr_LazyOnDemandOnProperty;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UMyDataAsset_LazyOnDemand* MyLazyOnDemand_Asset;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UMyDataAsset_Eager* MyEager_Asset;

public:
	static void RegisterObjectHandleCallback();
	UFUNCTION(BlueprintCallable)
	static void LoadBehaviorTest();
};