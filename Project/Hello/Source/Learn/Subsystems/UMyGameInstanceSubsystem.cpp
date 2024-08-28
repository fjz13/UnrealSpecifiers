// Copyright Epic Games, Inc. All Rights Reserved.

#include "UMyGameInstanceSubsystem.h"
#include "MyScoreSubsystem.h"

void UMyGameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Collection.InitializeDependency(UMyScoreSubsystem::StaticClass());

	
	UMyScoreSubsystem* ss=((FSubsystemCollection<UGameInstanceSubsystem>&)Collection).GetSubsystem<UMyScoreSubsystem>(UMyScoreSubsystem::StaticClass());
	//UMyScoreSubsystem* ss= Collection.GetSubsystem<UMyScoreSubsystem>();
}

void UMyGameInstanceSubsystem::Deinitialize()
{

}

void UMyGameInstanceSubsystem::AddScore(float delta)
{
	Score+=delta;
}

void UMyGameInstanceSubsystem::MyTest(UGameInstance* gi)
{
	//TArray<UMyGameInstanceSubsystem*>& items=  gi->GetSubsystemArray<UMyGameInstanceSubsystem>();


}
