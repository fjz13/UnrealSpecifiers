// Fill out your copyright notice in the Description page of Project Settings.

#include "MyDataAsset.h"
#include "Misc/Paths.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "HAL/FileManager.h"
#include "UObject/SavePackage.h"

UMyDataAsset::UMyDataAsset(const FObjectInitializer& initializer)
	:Super(initializer)
{
	Score = 9999.f;
	/*FString path = this->GetPathName();
	LOG_INSIDER("UMyDataAsset::UMyDataAsset %s", *path);

	FString objectFlags = Insider::ObjectFlagsToString(this->GetFlags());
	FString classFlags = Insider::ClassFlagsToString(this->GetClass()->GetClassFlags());
	LOG_INSIDER("UMyDataAsset::ObjectFlags %s", *objectFlags);
	LOG_INSIDER("UMyDataAsset::ClassFlags %s", *classFlags);

	LOG_INSIDER("UMyDataAsset::Score %f", Score);*/

}

void UMyDataAsset::PostLoad()
{
	Super::PostLoad();
	/*FString path= this->GetPathName();
	LOG_INSIDER("UMyDataAsset::PostLoad %s",*path);
	FString objectFlags = Insider::ObjectFlagsToString(this->GetFlags());
	FString classFlags = Insider::ClassFlagsToString(this->GetClass()->GetClassFlags());
	LOG_INSIDER("UMyDataAsset::ObjectFlags %s", *objectFlags);
	LOG_INSIDER("UMyDataAsset::ClassFlags %s", *classFlags);
	LOG_INSIDER("UMyDataAsset::Score %f", Score);*/
}

void UMyDataAsset::PostInitProperties()
{
	Super::PostInitProperties();

	/*FString path = this->GetPathName();
	LOG_INSIDER("UMyDataAsset::PostInitProperties %s", *path);
	FString objectFlags = Insider::ObjectFlagsToString(this->GetFlags());
	FString classFlags = Insider::ClassFlagsToString(this->GetClass()->GetClassFlags());
	LOG_INSIDER("UMyDataAsset::ObjectFlags %s", *objectFlags);
	LOG_INSIDER("UMyDataAsset::ClassFlags %s", *classFlags);

	LOG_INSIDER("UMyDataAsset::Score %f", Score);*/
}

void UMyDataAsset::CreateNewAsset(FString assetName, bool isTextFormat /*= false*/)
{
	//��Ҫ��ģ����Ϊ "LoadingPhase": "PostEngineInit"�����ܱ�֤GEditor�Ѿ����� �����������֤���ڳ���
	FString AssetPath = FPaths::ProjectContentDir();
	FString PackagePath = FPaths::Combine(TEXT("/Game/"), assetName);
	FString outPackageFilePath;
	if (FPackageName::DoesPackageExist(PackagePath, &outPackageFilePath))
	{
		IFileManager::Get().Delete(*outPackageFilePath);
	}

	FSavePackageArgs saveArgs;


	UPackage *Package = CreatePackage(*PackagePath);
	saveArgs.SaveFlags = SAVE_None;
	saveArgs.SaveFlags |= SAVE_KeepGUID;	//����Guid,���ò�����

	UMyDataAsset* TestAsset = NewObject<UMyDataAsset>(Package, UMyDataAsset::StaticClass(), *assetName, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone);

	TestAsset->Score = 9999.f;

	FAssetRegistryModule::AssetCreated(TestAsset);
	TestAsset->MarkPackageDirty();

	FString ext = isTextFormat ? FPackageName::GetTextAssetPackageExtension() : FPackageName::GetAssetPackageExtension();

	FString FilePath = FPackageName::LongPackageNameToFilename(PackagePath, ext);

	saveArgs.TopLevelFlags= EObjectFlags::RF_Public | EObjectFlags::RF_Standalone;
	saveArgs.Error=GError;


	bool bSuccess = UPackage::SavePackage(Package, TestAsset,*FilePath,saveArgs);

	Package->ConditionalBeginDestroy();	//ɾ���ڴ��еĶ��󣬷����ڱ༭����򿪺��ٱ��棬�������ҵ��ö��󣬵��±���ʧ��
	//LOG_INSIDER("Saved Package: %s", bSuccess ? TEXT("True") : TEXT("False"));
}