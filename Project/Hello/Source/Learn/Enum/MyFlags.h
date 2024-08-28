// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyFlags.generated.h"

UENUM(Blueprintable,Meta = (Bitflags))
enum class MyFlags:uint8
{
	First,
	Second,
	Third,
};
