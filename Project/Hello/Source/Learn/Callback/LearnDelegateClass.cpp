// Fill out your copyright notice in the Description page of Project Settings.

#include "LearnDelegateClass.h"
#include "LearnTypes.h"

LearnDelegateClass::LearnDelegateClass()
{
	
}

LearnDelegateClass::~LearnDelegateClass()
{
	
}

void LearnDelegateClass::PrintIntRaw(int32 val)
{
	FString str = FString::Printf(L"%s:%d", L"PrintIntRaw", val);
	GEngine->AddOnScreenDebugMessage(-1, LearnTypes::ScreenMessageDuration, FColor::Red, str);
}

void LearnDelegateClass::PrintIntSP(int32 val)
{
	FString str = FString::Printf(L"%s:%d", L"PrintIntSP", val);
	GEngine->AddOnScreenDebugMessage(-1, LearnTypes::ScreenMessageDuration, FColor::Red, str);
}
