// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AttributeSet.h"
#include "MyMonster.generated.h"

UCLASS(Blueprintable, BlueprintType)
class AMyMonster : public AActor
{
	GENERATED_BODY()

	AMyMonster();
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GAS, meta = ())
		class UAbilitySystemComponent* AbilitySystem;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GAS")
	class UMyAttributeSet* AttributeSet;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GAS")
	class UMyAttributeSet_Hide* AttributeSet_Hide;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GAS")
	FGameplayAttribute MyAttribute;
};

