// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyPluginEditorSubsystem.h"

void UMyPluginEditorSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{

}

void UMyPluginEditorSubsystem::Deinitialize()
{

}

void UMyPluginEditorSubsystem::AddScore(float delta)
{
	Score+=delta;
}
