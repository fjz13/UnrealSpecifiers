// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProperty_EditCondition.generated.h"


UCLASS(BlueprintType)
class INSIDER_API UMyProperty_EditCondition_Test :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)
	bool MyBool;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)
	int32 MyInt = 123;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property, meta = (EditCondition = "MyBool"))
	int32 MyInt_EditCondition = 123;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property, meta = (EditCondition = "!MyBool"))
	int32 MyInt_EditCondition_Not = 123;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property, meta = (EditConditionHides, EditCondition = "MyBool"))
	int32 MyInt_EditCondition_Hides = 123;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PropertyExpression)
	int32 MyFirstInt = 123;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PropertyExpression)
	int32 MySecondInt = 123;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PropertyExpression, meta = (EditCondition = "(MyFirstInt+MySecondInt)==500"))
	int32 MyInt_EditConditionExpression = 123;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PropertyExpression, meta = (EditCondition = "!((MyFirstInt+MySecondInt)==500)"))
	int32 MyInt_EditConditionExpression_Not = 123;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PropertyExpression, meta = (EditConditionHides, EditCondition = "(MyFirstInt+MySecondInt)==500"))
	int32 MyInt_EditConditionExpression_Hides = 123;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InlineEditConditionToggle, meta = (InlineEditConditionToggle))
	bool MyBool_Inline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InlineEditConditionToggle, meta = (EditCondition = "MyBool_Inline"))
	int32 MyInt_EditCondition_UseInline = 123;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InlineEditConditionToggle, meta = (HideEditConditionToggle,EditCondition = "MyBool_Inline"))
	int32 MyInt_EditCondition_UseInline_Hide = 123;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InlineEditConditionToggle)
	int32 MyThirdInt_Inline = 123;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InlineEditConditionToggle, meta = (EditCondition = "MyThirdInt_Inline>200"))
	int32 MyInt_EditConditionExpression_UseInline = 123;
};