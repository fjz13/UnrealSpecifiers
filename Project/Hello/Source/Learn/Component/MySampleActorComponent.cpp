// Fill out your copyright notice in the Description page of Project Settings.

#include "MySampleActorComponent.h"


// Sets default values
UMySampleActorComponent::UMySampleActorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UMySampleActorComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UMySampleActorComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	AActor* actor = GetOwner();
	FRotator delta = RotationSpeed*DeltaTime;
	actor->AddActorLocalRotation(delta);
}
