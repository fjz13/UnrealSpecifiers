// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Engine/EngineTypes.h"

#include "BehaviorTree/BTDecorator.h"
#include "MyBT_HiddenNode.generated.h"

UCLASS(MinimalAPI,meta = ())
class UMyBT_NotHiddenNode : public UBTDecorator
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(Category = Node, EditAnywhere)
	float MyFloat;
};

UCLASS(MinimalAPI,meta = (HiddenNode))
class UMyBT_HiddenNode : public UBTDecorator
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(Category = Node, EditAnywhere)
	float MyFloat;
};
