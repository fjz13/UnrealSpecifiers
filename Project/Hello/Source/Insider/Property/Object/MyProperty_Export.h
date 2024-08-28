// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProperty_Export.generated.h"


UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyProperty_ExportObject :public UDataAsset
{
public:
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyValue = 123;
};


UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyProperty_Export :public UDataAsset
{
public:
public:
	GENERATED_BODY()
		UMyProperty_Export(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
public:
	//PropertyFlags:	CPF_Edit | CPF_BlueprintVisible | CPF_ExportObject | CPF_ZeroConstructor | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Export, Category = Behavior)
		UMyProperty_ExportObject* ObjectExport;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Behavior)
		UMyProperty_ExportObject* ObjectWithoutExport;
};

