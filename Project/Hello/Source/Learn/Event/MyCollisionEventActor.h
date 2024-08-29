// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyCollisionEventActor.generated.h"


UCLASS(Blueprintable)
class LEARN_API AMyCollisionEventActor :public AActor
{
	GENERATED_BODY()
public:
	AMyCollisionEventActor();
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* mBoxComponent;

protected:
	//begin overlap
	UFUNCTION()
	void OnMyBeginOverlap(AActor* overlapAcor, AActor* otherActor);
};
