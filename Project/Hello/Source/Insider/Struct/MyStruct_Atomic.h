// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyStruct_Atomic.generated.h"


USTRUCT(BlueprintType)
struct INSIDER_API FMyStruct_InnerItem
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 A = 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 B = 2;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 C = 3;

	bool operator==(const FMyStruct_InnerItem& other)const
	{
		return A == other.A;
	}

};



USTRUCT(BlueprintType)
struct INSIDER_API FMyStruct_NoAtomic
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FMyStruct_InnerItem Item;
};


USTRUCT(Atomic, BlueprintType)
struct INSIDER_API FMyStruct_Atomic
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FMyStruct_InnerItem Item;
};


template<>
struct TStructOpsTypeTraits<FMyStruct_InnerItem> : public TStructOpsTypeTraitsBase2<FMyStruct_InnerItem>
{
	enum
	{
		WithIdenticalViaEquality = true,
	};
};
