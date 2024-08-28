// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyClass_DebugTreeLeaf.generated.h"


UCLASS(BlueprintType, meta = (DebugTreeLeaf))
class INSIDER_API UMyClass_DebugTreeLeaf :public UObject
{
	GENERATED_BODY()
	UMyClass_DebugTreeLeaf();
public:
	UPROPERTY(BlueprintReadWrite)
	TArray<int32> IntArray;
	UPROPERTY(BlueprintReadWrite)
	TMap<int32, FString> IntStringMap;
	UPROPERTY(BlueprintReadWrite)
	TSet<int32> IntSet;
};

