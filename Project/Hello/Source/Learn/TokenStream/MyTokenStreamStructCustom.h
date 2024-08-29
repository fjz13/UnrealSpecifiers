// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Class.h"
#include "MyTokenStreamStructCustom.generated.h"

class UMyTokenStreamClass2;

USTRUCT(Blueprintable, Blueprintable)
struct LEARN_API FMyTokenStreamStructCustom
{
	GENERATED_BODY()
public:
	FMyTokenStreamStructCustom();

	void AddStructReferencedObjects(class FReferenceCollector& Collector)const;

public:
	UMyTokenStreamClass2* mOtherObject = nullptr;
};

template<>
struct TStructOpsTypeTraits<FMyTokenStreamStructCustom> : public TStructOpsTypeTraitsBase2<FMyTokenStreamStructCustom>
{
	enum
	{
		WithAddStructReferencedObjects = true,
	};
};
