// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InstancedStruct.h"
#include "MyProperty_Struct.generated.h"


USTRUCT(BlueprintType)
struct INSIDER_API FMyStruct_InitTest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MyProperty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (IgnoreForMemberInitializationTest))
	int32 MyProperty_IgnoreTest;
};


UCLASS(BlueprintType)
class INSIDER_API UMyProperty_Struct :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InstancedStruct")
	FInstancedStruct MyStruct;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InstancedStruct", meta = (BaseStruct = "/Script/Insider.MyCommonStruct"))
	FInstancedStruct MyStruct_BaseStruct;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InstancedStruct", meta = (ExcludeBaseStruct, BaseStruct = "/Script/Insider.MyCommonStruct"))
	FInstancedStruct MyStruct_ExcludeBaseStruct;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InstancedStruct", meta = (StructTypeConst))
	FInstancedStruct MyStruct_Const;
};

