// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

UCLASS(BlueprintType)
class INSIDER_API UMyAnimInstance :public UAnimInstance
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "Animation|Insider", meta = (BlueprintInternalUseOnly = "true", AnimGetter, BlueprintThreadSafe))
	float MyGetAnimationLength_AnimGetter(int32 AssetPlayerIndex);

	UFUNCTION(BlueprintPure, Category = "Animation|Insider", meta = (BlueprintThreadSafe))
	float MyGetAnimationLength(int32 AssetPlayerIndex);
public:
	UFUNCTION(BlueprintPure, Category = "Animation|Insider", meta = (BlueprintInternalUseOnly = "true", AnimGetter, BlueprintThreadSafe))
	float MyGetStateWeight_AnimGetter(int32 MachineIndex, int32 StateIndex);

	UFUNCTION(BlueprintPure, Category = "Animation|Insider", meta = (BlueprintThreadSafe))
	float MyGetStateWeight(int32 MachineIndex, int32 StateIndex);
public:
	UFUNCTION(BlueprintPure, Category = "Animation|Insider", meta = (BlueprintInternalUseOnly = "true", AnimGetter, BlueprintThreadSafe))
	float MyGetTransitionTimeElapsed_AnimGetter(int32 MachineIndex, int32 TransitionIndex);

	UFUNCTION(BlueprintPure, Category = "Animation|Insider", meta = (BlueprintThreadSafe))
	float MyGetTransitionTimeElapsed(int32 MachineIndex, int32 TransitionIndex);

public:
	UFUNCTION(BlueprintPure, Category = "Animation|Insider", meta = (BlueprintInternalUseOnly = "true", AnimGetter, GetterContext = "Transition", BlueprintThreadSafe))
	float MyGetStateWeight_AnimGetter_OnlyTransition(int32 MachineIndex, int32 StateIndex);

	UFUNCTION(BlueprintPure, Category = "Animation|Insider", meta = (BlueprintInternalUseOnly = "true", AnimGetter, GetterContext = "CustomBlend", BlueprintThreadSafe))
	float MyGetTransitionTimeElapsed_AnimGetter_OnlyCustomBlend(int32 MachineIndex, int32 TransitionIndex);
};

