// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAssetManager.h"
#include "Log/LogTypes.h"
#include "UObject/UObjectGlobals.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Utility/InsiderSubsystem.h"


UMyAssetManager* UMyAssetManager::Get()
{
	UMyAssetManager* This = Cast<UMyAssetManager>(GEngine->AssetManager);

	if (This)
	{
		return This;
	}
	else
	{
		UE_LOG(LogLearn, Fatal, TEXT("Invalid AssetManager in DefaultEngine.ini, must be MyAssetManager!"));
		return NewObject<UMyAssetManager>(); // never calls this
	}
}

void UMyAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

#if WITH_EDITOR
	FCoreUObjectDelegates::OnAssetLoaded.AddUObject(this, &UMyAssetManager::OnAssetLoaded);
#endif

}

void UMyAssetManager::OnAssetLoaded(UObject* Asset)
{
	UE_LOG(LogLearn, Display, TEXT("%s Loaded"), *Asset->GetFullName());
	NewLoadedAssets.Add(Asset->GetFullName());
}


FString UMyAssetManager::DependencyCategoryToString(UE::AssetRegistry::EDependencyCategory flags)
{
	FString Result;
	if (EnumHasAnyFlags(flags, UE::AssetRegistry::EDependencyCategory::Package))
	{
		Result += TEXT("Package | ");
	}
	if (EnumHasAnyFlags(flags, UE::AssetRegistry::EDependencyCategory::Manage))
	{
		Result += TEXT("Manage | ");
	}
	if (EnumHasAnyFlags(flags, UE::AssetRegistry::EDependencyCategory::SearchableName))
	{
		Result += TEXT("SearchableName | ");
	}

	if (!Result.IsEmpty())
	{
		Result.RemoveAt(Result.Len() - 2, 2);
	}
	else
	{
		return "None";
	}
	return Result;
}

FString UMyAssetManager::DependencyPropertyToString(UE::AssetRegistry::EDependencyProperty flags)
{
	FString Result;

	if (EnumHasAnyFlags(flags, UE::AssetRegistry::EDependencyProperty::Hard))
	{
		Result += TEXT("Hard | ");
	}
	if (EnumHasAnyFlags(flags, UE::AssetRegistry::EDependencyProperty::Game))
	{
		Result += TEXT("Game | ");
	}
	if (EnumHasAnyFlags(flags, UE::AssetRegistry::EDependencyProperty::Build))
	{
		Result += TEXT("Build | ");
	}
	if (EnumHasAnyFlags(flags, UE::AssetRegistry::EDependencyProperty::Direct))
	{
		Result += TEXT("Direct | ");
	}

	if (!Result.IsEmpty())
	{
		Result.RemoveAt(Result.Len() - 2, 2);
	}
	else
	{
		return "None";
	}
	return Result;
}


FString UMyAssetManager::PrintAssetReferences(FString Path)
{
	FString Result;

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));

	FAssetIdentifier assetId(*Path);

	TArray<FAssetDependency> outReferences;
	AssetRegistryModule.Get().GetReferencers(assetId, outReferences, UE::AssetRegistry::EDependencyCategory::All);

	for (const FAssetDependency& dep : outReferences)
	{
		Result += FString::Printf(TEXT("Referencer:\t%s\t%s\t%s\n"), *dep.AssetId.ToString(), *DependencyCategoryToString(dep.Category), *DependencyPropertyToString(dep.Properties));
	}

	TArray<FAssetDependency> OutDependencies;
	AssetRegistryModule.Get().GetDependencies(assetId, OutDependencies, UE::AssetRegistry::EDependencyCategory::All);
	for (const FAssetDependency& dep : OutDependencies)
	{
		Result += FString::Printf(TEXT("Dependency:\t%s\t%s\t%s\n"), *dep.AssetId.ToString(), *DependencyCategoryToString(dep.Category), *DependencyPropertyToString(dep.Properties));
	}

	return Result;
}

FString UMyAssetManager::MyLoadObject(FString Path)
{
	FString result;
	NewLoadedAssets.Empty();
	UObject* obj = LoadObject<UObject>(nullptr, *Path);
	if (obj != nullptr)
	{
		result += FString::Printf(TEXT("Loaded:\t%s\n"), *obj->GetFullName());

		NewLoadedAssets.Remove(obj->GetFullName());//remove self
		for (const FString& str : NewLoadedAssets)
		{
			result += FString::Printf(TEXT("NewLoaded:\t%s\n"), *str);
		}

		FString str1 = UInsiderSubsystem::Get().PrintObject(obj, EInsiderPrintFlags::PackageDefault);
		UE_LOG(LogLearn, Warning, TEXT("\n%s\n"), *str1);

	}
	else
	{
		result += FString::Printf(TEXT("NotFound:\t%s\n"), *Path);
	}


	return result;
}

