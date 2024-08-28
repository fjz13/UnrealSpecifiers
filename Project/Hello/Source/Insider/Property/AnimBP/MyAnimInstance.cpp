// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAnimInstance.h"
#include "Animation/AnimInstanceProxy.h"

float UMyAnimInstance::MyGetAnimationLength_AnimGetter(int32 AssetPlayerIndex)
{
	return GetInstanceAssetPlayerLength(AssetPlayerIndex);
}

float UMyAnimInstance::MyGetAnimationLength(int32 AssetPlayerIndex)
{
	return 0;
}

float UMyAnimInstance::MyGetStateWeight_AnimGetter(int32 MachineIndex, int32 StateIndex)
{
	return 0.f;
}

float UMyAnimInstance::MyGetStateWeight(int32 MachineIndex, int32 StateIndex)
{
	return 0.f;
}

float UMyAnimInstance::MyGetTransitionTimeElapsed_AnimGetter(int32 MachineIndex, int32 TransitionIndex)
{
	return 0.f;
}

float UMyAnimInstance::MyGetTransitionTimeElapsed(int32 MachineIndex, int32 TransitionIndex)
{
	return 0.f;
}

float UMyAnimInstance::MyGetStateWeight_AnimGetter_OnlyTransition(int32 MachineIndex, int32 StateIndex)
{
	return 0.f;
}

float UMyAnimInstance::MyGetTransitionTimeElapsed_AnimGetter_OnlyCustomBlend(int32 MachineIndex, int32 TransitionIndex)
{
	return 0.f;
}
