// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProperty_Network.h"
#include "Net/UnrealNetwork.h"


void AMyProperty_Network::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMyProperty_Network, MyInt_Replicated);
	DOREPLIFETIME(AMyProperty_Network, MyInt_ReplicatedUsing);
	DOREPLIFETIME(AMyProperty_Network, MyStruct_Replicated);
}

void AMyProperty_Network::OnRep_MyInt(int32 oldValue)
{
	//todo sth after valued changed
}