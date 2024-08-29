// Fill out your copyright notice in the Description page of Project Settings.

#include "MyFunction_Sealed.h"
#include "Utility/InsiderSubsystem.h"

void AMyFunction_Sealed::MyFunc_RunOnClient_SealedEvent_Implementation()
{
	UInsiderSubsystem::Get().PrintFuncStatus(this, TEXT("MyFunc_RunOnClient_SealedEvent_Implementation"));
}

void AMyFunction_Sealed::MyFunc_RunOnServer_SealedEvent_Implementation()
{
	UInsiderSubsystem::Get().PrintFuncStatus(this, TEXT("MyFunc_RunOnServer_SealedEvent_Implementation"));
}

void AMyFunction_Sealed::MyFunc_RunOnClient_Implementation()
{
	UInsiderSubsystem::Get().Get().PrintFuncStatus(this, TEXT("MyFunc_RunOnClient_Implementation"));
}

void AMyFunction_Sealed::MyFunc_RunOnServer_Implementation()
{
	UInsiderSubsystem::Get().PrintFuncStatus(this, TEXT("MyFunc_RunOnServer_Implementation"));
}


void AMyFunction_Sealed_Child::MyFunc_RunOnClient_SealedEvent()
{

}

void AMyFunction_Sealed_Child::MyFunc_RunOnServer_SealedEvent()
{

}

void AMyFunction_Sealed_Child::MyFunc_RunOnClient()
{

}

void AMyFunction_Sealed_Child::MyFunc_RunOnServer()
{

}
