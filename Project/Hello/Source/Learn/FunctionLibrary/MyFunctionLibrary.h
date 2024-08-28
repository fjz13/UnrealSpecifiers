// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyFunctionLibrary.generated.h"

UCLASS()
class LEARN_API UMyFunctionLibrary :public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "MyFunctionLibrary")
	static int32 MyFunction_Call(int32 val);

	UFUNCTION(BlueprintPure, Category = "MyFunctionLibrary")
		static int32 MyFunction_Pure();

};
