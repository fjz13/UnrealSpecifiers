#pragma once
#include "InsiderTypes.h"
#include "Logging/LogMacros.h"

DECLARE_LOG_CATEGORY_EXTERN(LogInsider, Log, All);

#define LOG_INSIDER(Format, ...)	UE_LOG( LogInsider, Log, TEXT(Format), ##__VA_ARGS__ )
#define LOG_INSIDER(Format, ...)	UE_LOG( LogInsider, Log, TEXT(Format), ##__VA_ARGS__ )


INSIDER_BEGIN;

class LogHelper
{
public:
	static void AddOnScreenDebugMessage(int32 Key, float TimeToDisplay, FColor DisplayColor, const FString& DebugMessage, bool bNewerOnTop = true, const FVector2D& TextScale = FVector2D::UnitVector);
	static void UseGLog(FString str);
};


INSIDER_END;