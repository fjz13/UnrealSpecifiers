// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyPluginGameInstanceSubsystem.h"

UMyPluginGameInstanceSubsystem::UMyPluginGameInstanceSubsystem()
{

}

void UMyPluginGameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{

}

void UMyPluginGameInstanceSubsystem::Deinitialize()
{

}

void UMyPluginGameInstanceSubsystem::AddScore(float delta)
{
	Score+=delta;
}