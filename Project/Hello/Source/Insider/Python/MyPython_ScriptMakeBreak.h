// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyPython_ScriptMakeBreak.generated.h"


USTRUCT(BlueprintType, meta = (ScriptDefaultMake, ScriptDefaultBreak,HasNativeMake = "/Script/Insider.MyPython_MakeBreak_Test.MyNativeMake", HasNativeBreak = "/Script/Insider.MyPython_MakeBreak_Test.MyNativeBreak"))
struct INSIDER_API FMyPythonMBStructNative
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MyInt = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString MyString;
};

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyPython_MakeBreak_Test :public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, meta = ())
	static FMyPythonMBStructNative MyNativeMake(int32 InInt) { return FMyPythonMBStructNative{ InInt,TEXT("Hello") }; }

	UFUNCTION(BlueprintPure, meta = ())
	static void MyNativeBreak(const FMyPythonMBStructNative& InStruct, int& outInt) { outInt = InStruct.MyInt + 123;  }
};

