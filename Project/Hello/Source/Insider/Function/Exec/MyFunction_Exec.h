// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyFunction_Exec.generated.h"

UENUM(BlueprintType)
enum class EMyExecPins : uint8
{
	First,
	Second,
	Third,
};


UENUM(BlueprintType)
namespace EMyExecPins2
{
	enum Type : int
	{
		Found,
		NotFound,
	};
}


UENUM(BlueprintType)
enum class EMyExecAnimalPins : uint8
{
	Cat,
	Dog,
};




UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyFunction_Exec :public APawn
{
public:
	GENERATED_BODY()
public:
	//FunctionFlags:	FUNC_Final | FUNC_Exec | FUNC_Native | FUNC_Public 
	UFUNCTION(exec)
	void MyExec();

public:
	UFUNCTION(BlueprintCallable, meta = (ExpandEnumAsExecs = "Pins"))
	static int32 MyEnumAsExec_Output(FString Name, EMyExecPins& Pins) { return 0; }

	UFUNCTION(BlueprintCallable, meta = (ExpandEnumAsExecs = "Pins"))
	static int32 MyEnumAsExec_Input(FString Name, TEnumAsByte<EMyExecPins2::Type> Pins) { return 0; }

	UFUNCTION(BlueprintCallable, meta = (ExpandEnumAsExecs = "ReturnValue"))
	static EMyExecPins MyEnumAsExec_Return(FString Name) { return EMyExecPins::First; }
public:
	UFUNCTION(BlueprintCallable, meta = (ExpandEnumAsExecs = "Pins"))
	static int32 MyBoolAsExec_Output(FString Name, bool& Pins) { return 0; }

	UFUNCTION(BlueprintCallable, meta = (ExpandEnumAsExecs = "Pins"))
	static int32 MyBoolAsExec_Input(FString Name, bool Pins) { return 0; }

	UFUNCTION(BlueprintCallable, meta = (ExpandEnumAsExecs = "ReturnValue"))
	static bool MyBoolAsExec_Return(FString Name) { return false; }
public:
	UFUNCTION(BlueprintCallable, meta = (ExpandEnumAsExecs = "InPins,OutAnimal|OutPins|ReturnValue"))
	static bool MyEnumAsExec_MultipleOut(FString Name, EMyExecPins InPins, EMyExecAnimalPins& OutAnimal, TEnumAsByte<EMyExecPins2::Type>& OutPins, FString& Result);
};


//ExpandBoolAsExecs == ExpandEnumAsExecs
/*
	UFUNCTION(BlueprintCallable, meta = (ExpandBoolAsExecs = "Pins"))
	static int32 MyEnumAsExec_Output(FString Name, EMyExecPins& Pins) { return 0; }

	UFUNCTION(BlueprintCallable, meta = (ExpandBoolAsExecs = "Pins"))
	static int32 MyEnumAsExec_Input(FString Name, TEnumAsByte<EMyExecPins2::Type> Pins) { return 0; }

	UFUNCTION(BlueprintCallable, meta = (ExpandBoolAsExecs = "ReturnValue"))
	static EMyExecPins MyEnumAsExec_Return(FString Name) { return EMyExecPins::First; }
public:
	UFUNCTION(BlueprintCallable, meta = (ExpandBoolAsExecs = "Pins"))
	static int32 MyBoolAsExec_Output(FString Name, bool& Pins) { return 0; }

	UFUNCTION(BlueprintCallable, meta = (ExpandBoolAsExecs = "Pins"))
	static int32 MyBoolAsExec_Input(FString Name, bool Pins) { return 0; }

	UFUNCTION(BlueprintCallable, meta = (ExpandBoolAsExecs = "ReturnValue"))
	static bool MyBoolAsExec_Return(FString Name) { return false; }
public:
	UFUNCTION(BlueprintCallable, meta = (ExpandBoolAsExecs = "InPins,OutAnimal|OutPins|ReturnValue"))
	static bool MyEnumAsExec_MultipleOut(FString Name, EMyExecPins InPins, EMyExecAnimalPins& OutAnimal, TEnumAsByte<EMyExecPins2::Type>& OutPins, FString& Result);
*/