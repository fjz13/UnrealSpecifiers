// Fill out your copyright notice in the Description page of Project Settings.

#include "MyFunction_PlayerController.h"
#include "Utility/Log.h"
#include "Utility/InsiderSubsystem.h"

void AMyFunction_PlayerController::MyFunc_RunOnClient_Implementation()
{
	UInsiderSubsystem::Get().PrintFuncStatus(this, TEXT("MyFunc_RunOnClient_Implementation"));
}

void AMyFunction_PlayerController::MyFunc_RunOnServer_Implementation()
{
	UInsiderSubsystem::Get().PrintFuncStatus(this, TEXT("MyFunc_RunOnServer_Implementation"));
}

void AMyFunction_PlayerController::MyFunc2_RunOnClient_Implementation()
{
	UInsiderSubsystem::Get().PrintFuncStatus(this, TEXT("MyFunc2_RunOnClient_Implementation"));
}

bool AMyFunction_PlayerController::MyFunc2_RunOnClient_Validate()
{
	UInsiderSubsystem::Get().PrintFuncStatus(this, TEXT("MyFunc2_RunOnClient_Validate"));

	return true;
}

void AMyFunction_PlayerController::MyFunc2_RunOnServer_Implementation()
{
	UInsiderSubsystem::Get().PrintFuncStatus(this, TEXT("MyFunc2_RunOnServer_Implementation"));
}

bool AMyFunction_PlayerController::MyFunc2_RunOnServer_Validate()
{
	UInsiderSubsystem::Get().PrintFuncStatus(this, TEXT("MyFunc2_RunOnServer_Validate"));
	return true;
}

void AMyFunction_PlayerController::MyFunc_ServiceResponse()
{
	UInsiderSubsystem::Get().PrintFuncStatus(this, TEXT("MyFunc_ServiceResponse"));
}



