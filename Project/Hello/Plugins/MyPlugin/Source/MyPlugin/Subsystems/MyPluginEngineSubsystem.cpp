// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyPluginEngineSubsystem.h"

void UMyPluginEngineSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{

}

void UMyPluginEngineSubsystem::Deinitialize()
{

}

void UMyPluginEngineSubsystem::AddScore(float delta)
{
	Score+=delta;
}