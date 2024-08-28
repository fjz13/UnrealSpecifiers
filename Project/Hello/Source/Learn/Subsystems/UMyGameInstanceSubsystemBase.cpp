// Copyright Epic Games, Inc. All Rights Reserved.

#include "UMyGameInstanceSubsystemBase.h"

void UMyGameInstanceSubsystemBase::Initialize(FSubsystemCollectionBase& Collection)
{

}

void UMyGameInstanceSubsystemBase::Deinitialize()
{

}

void UMyGameInstanceSubsystemBase::AddScore(float delta)
{
	Score += delta;
}

void UMyGameInstanceSubsystemBase::MyTest(UGameInstance* gi)
{
	//TArray<UMyGameInstanceSubsystemBase*> items = gi->GetSubsystemArrayCopy<UMyGameInstanceSubsystemBase>();
}
