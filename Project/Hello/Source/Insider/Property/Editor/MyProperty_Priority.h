// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProperty_Priority.generated.h"

UCLASS(BlueprintType)
class INSIDER_API UMyProperty_Priority :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AfterTest)
	int32 MyInt = 123;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AfterTest)
	FString MyString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AfterTest, meta = (DisplayAfter = "MyInt"))
	int32 MyInt_After = 123;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AfterTest2, meta = (DisplayAfter = "MyInt"))
	int32 MyInt_After2 = 123;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PriorityTest, meta = (DisplayPriority = 3))
	int32 MyInt_P3 = 123;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PriorityTest, meta = (DisplayPriority = 1))
	int32 MyInt_P1 = 123;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PriorityTest, meta = (DisplayPriority = 2))
	int32 MyInt_P2 = 123;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PriorityTest, meta = (DisplayPriority = 4,DisplayAfter="MyInt_P1"))
	int32 MyInt_P4 = 123;

};

