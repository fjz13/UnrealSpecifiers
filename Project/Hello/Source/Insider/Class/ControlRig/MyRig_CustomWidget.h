// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Units/RigUnit.h"
#include "Common/CommonTypes.h"
#include "MyRig_CustomWidget.generated.h"


USTRUCT(meta = (DisplayName = "MyRigCustomWidget"))
struct INSIDER_API FRigUnit_MyRigCustomWidget : public FRigUnit
{
	GENERATED_BODY()

	RIGVM_METHOD()
		virtual void Execute() override;
public:
	UPROPERTY(meta = (Input))
	FString MyString;

	UPROPERTY(meta = (Input, CustomWidget = "BoneName"))
	FString MyString_Custom;

	UPROPERTY(meta = (Output))
	float MyFloat_Output = 123.f;
};