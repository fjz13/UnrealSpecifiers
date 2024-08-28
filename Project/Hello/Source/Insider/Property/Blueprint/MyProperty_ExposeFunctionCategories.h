// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProperty_ExposeFunctionCategories.generated.h"

UCLASS(BlueprintType)
class INSIDER_API UMyProperty_ExposeFunctionCategories :public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "FirstFunc")
	void MyExposeFunc1() {}
	UFUNCTION(BlueprintCallable, Category = "SecondFunc")
	void MyExposeFunc2() {}
	UFUNCTION(BlueprintCallable, Category = "ThirdFunc")
	void MyExposeFunc3() {}
};

UCLASS(BlueprintType)
class INSIDER_API UMyProperty_ExposeFunctionCategories_Test :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, meta = (ExposeFunctionCategories = "FirstFunc,ThirdFunc"))
	UMyProperty_ExposeFunctionCategories* MyObject_Expose;
};
