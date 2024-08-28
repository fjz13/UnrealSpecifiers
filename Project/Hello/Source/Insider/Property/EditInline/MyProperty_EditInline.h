// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/CommonTypes.h"
#include "MyProperty_EditInline.generated.h"

USTRUCT(BlueprintType)
struct FMyPropertyEditInline
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StructInnerInt = 123;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString StructInnerString;
};

UCLASS(BlueprintType)
class INSIDER_API UMyProperty_EditInline_Sub :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ObjectInnerInt = 123;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ObjectInnerString;
};


UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyProperty_EditInline :public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FMyPropertyEditInline MyStruct;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditInline))
	FMyPropertyEditInline MyStruct_EditInline;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (NoEditInline))
	FMyPropertyEditInline MyStruct_NoEditInline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMyProperty_EditInline_Sub* MyObject;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditInline))
	UMyProperty_EditInline_Sub* MyObject_EditInline;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (NoEditInline))
	UMyProperty_EditInline_Sub* MyObject_NoEditInline;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UMyProperty_EditInline_Sub*> MyObjectArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditInline))
	TArray<UMyProperty_EditInline_Sub*> MyObjectArray_EditInline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (NoEditInline))
	TArray<UMyProperty_EditInline_Sub*> MyObjectArray_NoEditInline;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FMyCommonStruct, int32> MyStructMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ForceInlineRow))
	TMap<FMyCommonStruct, int32> MyStructMap_ForceInlineRow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<int32, FMyCommonStruct> MyStructMap2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ForceInlineRow))
	TMap<int32, FMyCommonStruct> MyStructMap_ForceInlineRow2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FMyCommonStruct> MyStructArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ForceInlineRow))
	TArray<FMyCommonStruct> MyStructArray_ForceInlineRow;
public:
	UFUNCTION(CallInEditor)
	void ClearInnerObject();
	UFUNCTION(CallInEditor)
	void InitInnerObject();

	UFUNCTION(CallInEditor)
	void AddMeta();

	UFUNCTION(CallInEditor)
	void RemoveMeta();
};

