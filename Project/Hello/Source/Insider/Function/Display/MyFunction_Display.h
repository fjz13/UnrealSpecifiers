// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyFunction_Display.generated.h"

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyFunction_Display :public UBlueprintFunctionLibrary
{
public:
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, meta = (CompactNodeTitle = "MyCompact", DisplayName = "AnotherName"))
	static int32 MyFunc_HasCompactNodeTitle(FString Name) { return 0; }

	UFUNCTION(BlueprintCallable, meta = ())
	static int32 MyFunc_NoCompactNodeTitle(FString Name) { return 0; }

	UFUNCTION(BlueprintPure, meta = (CompactNodeTitle = "MyPure", DisplayName = "AnotherName"))
	static int32 MyPure_HasCompactNodeTitle(FString Name) { return 0; }

	UFUNCTION(BlueprintPure, meta = ())
	static int32 MyPure_NoCompactNodeTitle(FString Name) { return 0; }
public:
	UFUNCTION(BlueprintCallable, meta = (AdvancedDisplay = "2"))
	static int32 MyFunc_HasAdvancedDisplay_WithOrder(int32 First, int32 Second, /*CPF_AdvancedDisplay*/int32 Third,  /*CPF_AdvancedDisplay*/int32 Fourth, /*CPF_AdvancedDisplay*/ int32 Fifth) { return 0; }
	UFUNCTION(BlueprintCallable, meta = (AdvancedDisplay = "Fourth,Fifth"))
	static int32 MyFunc_HasAdvancedDisplay_WithName(int32 First, int32 Second, int32 Third,  /*CPF_AdvancedDisplay*/int32 Fourth, /*CPF_AdvancedDisplay*/ int32 Fifth) { return 0; }

	UFUNCTION(BlueprintCallable, meta = ())
	static int32 MyFunc_NoAdvancedDisplay(int32 First, int32 Second, int32 Third, int32 Fourth, int32 Fifth) { return 0; }

public:
	UFUNCTION(BlueprintCallable, meta = (ReturnDisplayName = "IsSuccess"))
	static bool MyFunc_HasReturnDisplayName(FString Name) { return true; }

	UFUNCTION(BlueprintCallable, meta = ())
	static bool MyFunc_NoReturnDisplayName(FString Name) { return true; }
};
