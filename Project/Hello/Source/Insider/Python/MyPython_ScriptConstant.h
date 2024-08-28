// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyPython_ScriptConstant.generated.h"


USTRUCT(BlueprintType)
struct INSIDER_API FMyPythonConstantStruct
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString MyString;
};

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyPython_ConstantOwner :public UObject
{
	GENERATED_BODY()
public:
};


UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyPython_Constant_Test :public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, meta = (ScriptConstant))
	static int32 MyIntConst() { return 123; }

	UFUNCTION(BlueprintPure, meta = (ScriptConstant = "MyOtherIntConst"))
	static int32 MyIntConst2() { return 456; }


	UFUNCTION(BlueprintPure, meta = (ScriptConstant))
	static FMyPythonConstantStruct MyStructConst() { return FMyPythonConstantStruct{ TEXT("Hello") }; }

	UFUNCTION(BlueprintPure, meta = (ScriptConstant = "MyOtherStructConst"))
	static FMyPythonConstantStruct MyStructConst2() { return FMyPythonConstantStruct{ TEXT("World") }; }

public:
	UFUNCTION(BlueprintPure, meta = (ScriptConstant="FirstString", ScriptConstantHost = "/Script/Insider.MyPython_ConstantOwner"))
	static FString MyStringConst() { return TEXT("First"); }
};

