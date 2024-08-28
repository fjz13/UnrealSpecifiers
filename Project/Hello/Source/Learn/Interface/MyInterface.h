// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyInterface.generated.h"

UINTERFACE(Blueprintable)
class LEARN_API UMyInterface:public UInterface
{
	GENERATED_UINTERFACE_BODY()
};


class IMyInterface
{
	GENERATED_IINTERFACE_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Func_ImplementableEvent() const;

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void Func_NativeEvent() const;


};