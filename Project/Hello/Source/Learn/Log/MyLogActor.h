// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LogTypes.h"
#include "MyLogActor.generated.h"

UCLASS(Blueprintable)
class LEARN_API AMyLogActor :public AActor
{
	GENERATED_BODY()
public:
	AMyLogActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable)
		void AddOnScreenDebugMessage(int32 Key, float TimeToDisplay, FColor DisplayColor, const FString& DebugMessage, bool bNewerOnTop = true, const FVector2D& TextScale = FVector2D::UnitVector);
public:
	UFUNCTION(BlueprintCallable)
		void AddLog(const FString& DebugMessage, MyLogVerbosity verbosity= MyLogVerbosity::Display);
public:
	UFUNCTION(BlueprintCallable)
		void DrawDebugStringOnSelf(const FString& DebugMessage, FColor DisplayColor, float TimeToDisplay,bool castShadow=true);

	UFUNCTION(BlueprintCallable)
		void UseGLog(FString str);
};
