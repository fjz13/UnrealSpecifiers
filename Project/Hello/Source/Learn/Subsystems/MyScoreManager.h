// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "MyScoreManager.generated.h"

UCLASS()
class LEARN_API UMyScoreManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure,DisplayName="MyScoreManager")
	static UMyScoreManager* Instance();
public:
	UFUNCTION(BlueprintCallable)
		void AddScore(float delta);
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Score;
};

