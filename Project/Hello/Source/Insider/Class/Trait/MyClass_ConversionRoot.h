// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyClass_ConversionRoot.generated.h"

//(BlueprintType = true, IncludePath = Class/Trait/MyClass_ConversionRoot.h, IsBlueprintBase = true, IsConversionRoot = true, ModuleRelativePath = Class/Trait/MyClass_ConversionRoot.h)
UCLASS(Blueprintable,BlueprintType, ConversionRoot)
class INSIDER_API AMyActor_ConversionRoot :public AActor
{
	GENERATED_BODY()
};
