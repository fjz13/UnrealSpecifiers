// Fill out your copyright notice in the Description page of Project Settings.

#include "MyFunction_Exec.h"

void AMyFunction_Exec::MyExec()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "MyExec");
}

bool AMyFunction_Exec::MyEnumAsExec_MultipleOut(FString Name, EMyExecPins InPins, EMyExecAnimalPins& OutAnimal, TEnumAsByte<EMyExecPins2::Type>& OutPins, FString& Result)
{
	if (InPins == EMyExecPins::First)
	{
		Result += TEXT("Input:First");
	}
	if (InPins == EMyExecPins::Second)
	{
		Result += TEXT("Input:Second");
	}
	if (InPins == EMyExecPins::Third)
	{
		Result += TEXT("Input:Third");
	}

	if (Name.Contains(TEXT("Cat")))
	{
		OutAnimal = EMyExecAnimalPins::Cat;
		Result += TEXT("Output:Cat");
	}
	if (Name.Contains(TEXT("Dog")))
	{
		OutAnimal = EMyExecAnimalPins::Dog;
		Result += TEXT("Output:Dog");
	}
	if (Name.Contains(TEXT("Found")))
	{
		OutPins = EMyExecPins2::Found;
		Result += TEXT("Output:Found");
	}
	if (Name.Contains(TEXT("NotFound")))
	{
		OutPins = EMyExecPins2::NotFound;
		Result += TEXT("Output:NotFound");
	}

	return true;
}
