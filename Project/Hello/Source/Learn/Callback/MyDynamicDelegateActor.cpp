// Fill out your copyright notice in the Description page of Project Settings.

#include "MyDynamicDelegateActor.h"
#include "LearnTypes.h"

AMyDynamicDelegateActor::AMyDynamicDelegateActor()
{
}

// Called when the game starts or when spawned
void AMyDynamicDelegateActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyDynamicDelegateActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyDynamicDelegateActor::ExecuteCallback(int32 val)
{
	OnMulticastDelegateAssignAndCall.Broadcast(val);
	OnMulticastDelegateAssign.Broadcast(val);
	OnMulticastDelegate.Broadcast(val);
	OnSinglecastDelegate.ExecuteIfBound(val);
}

void AMyDynamicDelegateActor::AddDelegate(FMyDynamicSinglecastDelegate_One Event)
{
	OnMulticastDelegateAssignAndCall.Add(Event);
}
