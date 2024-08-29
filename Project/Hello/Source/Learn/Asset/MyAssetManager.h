// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "Misc/AssetRegistryInterface.h"
#include "MyAssetManager.generated.h"

inline uint32 GetTypeHash(const FAssetDependency& dep)
{
	return GetTypeHash(dep.AssetId)^(uint32)dep.Category^(uint32)dep.Properties;
}

DECLARE_DYNAMIC_DELEGATE(FOnPackageLoaded);

UCLASS(Blueprintable, Blueprintable)
class LEARN_API UMyAssetManager :public UAssetManager
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, CallInEditor,DisplayName="MyAssetManager")
	static UMyAssetManager* Get();
public:
	virtual void StartInitialLoading() override;
private:
	void OnAssetLoaded(UObject* Asset);
	void OnAsyncAssetLoaded(FSoftObjectPath Path);
	void OnPackageLoaded(const FName& PackageName, UPackage* LoadedPackage, EAsyncLoadingResult::Type Result);
public:
	UFUNCTION(BlueprintCallable, CallInEditor)
		FString PrintAssetReferences(FString Path);

	UFUNCTION(BlueprintCallable, CallInEditor)
		FString MyLoadObject(FString Path);

	UFUNCTION(BlueprintCallable, CallInEditor)
		FString MyLoadPackage(FString Path);

	UFUNCTION(BlueprintCallable, CallInEditor)
		FString MyFindObject(FString Path);

	UFUNCTION(BlueprintCallable, CallInEditor)
		FString MyAsyncLoadObject(FSoftObjectPath Path, FOnPackageLoaded OnPackageLoaded);

	UFUNCTION(BlueprintPure, CallInEditor)
	float GetCurrentLoadProgress(int32& LoadedCount, int32& RequestedCount)const;

	UFUNCTION(BlueprintCallable, CallInEditor)
		void ReleaseStreamableHandle();
private:
	TArray<FString> NewLoadedAssets;
	TSharedPtr<FStreamableHandle> CurrentStreamableHandle;
	FString CurrentLoadPackage;
private:
	static FString DependencyCategoryToString(UE::AssetRegistry::EDependencyCategory Category);
	static FString DependencyPropertyToString(UE::AssetRegistry::EDependencyProperty Properties);

	static void GetDependciesRecursive(FAssetIdentifier path,TSet<FAssetDependency>& outDeps);
};
