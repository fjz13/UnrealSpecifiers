// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyClass_Place.generated.h"


//ClassFlags:	CLASS_Config | CLASS_MatchedSerializers | CLASS_Native | CLASS_NotPlaceable | CLASS_RequiredAPI | CLASS_TokenStreamAssembled | CLASS_HasInstancedReference | CLASS_Intrinsic | CLASS_Constructed 
UCLASS(Blueprintable,BlueprintType, NotPlaceable)
class INSIDER_API AMyActor_NotPlaceable :public AActor
{
	GENERATED_BODY()
};

//ClassFlags:	CLASS_Config | CLASS_MatchedSerializers | CLASS_Native | CLASS_NotPlaceable | CLASS_RequiredAPI | CLASS_TokenStreamAssembled | CLASS_HasInstancedReference | CLASS_Intrinsic | CLASS_Constructed 
UCLASS(Blueprintable, BlueprintType)	
class INSIDER_API AMyActor_NotPlaceableChild :public AMyActor_NotPlaceable
{
	GENERATED_BODY()
};

//ClassFlags:	CLASS_Config | CLASS_MatchedSerializers | CLASS_Native | CLASS_ReplicationDataIsSetUp | CLASS_RequiredAPI | CLASS_TokenStreamAssembled | CLASS_HasInstancedReference | CLASS_Intrinsic | CLASS_Constructed 
UCLASS(Blueprintable, BlueprintType,placeable)	//placeable是默认的，可以不写
class INSIDER_API AMyActor_Placeable :public AActor
{
	GENERATED_BODY()
};

