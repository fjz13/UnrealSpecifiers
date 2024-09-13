// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MyComponent_SkipUCSModifiedProperties.generated.h"


UCLASS(Blueprintable, BlueprintType,meta=(BlueprintSpawnableComponent))
class INSIDER_API UMyComponent_SkipUCSModifiedProperties :public UActorComponent
{
public:
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString MyString_Default = TEXT("Hello");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (SkipUCSModifiedProperties))
	FString MyString_Skip = TEXT("Hello");
};
