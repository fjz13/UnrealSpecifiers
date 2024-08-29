// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyScoreManager.h"


UMyScoreManager* UMyScoreManager::Instance()
{
	static UMyScoreManager* instance=nullptr;
	if (instance==nullptr)
	{
		instance=NewObject<UMyScoreManager>();
		instance->AddToRoot();
	}
	return instance;
	//return GetMutableDefault<UMyScoreManager>();
}

void UMyScoreManager::AddScore(float delta)
{
	Score += delta;
}