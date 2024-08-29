// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/CommonTypes.h"
#include "MyActor_EditWidget.generated.h"

UCLASS(BlueprintType)
class INSIDER_API AMyActor_EditWidget :public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EditWidget")
	FVector MyVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EditWidget", meta = (MakeEditWidget))
	FVector MyVector_MakeEditWidget;
public:
	UFUNCTION()
	FString ValidateMyVector();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EditWidget", meta = (MakeEditWidget, ValidateWidgetUsing = "ValidateMyVector"))
	FVector MyVector_MakeEditWidget_Validate;
};

