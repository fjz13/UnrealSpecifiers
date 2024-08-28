// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyClass_RestrictedToClasses.generated.h"

UCLASS(Blueprintable)
class INSIDER_API UMyClass_RestrictedToClasses :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float MyFloat;
};

UCLASS(meta=(RestrictedToClasses="MyClass_RestrictedToClasses"))
class INSIDER_API UMyClass_RestrictedToClassesLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	static float GetMyClassRestrictedFloat(UMyClass_RestrictedToClasses* myObject) {return myObject->MyFloat;}
};
