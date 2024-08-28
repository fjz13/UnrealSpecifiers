// Fill out your copyright notice in the Description page of Project Settings.

#include "LearnCharacter.h"
#include "Log/LogTypes.h"
#include "LearnTypes.h"

ALearnCharacter::ALearnCharacter()
{

}

void ALearnCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis("MoveRight", this, &ALearnCharacter::OnMoveRight);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ALearnCharacter::OnFire);

}

void ALearnCharacter::OnMoveRight(float val)
{
	if (!FMath::IsNearlyZero(val))
	{
		FString str = FString::Printf(L"MoveRight:%f", val);
		GEngine->AddOnScreenDebugMessage(-1, LearnTypes::ScreenMessageDuration, FColor::Red, str);
	}
}

void ALearnCharacter::OnFire()
{
	FString str = FString::Printf(L"Fire");
	GEngine->AddOnScreenDebugMessage(-1, LearnTypes::ScreenMessageDuration, FColor::Red, str);
}