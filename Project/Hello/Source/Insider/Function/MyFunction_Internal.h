// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyFunction_Internal.generated.h"

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyFunction_Internal :public AActor
{
public:
	GENERATED_BODY()
public:
	//(BlueprintInternalUseOnly = true, BlueprintType = true, ModuleRelativePath = Function/MyFunction_Internal.h)
	//FunctionFlags:	FUNC_Final | FUNC_Native | FUNC_Public | FUNC_BlueprintCallable 
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void MyFunc_InternalOnly();

	//FunctionFlags:	FUNC_Final | FUNC_Native | FUNC_Public | FUNC_BlueprintCallable 
	UFUNCTION(BlueprintCallable)
	void MyFunc_Default();


};
