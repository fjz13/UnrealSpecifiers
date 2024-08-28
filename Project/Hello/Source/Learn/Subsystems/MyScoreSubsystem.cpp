// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyScoreSubsystem.h"

void UMyScoreSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	
}

void UMyScoreSubsystem::Deinitialize()
{
}

void UMyScoreSubsystem::Tick(float DeltaTime)
{

}

TStatId UMyScoreSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UMyScoreSubsystem, STATGROUP_Tickables);
}

void UMyScoreSubsystem::AddScore(float delta)
{
	Score += delta;
	OnScoreChanged.Broadcast(Score);
}