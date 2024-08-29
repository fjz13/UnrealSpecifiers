// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyFunction_BinaryOperator.generated.h"

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyFunction_BinaryOperator :public UBlueprintFunctionLibrary
{
public:
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, meta = (CommutativeAssociativeBinaryOperator))
	static float My_CallableAdd_WithBinaryOperator(float A, float B) { return A + B; }

	UFUNCTION(BlueprintPure, meta = (CommutativeAssociativeBinaryOperator))
	static float My_PureAdd_WithBinaryOperator(float A, float B) { return A + B; }

	UFUNCTION(BlueprintPure, meta = ())
	static float My_Add_NoBinaryOperator(float A, float B) { return A + B; }

	//error : Commutative associative binary operators must have exactly 2 parameters of the same type and a return value.
	//UFUNCTION(BlueprintPure, meta = (CommutativeAssociativeBinaryOperator))
	//static float My_PureAdd3_WithBinaryOperator(float A, float B,float C) { return A + B+C; }
};


