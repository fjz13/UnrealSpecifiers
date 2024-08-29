// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProperty_AssetDataTags.generated.h"


USTRUCT(BlueprintType)
struct INSIDER_API FMyTableRow_Required :public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MyInt = 123;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString MyString;
};


USTRUCT(BlueprintType)
struct INSIDER_API FMyTableRow_Disallowed :public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MyFloat = 123.f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* MyTexture=nullptr;
};


UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyProperty_AssetDataTags :public UDataAsset
{
public:
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Object)
	TObjectPtr<UObject> MyAsset_Default;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Object, meta = (RequiredAssetDataTags = "MyIdForSearch=MyId456"))
	TObjectPtr<UObject> MyAsset_RequiredAssetDataTags;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Object, meta = (DisallowedAssetDataTags = "MyOtherId=MyOtherId789"))
	TObjectPtr<UObject> MyAsset_DisallowedAssetDataTags;
public:
	UPROPERTY(EditAnywhere, Category = DataTable)
	TObjectPtr<class UDataTable> MyDataTable_Default;

	UPROPERTY(EditAnywhere, Category = DataTable, meta = (RequiredAssetDataTags = "RowStructure=/Script/Insider.MyTableRow_Required"))
	TObjectPtr<class UDataTable> MyDataTable_RequiredAssetDataTags;

	UPROPERTY(EditAnywhere, Category = DataTable, meta = (DisallowedAssetDataTags = "RowStructure=/Script/Insider.MyTableRow_Disallowed"))
	TObjectPtr<class UDataTable> MyDataTable_DisallowedAssetDataTags;
};

