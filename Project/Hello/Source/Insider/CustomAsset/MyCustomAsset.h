// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/CommonTypes.h"
#include "MyCustomAsset.generated.h"

//this object is used to check AllowEditInlineCustomization
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyCustomAsset :public UObject
{
	GENERATED_BODY()
public:
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditInline))
	UMyCommonObject* MyCommonObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditInline,AllowEditInlineCustomization))
	UMyCommonObject* MyCommonObject_Customization;
public:
	UFUNCTION(CallInEditor)
	void ClearInnerObject();
	UFUNCTION(CallInEditor)
	void InitInnerObject();
};

