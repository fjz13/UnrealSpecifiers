// Fill out your copyright notice in the Description page of Project Settings.

#include "MyFunction_Network.h"
#include "Utility/Log.h"
#include "Utility/InsiderSubsystem.h"

void AMyFunction_Network::BeginPlay()
{
	Super::BeginPlay();
}

void AMyFunction_Network::MyFunc_Default()
{
	UInsiderSubsystem::Get().PrintFuncStatus(this, TEXT("MyFunc_Default"));
}

void AMyFunction_Network::MyFunc_BlueprintAuthorityOnly()
{
	UInsiderSubsystem::Get().PrintFuncStatus(this, TEXT("MyFunc_BlueprintAuthorityOnly"));
}

void AMyFunction_Network::MyFunc_BlueprintCosmetic()
{
	UInsiderSubsystem::Get().PrintFuncStatus(this, TEXT("MyFunc_BlueprintCosmetic"));
}

void AMyFunction_Network::MyFunc_NetMulticast_Implementation()
{
	UInsiderSubsystem::Get().PrintFuncStatus(this, TEXT("MyFunc_NetMulticast_Implementation"));
}

void AMyFunction_Network::MyFunc2_NetMulticast_Implementation()
{
	UInsiderSubsystem::Get().PrintFuncStatus(this, TEXT("MyFunc2_NetMulticast_Implementation"));
}

bool AMyFunction_Network::MyFunc2_NetMulticast_Validate()
{
	UInsiderSubsystem::Get().PrintFuncStatus(this, TEXT("MyFunc2_NetMulticast_Validate"));
	return true;
}

