// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "MyPluginEngineSubsystem.generated.h"

UCLASS()
class MYPLUGIN_API UMyPluginEngineSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()
public:
public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override { return true; }
	virtual void Initialize(FSubsystemCollectionBase& Collection)override;
	virtual void Deinitialize()override;

public:
	UFUNCTION(BlueprintCallable)
	void AddScore(float delta);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Score;

};

