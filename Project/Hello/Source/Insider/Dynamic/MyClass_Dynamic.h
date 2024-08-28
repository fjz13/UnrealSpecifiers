// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyClass_Dynamic.generated.h"

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyClass_Dynamic :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyProperty;
	UFUNCTION(BlueprintCallable)
		void MyFunc();
public:
	UFUNCTION(BlueprintCallable)
	static void AddPropertyToMyClass();

};
