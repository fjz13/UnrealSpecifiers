// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProperty_RowType.generated.h"




UCLASS(BlueprintType)
class INSIDER_API UMyProperty_RowType :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RowTypeTest")
	FDataTableRowHandle MyRowHandle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RowTypeTest", meta = (RowType = "/Script/Insider.MyCommonRow"))
	FDataTableRowHandle MyRowHandle_RowType;
};

