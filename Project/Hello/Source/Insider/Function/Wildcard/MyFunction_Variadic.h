// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyFunction_Variadic.generated.h"

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyFunction_Variadic : public UBlueprintFunctionLibrary
{
public:
	GENERATED_BODY()
public:
	/*
			[PrintVariadicFields	Function->Struct->Field->Object	/Script/Insider.MyFunction_Variadic:PrintVariadicFields]
			(BlueprintInternalUseOnly = true, BlueprintType = true, CustomThunk = true, ModuleRelativePath = Function/Variadic/MyFunction_Variadic.h, Variadic = )
	*/
	UFUNCTION(BlueprintCallable, CustomThunk, BlueprintInternalUseOnly, meta = (Variadic))
	static FString PrintVariadicFields(const TArray<FString>& Inputs, const TArray<FString>& Outputs);
	DECLARE_FUNCTION(execPrintVariadicFields);
};