FString UMyAssetManager::MyLoadPackage(FString Path)
{
	FString result;
	NewLoadedAssets.Empty();
	UPackage* obj = LoadPackage(nullptr, *Path,LOAD_None);

	if (obj != nullptr)
	{
		result += FString::Printf(TEXT("Loaded:\t%s\n"), *obj->GetFullName());

		NewLoadedAssets.Remove(obj->GetFullName());//remove self
		for (const FString& str : NewLoadedAssets)
		{
			result += FString::Printf(TEXT("NewLoaded:\t%s\n"), *str);
		}

		FString str1 = UInsiderSubsystem::Get().PrintObject(obj, EInsiderPrintFlags::PackageDefault);
		UE_LOG(LogLearn, Warning, TEXT("\n%s\n"), *str1);

	}
	else
	{
		result += FString::Printf(TEXT("NotFound:\t%s\n"), *Path);
	}


	return result;
}

FString UMyAssetManager::MyFindObject(FString Path)
{
	FString result;
	NewLoadedAssets.Empty();
	UObject* obj = LoadObject<UObject>(nullptr, *Path);
	if (obj != nullptr)
	{
		result += FString::Printf(TEXT("Found:\t%s\n"), *obj->GetFullName());

		NewLoadedAssets.Remove(obj->GetFullName());//remove self
		for (const FString& str : NewLoadedAssets)
		{
			result += FString::Printf(TEXT("NewLoaded:\t%s\n"), *str);
		}
	}
	else
	{
		result += FString::Printf(TEXT("NotFound:\t%s\n"), *Path);
	}

	return result;
}

void UMyAssetManager::OnAsyncAssetLoaded(FSoftObjectPath Path)
{
	UE_LOG(LogLearn, Display, TEXT("%s load completed."), *Path.ToString());
}


void UMyAssetManager::OnPackageLoaded(const FName& PackageName, UPackage* LoadedPackage, EAsyncLoadingResult::Type Result)
{
	UE_LOG(LogLearn, Display, TEXT("%s load completed."), *PackageName.ToString());
}

void UMyAssetManager::GetDependciesRecursive(FAssetIdentifier assetId, TSet<FAssetDependency>& outDeps)
{
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));

	TArray<FAssetDependency> OutDependencies;
	AssetRegistryModule.Get().GetDependencies(assetId, OutDependencies, UE::AssetRegistry::EDependencyCategory::All);
	for (const FAssetDependency& dep : OutDependencies)
	{
		if (!EnumHasAnyFlags(dep.Properties, UE::AssetRegistry::EDependencyProperty::Hard))
		{
			continue;
		}
		bool isAlreayInSet = false;
		outDeps.Add(dep, &isAlreayInSet);
		if (!isAlreayInSet)
		{
			GetDependciesRecursive(dep.AssetId, outDeps);
		}
	}
}

FString UMyAssetManager::MyAsyncLoadObject(FSoftObjectPath Path, FOnPackageLoaded OnPackageLoaded)
{
	FString result;
	result += FString::Printf(TEXT("StartLoad:\t%s\n"), *Path.ToString());

	FStreamableManager& streamableManager = GetStreamableManager();
	//TArray<FSoftObjectPath> depAssets;
	
	//FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
	//TSet<FAssetDependency> OutDependencies;

	//GetDependciesRecursive(FAssetIdentifier(*Path.ToString()), OutDependencies);
	//for (const FAssetDependency& dep : OutDependencies)
	//{
	//	depAssets.Add(dep.AssetId.ToString());
	//}
	//depAssets.Add(Path);//add self
	//CurrentStreamableHandle = streamableManager.RequestAsyncLoad(depAssets, [=] {OnPackageLoaded.ExecuteIfBound(); });


	CurrentLoadPackage= Path.ToString();
	LoadPackageAsync(CurrentLoadPackage, FLoadPackageAsyncDelegate::CreateLambda([=](const FName& PackageName, UPackage* LoadedPackage, EAsyncLoadingResult::Type Result){OnPackageLoaded.ExecuteIfBound();}));

	return result;
}

float UMyAssetManager::GetCurrentLoadProgress(int32& LoadedCount, int32& RequestedCount) const
{
	return GetAsyncLoadPercentage(*CurrentLoadPackage);

	/*if (CurrentStreamableHandle.IsValid())
	{
		CurrentStreamableHandle->GetLoadedCount(LoadedCount, RequestedCount);
		return CurrentStreamableHandle->GetProgress() * 100.f;
	}*/
}

void UMyAssetManager::ReleaseStreamableHandle()
{
	if (CurrentStreamableHandle.IsValid())
	{
		CurrentStreamableHandle->ReleaseHandle();
	}
}
