// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "MyGameInstance.generated.h"

UCLASS()
class LEARN_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public://UIϵͳ
	UFUNCTION(BlueprintCallable)
		void PushUI(TSubclassOf<UUserWidget> widgetClass);
public://����ϵͳ
	UFUNCTION(BlueprintCallable)
		void CompleteTask(FString taskName);
public://�Ʒ�ϵͳ
	UFUNCTION(BlueprintCallable)
		void AddScore(float delta);
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Score;
};

