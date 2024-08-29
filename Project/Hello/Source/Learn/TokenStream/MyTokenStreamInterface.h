// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyTokenStreamInterface.generated.h"

UINTERFACE(Blueprintable, Blueprintable)
class LEARN_API UMyTokenStreamInterface :public UInterface
{
	GENERATED_UINTERFACE_BODY()
};


class IMyTokenStreamInterface
{
	GENERATED_IINTERFACE_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void BPFunc() const;

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void Func_NativeEvent() const;

};