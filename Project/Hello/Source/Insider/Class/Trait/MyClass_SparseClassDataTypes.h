// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyClass_SparseClassDataTypes.generated.h"

USTRUCT(BlueprintType)
struct FMySparseClassData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	int32 MyInt_EditDefaultOnly = 123;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MyInt_BlueprintReadOnly = 1024;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString MyString_EditDefault = TEXT("MyName");	//FString GetMyString_EditDefault() const { return GetMySparseClassData(EGetSparseClassDataMethod::ArchetypeIfNull)->MyString_EditDefault; } \

	// "GetByRef" means that Blueprint graphs access a const ref instead of a copy.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (GetByRef))
	FString MyString_EditDefault_ReadOnly = TEXT("MyName");	//const FString& GetMyString_EditDefault_ReadOnly() const { return GetMySparseClassData(EGetSparseClassDataMethod::ArchetypeIfNull)->MyString_EditDefault_ReadOnly; }

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (NoGetter))
	FString MyString_EditDefault_NoGetter = TEXT("MyName");
};


//(BlueprintType = true, IncludePath = Class / Trait / MyClass_SparseClassDataTypes.h, IsBlueprintBase = true, ModuleRelativePath = Class / Trait / MyClass_SparseClassDataTypes.h, SparseClassDataTypes = MySparseClassData)
UCLASS(Blueprintable, BlueprintType, SparseClassDataTypes = MySparseClassData)
class INSIDER_API AMyActor_SparseClassDataTypes :public AActor
{
	GENERATED_BODY()

public:
#if WITH_EDITOR
	// ~ This function transfers existing data into FMySparseClassData.
	//virtual void MoveDataToSparseClassDataStruct() const override;
#endif // WITH_EDITOR
public:
#if WITH_EDITORONLY_DATA
	//UPROPERTY()
	//	int32 MyInt_EditDefaultOnly_DEPRECATED = 123;

	//UPROPERTY()
	//	int32 MyInt_BlueprintReadOnly_DEPRECATED = 1024;

	//UPROPERTY()
	//	FString MyString_EditDefault_ReadOnly_DEPRECATED = TEXT("MyName");
#endif // WITH_EDITORONLY_DATA

public:
	//UFUNCTION(BlueprintPure)
	//int32 GetMyMyInt_BlueprintReadOnly()const;

public:
	UPROPERTY(EditAnywhere)
	float MyFloat_EditAnywhere = 555.f;

	UPROPERTY(BlueprintReadWrite)
	float MyFloat_BlueprintReadWrite = 666.f;
};
