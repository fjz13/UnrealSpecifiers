// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyLocalPlayerSubsystem.h"

void UMyLocalPlayerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{

}

void UMyLocalPlayerSubsystem::Deinitialize()
{

}

void UMyLocalPlayerSubsystem::AddScore(float delta)
{
	ULocalPlayer* player= GetLocalPlayer();
	APlayerController* pc= player->GetPlayerController(nullptr);
	Score+=delta;
}