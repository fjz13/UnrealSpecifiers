// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyPython_ScriptOperator.generated.h"


USTRUCT(BlueprintType)
struct INSIDER_API FMyPythonMathStruct
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Value = 0;
};


UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyPython_Operator_Test :public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, meta = (ScriptMethod=HasValue,ScriptOperator = "bool"))
	static bool IsValid(const FMyPythonMathStruct& InStruct) { return InStruct.Value != 0; }

	UFUNCTION(BlueprintCallable, meta = (ScriptOperator = "neg"))
	static FMyPythonMathStruct Neg(const FMyPythonMathStruct& InStruct) { return { -InStruct.Value }; }

	UFUNCTION(BlueprintCallable, meta = (ScriptOperator = "=="))
	static bool IsEqual(const FMyPythonMathStruct& A, const FMyPythonMathStruct& B) { return A.Value == B.Value; }

	UFUNCTION(BlueprintCallable, meta = (ScriptOperator = "+;+="))
	static FMyPythonMathStruct AddInt(FMyPythonMathStruct InStruct, const int32 InValue) { InStruct.Value += InValue; return InStruct; }


};

