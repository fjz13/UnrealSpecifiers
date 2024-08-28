// Fill out your copyright notice in the Description page of Project Settings.

#include "LearnPlayerController.h"
#include "Log/LogTypes.h"
#include "LearnTypes.h"

ALearnPlayerController::ALearnPlayerController()
{
	
}

void ALearnPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (InputComponent)
	{
		InputComponent->BindAxis("MoveForward", this, &ALearnPlayerController::OnMoveForward);
		InputComponent->BindAction("Jump", IE_Pressed, this, &ALearnPlayerController::OnJump);
	}

}

void ALearnPlayerController::OnMoveForward(float val)
{
	if (!FMath::IsNearlyZero(val))
	{
		FString str = FString::Printf(L"MoveForward:%f", val);
		GEngine->AddOnScreenDebugMessage(-1, LearnTypes::ScreenMessageDuration, FColor::Red, str);
	}
}

void ALearnPlayerController::OnJump()
{
	FString str = FString::Printf(L"Jump");
	GEngine->AddOnScreenDebugMessage(-1, LearnTypes::ScreenMessageDuration, FColor::Red, str);
}