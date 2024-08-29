// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MyPluginGameInstanceSubsystem.generated.h"

UCLASS()
class MYPLUGIN_API UMyPluginGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UMyPluginGameInstanceSubsystem();
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

