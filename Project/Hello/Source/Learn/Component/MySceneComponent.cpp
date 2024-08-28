// Fill out your copyright notice in the Description page of Project Settings.

#include "MySceneComponent.h"


// Sets default values
UMySceneComponent::UMySceneComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UMySceneComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UMySceneComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FRotator delta = RotationSpeed*DeltaTime;
	AddRelativeRotation(delta);
}
