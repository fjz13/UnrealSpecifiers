// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovieSceneDynamicBinding.h"
#include "MySequencerBindingResolverLibrary.generated.h"

UCLASS(meta=(SequencerBindingResolverLibrary), MinimalAPI)
class UMySequencerBindingResolverLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/** Resolve the bound object to the player's pawn */
	UFUNCTION(BlueprintPure, Category="Sequencer|Insider", meta=(WorldContext="WorldContextObject"))
	static FMovieSceneDynamicBindingResolveResult ResolveToMyActor(UObject* WorldContextObject, FString ActorTag);
};

