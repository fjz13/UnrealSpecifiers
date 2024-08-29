// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyEditorActor.generated.h"

UCLASS(Blueprintable)
class LEARN_API AMyEditorActor :public AActor
{
	GENERATED_BODY()
public:
	AMyEditorActor();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Width;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Height;

	UPROPERTY(VisibleAnywhere)
		float Area;
public:
#if WITH_EDITORONLY_DATA
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)override;
#endif
};
