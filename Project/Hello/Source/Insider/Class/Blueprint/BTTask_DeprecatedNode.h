// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Engine/EngineTypes.h"

#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_DeprecatedNode.generated.h"

UCLASS(meta = (DeprecatedNode, DeprecationMessage = "This BT node is deprecated. Don't use this anymore."), MinimalAPI)
class UBTTask_MyDeprecatedNode : public UBTTaskNode
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(Category = Node, EditAnywhere)
	float MyFloat;
};
