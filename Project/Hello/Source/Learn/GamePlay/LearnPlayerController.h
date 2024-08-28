// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LearnPlayerController.generated.h"

UCLASS(Blueprintable)
class LEARN_API ALearnPlayerController :public APlayerController
{
	GENERATED_BODY()
public:
	ALearnPlayerController();
protected:
	virtual void SetupInputComponent()override;
protected:
	void OnMoveForward(float val);
	void OnJump();

};
