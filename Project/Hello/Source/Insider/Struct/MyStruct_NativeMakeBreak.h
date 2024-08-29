// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyStruct_NativeMakeBreak.generated.h"

//(BlueprintType = true, HasNativeBreak = /Script/Insider.MyHasNativeStructHelperLibrary.BreakMyHasNativeStruct, HasNativeMake = /Script/Insider.MyHasNativeStructHelperLibrary.MakeMyHasNativeStruct, ModuleRelativePath = Struct/MyStruct_NativeMakeBreak.h)
USTRUCT(BlueprintType, meta = (HasNativeBreak = "/Script/Insider.MyHasNativeStructHelperLibrary.BreakMyHasNativeStruct", HasNativeMake = "/Script/Insider.MyHasNativeStructHelperLibrary.MakeMyHasNativeStruct"))
struct INSIDER_API FMyStruct_HasNative
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MyReadWrite=0.f;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float MyReadOnly=0.f;
	UPROPERTY(EditAnywhere)
	float MyNotBlueprint=0.f;
};

USTRUCT(BlueprintType)
struct INSIDER_API FMyStruct_HasDefaultMakeBreak
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MyReadWrite=0.f;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float MyReadOnly=0.f;
	UPROPERTY(EditAnywhere)
	float MyNotBlueprint=0.f;
};


UCLASS()
class UMyHasNativeStructHelperLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	static void BreakMyHasNativeStruct(const FMyStruct_HasNative& myStruct, float& outValue);

	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	static FMyStruct_HasNative MakeMyHasNativeStruct(float value);
};