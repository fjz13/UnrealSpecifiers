// Fill out your copyright notice in the Description page of Project Settings.

#include "MyFunction_Async.h"
#include "Engine/World.h"
#include "TimerManager.h"

#if WITH_EDITOR
#include <BlueprintActionDatabase.h>
#endif

UMyFunction_Async* UMyFunction_Async::DelayLoop(const UObject* WorldContextObject,
	const float DelayInSeconds, const int Iterations)
{
	UMyFunction_Async* Node = NewObject<UMyFunction_Async>();
	Node->WorldContextObject = WorldContextObject;
	Node->MyDelay = DelayInSeconds;
	Node->MyIterations = Iterations;
	return Node;
}


void UMyFunction_Async::Activate()
{
	if (nullptr == WorldContextObject)
	{
		FFrame::KismetExecutionMessage(TEXT("Invalid WorldContextObject."),
			ELogVerbosity::Error);
		return;
	}
	if (Active)
	{
		FFrame::KismetExecutionMessage(TEXT("DelayLoop is already running."),
			ELogVerbosity::Warning);
	}
	if (MyDelay <= 0.0f)
	{
		FFrame::KismetExecutionMessage(
			TEXT("DelayLoop delay can't be less or equal to 0."),
			ELogVerbosity::Warning);
	}
	if (MyIterations <= 0)
	{
		FFrame::KismetExecutionMessage(
			TEXT("DelayLoop iterations can't be less or equal to 0."),
			ELogVerbosity::Warning);
	}

	Active = true;
	for (int i = 0; i <= MyIterations; i++)
	{
		FTimerHandle IterationTimer;
		WorldContextObject->GetWorld()->GetTimerManager().SetTimer(
			IterationTimer, this, &UMyFunction_Async::ExecuteLoop, MyDelay * i);
	}

	FTimerHandle CompleteTimer;
	WorldContextObject->GetWorld()->GetTimerManager().SetTimer(
		CompleteTimer, this, &UMyFunction_Async::ExecuteComplete,
		MyDelay * (MyIterations + 1));
	// If the Complete pin should happen at the same time as the last iteration
	// use `MyDelay * MyIterations` here instead

}

void UMyFunction_Async::Test()
{
#if WITH_EDITOR

	FBlueprintActionDatabase& ActionDatabase = FBlueprintActionDatabase::Get();
	FBlueprintActionDatabase::FActionRegistry const& ActionRegistry = ActionDatabase.GetAllActions();

	for (auto Iterator(ActionRegistry.CreateConstIterator()); Iterator; ++Iterator)
	{
		const FObjectKey& ObjKey = Iterator->Key;
		const FBlueprintActionDatabase::FActionList& ActionList = Iterator->Value;

		if (UObject* ActionObject = ObjKey.ResolveObjectPtr())
		{
			if (ActionObject->GetName() == TEXT("AbilityTask_MoveToLocation"))
			{
				for (UBlueprintNodeSpawner const* NodeSpawner : ActionList)
				{
					FBlueprintActionInfo BlueprintAction(ActionObject, NodeSpawner);

				}
			}
		}
		else
		{
		}
	}
#endif
}

void UMyFunction_Async::ExecuteLoop()
{
	Loop.Broadcast();
}

void UMyFunction_Async::ExecuteComplete()
{
	Complete.Broadcast();
	Active = false;
}