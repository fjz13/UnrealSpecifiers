// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "MyPluginWorldSubsystem.generated.h"

UCLASS()
class MYPLUGIN_API UMyPluginWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	UMyPluginWorldSubsystem();
public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override { return true; }
	virtual void Initialize(FSubsystemCollectionBase& Collection)override;
	virtual void Deinitialize()override;

};

