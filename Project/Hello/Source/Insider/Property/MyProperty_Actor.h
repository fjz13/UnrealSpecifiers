// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/CommonTypes.h"
#include "MyProperty_Actor.generated.h"

UCLASS(BlueprintType)
class INSIDER_API AMyProperty_Actor :public AActor
{
	GENERATED_BODY()
public:
	//not work
	//UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MustBeLevelActorTest")
	//AActor* MyActor_NotMustBeLevelActor;
	//UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MustBeLevelActorTest",meta=(MustBeLevelActor=true))
	//AActor* MyActor_MustBeLevelActor;
};

