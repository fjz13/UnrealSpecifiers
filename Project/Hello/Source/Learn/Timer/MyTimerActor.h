// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyTimerActor.generated.h"


UCLASS(Blueprintable)
class LEARN_API AMyTimerActor :public AActor
{
	GENERATED_BODY()
public:
	AMyTimerActor();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	UFUNCTION(BlueprintCallable)
		void SetTimer(float delay,bool loop=false);

	void OnTimerCallback();
private:
	FTimerHandle mTimer;
};
