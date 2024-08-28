// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyFunction_Custom.generated.h"

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyFunction_Custom : public UObject
{
public:
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, CustomThunk)
	static int32 MyFunc_CustomDivide(int32 A, int32 B = 1);
	DECLARE_FUNCTION(execMyFunc_CustomDivide);


public:
	//(CustomStructureParam = inputStruct, CustomThunk = true, DisplayName = PrintStructFields, ModuleRelativePath = Function/MyFunction_Custom.h)
	UFUNCTION(BlueprintCallable, CustomThunk, meta = (DisplayName = "PrintStructFields", CustomStructureParam = "inputStruct"))
	static FString PrintStructFields(const int32& inputStruct) { return TEXT(""); }
	DECLARE_FUNCTION(execPrintStructFields);
	static FString Generic_PrintStructFields(const UScriptStruct* ScriptStruct, const void* StructData);
};
