// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyActor_ChildTick.generated.h"

//(BlueprintType = true, ChildCannotTick = , IncludePath = Class/Blueprint/MyActor_ChildTick.h, IsBlueprintBase = true, ModuleRelativePath = Class/Blueprint/MyActor_ChildTick.h)
UCLASS(Blueprintable,meta=(ChildCanTick))
class INSIDER_API AMyActor_ChildCanTick : public AActor
{
	GENERATED_BODY()
public:
	AMyActor_ChildCanTick()
	{
		PrimaryActorTick.bCanEverTick = false;
	}
};

//(BlueprintType = true, ChildCanTick = , IncludePath = Class/Blueprint/MyActor_ChildTick.h, IsBlueprintBase = true, ModuleRelativePath = Class/Blueprint/MyActor_ChildTick.h)
UCLASS(Blueprintable,meta=(ChildCanTick))
class INSIDER_API UMyActorComponent_ChildCanTick : public UActorComponent
{
	GENERATED_BODY()
public:
};

//(BlueprintType = true, ChildCannotTick = , IncludePath = Class/Blueprint/MyActor_ChildTick.h, IsBlueprintBase = true, ModuleRelativePath = Class/Blueprint/MyActor_ChildTick.h)
UCLASS(Blueprintable,meta=(ChildCannotTick))
class INSIDER_API AMyActor_ChildCannotTick : public AActor
{
	GENERATED_BODY()
public:
};

//(BlueprintType = true, ChildCannotTick = , IncludePath = Class/Blueprint/MyActor_ChildTick.h, IsBlueprintBase = true, ModuleRelativePath = Class/Blueprint/MyActor_ChildTick.h)
UCLASS(Blueprintable,meta=(ChildCannotTick))
class INSIDER_API UMyActorComponent_ChildCannotTick : public UActorComponent
{
	GENERATED_BODY()
public:
};
