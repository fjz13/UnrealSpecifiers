// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyClass_UseMinimalAPI.generated.h"


UCLASS(Blueprintable)
class UMyClass_UseMinimalAPI :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyProperty;
	UFUNCTION(BlueprintCallable)
		void MyFunc() { ++MyProperty; }

	UFUNCTION(BlueprintCallable)
		void TestFunc();
};