// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyConfigActor.generated.h"


UCLASS(Blueprintable)
class LEARN_API AMyConfigActor :public AActor
{
	GENERATED_BODY()
public:
	AMyConfigActor();

public:
	UFUNCTION(BlueprintCallable)
		void WriteConfig(FString sectionName, FString keyName, FString valueName, FString fileName);
	UFUNCTION(BlueprintCallable)
		FString ReadConfig(FString sectionName, FString keyName, FString fileName);
	
};
