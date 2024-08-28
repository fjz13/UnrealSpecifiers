// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyGameInstance.h"


void UMyGameInstance::PushUI(TSubclassOf < UUserWidget> widgetClass)
{

}

void UMyGameInstance::CompleteTask(FString taskName)
{

}

void UMyGameInstance::AddScore(float delta)
{
	Score += delta;
}