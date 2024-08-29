// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyClass_CustomThunkTemplates.generated.h"


UCLASS(meta = (CustomThunkTemplates = "FNoesisFunctionLibraryCustomThunkTemplates"))	//not used
class INSIDER_API UMyClass_CustomThunkTemplates :public UObject
{
	GENERATED_BODY()
public:
};

struct FNoesisFunctionLibraryCustomThunkTemplates
{
private:
	static void ExecutionMessage(const TCHAR* Message, ELogVerbosity::Type Verbosity)
	{
		FFrame::KismetExecutionMessage(Message, Verbosity);
	}

	template<typename T>
	static int32 LastIndexForLog(const TArray<T>& TargetArray)
	{
		const int32 ArraySize = TargetArray.Num();
		return (ArraySize > 0) ? (ArraySize - 1) : 0;
	}

};