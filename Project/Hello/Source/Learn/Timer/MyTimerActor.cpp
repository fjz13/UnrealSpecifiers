// Fill out your copyright notice in the Description page of Project Settings.

#include "MyTimerActor.h"
#include "LearnTypes.h"

AMyTimerActor::AMyTimerActor()
{
	
}

// Called when the game starts or when spawned
void AMyTimerActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyTimerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyTimerActor::SetTimer(float delay, bool loop)
{
	GetWorldTimerManager().SetTimer(mTimer, this, &AMyTimerActor::OnTimerCallback, delay, loop);
}

void AMyTimerActor::OnTimerCallback()
{
	GEngine->AddOnScreenDebugMessage(-1, LearnTypes::ScreenMessageDuration, FColor::Red, L"OnTimerCallback");
}
