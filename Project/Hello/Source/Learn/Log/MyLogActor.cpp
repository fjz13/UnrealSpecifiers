// Fill out your copyright notice in the Description page of Project Settings.

#include "MyLogActor.h"
#include "DrawDebugHelpers.h"
#include "LearnTypes.h"

AMyLogActor::AMyLogActor()
{

}

// Called when the game starts or when spawned
void AMyLogActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMyLogActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyLogActor::AddOnScreenDebugMessage(int32 Key, float TimeToDisplay, FColor DisplayColor, const FString& DebugMessage, bool bNewerOnTop /*= true*/, const FVector2D& TextScale /*= FVector2D::UnitVector*/)
{
	GEngine->AddOnScreenDebugMessage(Key, TimeToDisplay, DisplayColor, DebugMessage,bNewerOnTop,TextScale);
}

void AMyLogActor::AddLog(const FString& DebugMessage, MyLogVerbosity verbosity/*= MyLogVerbosity::Display*/)
{
	switch (verbosity)
	{
		break;
	case MyLogVerbosity::Fatal:
		UE_LOG(LogLearn, Fatal, TEXT("%s"), *DebugMessage);
		break;
	case MyLogVerbosity::Error:
		UE_LOG(LogLearn, Error, TEXT("%s"), *DebugMessage);
		break;
	case MyLogVerbosity::Warning:
		UE_LOG(LogLearn, Warning, TEXT("%s"), *DebugMessage);
		break;
	case MyLogVerbosity::Display:
		UE_LOG(LogLearn, Display, TEXT("%s"), *DebugMessage);
		break;
	case MyLogVerbosity::Log:
		UE_LOG(LogLearn, Log, TEXT("%s"), *DebugMessage);
		break;
	case MyLogVerbosity::Verbose:
		UE_LOG(LogLearn, Verbose, TEXT("%s"), *DebugMessage);
		break;
	case MyLogVerbosity::VeryVerbose:
	case MyLogVerbosity::All:
		UE_LOG(LogLearn, VeryVerbose, TEXT("%s"), *DebugMessage);
		break;
	case MyLogVerbosity::NoLogging:
	default:
		break;
	}
}

void AMyLogActor::DrawDebugStringOnSelf(const FString& DebugMessage, FColor DisplayColor, float TimeToDisplay, bool castShadow/*=false*/)
{
	DrawDebugString(GetWorld(), GetActorLocation(), DebugMessage, nullptr, DisplayColor, TimeToDisplay, castShadow);
	GLog->Log("BeginPlay");

}

void AMyLogActor::UseGLog(FString str)
{
	GLog->Log(*str);
}