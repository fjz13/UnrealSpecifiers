// Fill out your copyright notice in the Description page of Project Settings.

#include "MyFunctionActor.h"
#include "LearnTypes.h"

AMyFunctionActor::AMyFunctionActor()
{

}

// Called when the game starts or when spawned
void AMyFunctionActor::BeginPlay()
{
	Super::BeginPlay();

	Func_Callable();
	Func_ImplementableEvent();
	Func_NativeEvent();
}

// Called every frame
void AMyFunctionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyFunctionActor::Func_Callable()
{
	GEngine->AddOnScreenDebugMessage(-1, LearnTypes::ScreenMessageDuration, FColor::Red, "Cpp_Func_Callable");
}


void AMyFunctionActor::Func_CallInEditor()
{
	GEngine->AddOnScreenDebugMessage(-1, LearnTypes::ScreenMessageDuration, FColor::Red, "Cpp_Func_CallInEditor");
}

void AMyFunctionActor::Func_NativeEvent_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, LearnTypes::ScreenMessageDuration, FColor::Red, "Cpp_Func_NativeEvent_Implementation");
}
