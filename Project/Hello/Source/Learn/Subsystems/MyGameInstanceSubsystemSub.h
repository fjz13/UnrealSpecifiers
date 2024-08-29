// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "UMyGameInstanceSubsystemBase.h"
#include "MyGameInstanceSubsystemSub.generated.h"



UCLASS(abstract)
class LEARN_API UMyGameInstanceSubsystemSub1 : public UMyGameInstanceSubsystemBase
{
	GENERATED_BODY()
public:
public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override { return true; }
	virtual void Initialize(FSubsystemCollectionBase& Collection)override {}
	virtual void Deinitialize()override {}
};

UCLASS(abstract)
class LEARN_API UMyGameInstanceSubsystemSub2 : public UMyGameInstanceSubsystemBase
{
	GENERATED_BODY()
public:
public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override { return true; }
	virtual void Initialize(FSubsystemCollectionBase& Collection)override {}
	virtual void Deinitialize()override {}
};


UCLASS(abstract)
class LEARN_API UMyGameInstanceSubsystemSub3 : public UMyGameInstanceSubsystemBase
{
	GENERATED_BODY()
public:
public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override { return true; }
	virtual void Initialize(FSubsystemCollectionBase& Collection)override {}
	virtual void Deinitialize()override {}
};

