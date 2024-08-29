// Fill out your copyright notice in the Description page of Project Settings.

#include "LearnGameMode.h"
#include "UObject/ConstructorHelpers.h"

ALearnGameMode::ALearnGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> pawnClass(L"/Script/Learn.LearnPawn");
	if (pawnClass.Class!=nullptr)
	{
		DefaultPawnClass = pawnClass.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> playerControllerClass(L"/Script/Learn.LearnPlayerController");
	if (playerControllerClass.Class!=nullptr)
	{
		PlayerControllerClass = playerControllerClass.Class;
	}
	
	//// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	//if (PlayerPawnBPClass.Class != NULL)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Class;
	//}
}
