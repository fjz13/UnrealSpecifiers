// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyObjectWithSubobject.generated.h"

UCLASS(Blueprintable, Blueprintable)
class LEARN_API UMyObjectWithSubobject :public UObject
{
	GENERATED_BODY()

		UMyObjectWithSubobject();

public:public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		class UMyObject* MySubObject;
};
