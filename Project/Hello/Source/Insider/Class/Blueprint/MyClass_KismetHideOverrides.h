// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyClass_KismetHideOverrides.generated.h"


UCLASS(Blueprintable,meta=(KismetHideOverrides="ReceiveFloat"))
class INSIDER_API UMyClass_KismetHideOverrides :public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveFloat(float Value);

	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveString(const FString& Value);

};

UCLASS(Blueprintable,meta=(KismetHideOverrides="ReceiveFloat"))
class INSIDER_API AMyActor_KismetHideOverrides :public AActor
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveFloat(float Value);

	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveString(const FString& Value);

};
