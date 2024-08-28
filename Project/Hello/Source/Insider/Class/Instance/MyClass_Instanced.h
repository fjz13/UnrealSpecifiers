// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MyClass_Instanced.generated.h"


UCLASS(BlueprintType,NotBlueprintable)
class INSIDER_API UMyClass_Instanced :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyProperty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MyProperty2;
};

USTRUCT(BlueprintType)
struct FMyClassInstancedTableRow :public FTableRowBase
{
	GENERATED_BODY();
public:
	UPROPERTY(instanced, EditAnywhere, BlueprintReadWrite, Category = FeedBack)
		UMyClass_Instanced* ObjectWithInstanced=nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FeedBack)
		UMyClass_Instanced* ObjectWithoutInstanced=nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UTexture2D* Icon=nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Price=0.f;
};