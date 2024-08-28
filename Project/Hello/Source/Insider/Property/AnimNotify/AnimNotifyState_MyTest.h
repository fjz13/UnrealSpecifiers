// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/CommonTypes.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_MyTest.generated.h"

UCLASS(BlueprintType)
class INSIDER_API UAnimNotifyState_MyTest :public UAnimNotifyState
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName MyName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta=(AnimNotifyBoneName="true"))
	FName MyName_Bone;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoExpand)
	FMyCommonStruct MyStruct;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Expand, meta = (AnimNotifyExpand = "true"))
	FMyCommonStruct MyStruct_Expand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NoExpand)
	UMyCommonObject* MyObject;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Expand, meta = (AnimNotifyExpand = "true"))
	UMyCommonObject* MyObject_Expand;
};

