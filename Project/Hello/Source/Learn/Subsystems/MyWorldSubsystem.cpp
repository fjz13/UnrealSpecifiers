// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyWorldSubsystem.h"
#include "Kismet/GameplayStatics.h"

void UMyWorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{

}

void UMyWorldSubsystem::Deinitialize()
{

}

void UMyWorldSubsystem::AddScore(float delta)
{
	UWorld* world=GetWorld();
	AGameModeBase* gm= UGameplayStatics::GetGameMode(world);

	Score+=delta;
}