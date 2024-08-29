// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MyScoreSubsystem.generated.h"

UCLASS()
class LEARN_API UMyScoreSubsystem : public UGameInstanceSubsystem,public FTickableGameObject
{
	GENERATED_BODY()
public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override { return true; }
	virtual void Initialize(FSubsystemCollectionBase& Collection)override;
	virtual void Deinitialize()override;
public:
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override { return !IsTemplate(); }
	virtual TStatId GetStatId() const override;
public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FScoreChanged, float, NewScore);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable)
		FScoreChanged OnScoreChanged;

	UFUNCTION(BlueprintCallable)
		void AddScore(float delta);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Score;
};

