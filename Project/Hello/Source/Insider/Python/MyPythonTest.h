// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "MyPythonTest.generated.h"

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyPythonTestLibary2 :public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
};

UCLASS(Blueprintable, BlueprintType, meta = (ScriptName = "MyPythonLib"))
class INSIDER_API UMyPythonTestLibary :public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	static void MyScriptFunc_None();

	//unreal.MyPythonLib.my_script_func_default()
	UFUNCTION(BlueprintCallable, meta = ())
	static void MyScriptFuncDefault();

	//unreal.MyPythonLib.my_script_func()
	UFUNCTION(BlueprintCallable, meta = (ScriptName = "MyScriptFunc"))
	static void MyScriptFunc_ScriptName();

public:
	UFUNCTION(BlueprintCallable, meta = (ScriptNoExport))
	static void MyScriptFunc_NoExport();

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MyFloat = 123.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ScriptNoExport))
	float MyFloat_NoExport = 123.f;
public:
};

