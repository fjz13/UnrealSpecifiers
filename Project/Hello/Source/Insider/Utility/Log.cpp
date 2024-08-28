// Fill out your copyright notice in the Description page of Project Settings.

#include "Log.h"

DEFINE_LOG_CATEGORY(LogInsider);

INSIDER_BEGIN;


void LogHelper::AddOnScreenDebugMessage(int32 Key, float TimeToDisplay, FColor DisplayColor, const FString& DebugMessage, bool bNewerOnTop /*= true*/, const FVector2D& TextScale /*= FVector2D::UnitVector*/)
{
	GEngine->AddOnScreenDebugMessage(Key, TimeToDisplay, DisplayColor, DebugMessage,bNewerOnTop,TextScale);
}


void LogHelper::UseGLog(FString str)
{
	GLog->Log(*str);
}

INSIDER_END;
