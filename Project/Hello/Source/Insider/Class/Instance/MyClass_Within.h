// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyClass_Within.generated.h"


//auto* outer = NewObject<UMyClass_ModuleAPI>();
//auto* a = NewObject<UMyClass_Within>(outer);

UCLASS(Within= MyClass_Within_Outer)
class INSIDER_API UMyClass_Within :public UObject
{
	GENERATED_BODY()
};


UCLASS()
class INSIDER_API UMyClass_Within_Outer :public UObject
{
	GENERATED_BODY()
public:
};
