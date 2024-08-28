// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UMyGameInstanceSubsystem.generated.h"

UCLASS()
class LEARN_API UMyGameInstanceSubsystem : public UGameInstanceSubsystem
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

	UFUNCTION(BlueprintCallable)
	static void MyTest(UGameInstance* gi);
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Score;

};

