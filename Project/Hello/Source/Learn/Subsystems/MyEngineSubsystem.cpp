// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyEngineSubsystem.h"

void UMyEngineSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{

}

void UMyEngineSubsystem::Deinitialize()
{

}

void UMyEngineSubsystem::AddScore(float delta)
{
	Score+=delta;
}