// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyTokenStreamStructRef.generated.h"

class UMyTokenStreamClass2;

USTRUCT(Blueprintable, Blueprintable)
struct LEARN_API FMyTokenStreamStructRef
{
	GENERATED_BODY()
public:
	FMyTokenStreamStructRef();

	void AddReferencedObjects(FReferenceCollector& Collector);

public:
	UMyTokenStreamClass2* mOtherObject = nullptr;
};
