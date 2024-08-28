// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MySampleActorComponent.generated.h"


UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent))
class LEARN_API UMySampleActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	UMySampleActorComponent();

public:
	virtual void BeginPlay()override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FRotator RotationSpeed;
};
