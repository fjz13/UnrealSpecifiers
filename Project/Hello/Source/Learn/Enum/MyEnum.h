// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyEnum.generated.h"

UENUM(Blueprintable)
enum class MyEnum :uint8
{
	First,
	Second
};



UENUM(Blueprintable, meta = (EnumDisplayNameFn = "GetMyCustomEnumDisplayName"))
enum class MyCustomEnum :uint8
{
	Dance 	UMETA(DisplayName = "MyDance"),
	Rain 	UMETA(DisplayName = "MyRain"),
	Song	UMETA(DisplayName = "MySong")
};

extern FText GetMyCustomEnumDisplayName(int32 val);

enum class MyCppEnum :uint8
{
	First,
	Second
};

