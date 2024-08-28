// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LearnCharacter.generated.h"

UCLASS(Blueprintable)
class LEARN_API ALearnCharacter :public ACharacter
{
	GENERATED_BODY()
public:
	ALearnCharacter();

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void OnMoveRight(float val);
	void OnFire();
};
