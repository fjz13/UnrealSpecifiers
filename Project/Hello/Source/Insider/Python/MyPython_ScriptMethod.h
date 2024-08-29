// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "MyPython_ScriptMethod.generated.h"


UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyPython_ScriptMethod :public UObject
{
	GENERATED_BODY()
public:
};

USTRUCT(BlueprintType)
struct INSIDER_API FMyPythonStruct_ScriptMethod
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	mutable FString MyString;

};


UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyPython_ScriptMethod_Test :public UObject
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, meta = (ScriptMethod))
	static void MyFuncOnObject(UMyPython_ScriptMethod* obj, FString val);

	UFUNCTION(BlueprintCallable, meta = (ScriptMethod = "MySuperFuncOnObject;MyOtherFuncOnObject"))
	static void MyFuncOnObject2(UMyPython_ScriptMethod* obj, FString val);

public:
	UFUNCTION(BlueprintCallable, meta = (ScriptMethod))
	static void SetStringOnStruct(const FMyPythonStruct_ScriptMethod& myStruct, FString val);

	UFUNCTION(BlueprintCallable, meta = (ScriptMethod, ScriptMethodMutable))
	static void SetStringOnStructMutable(const FMyPythonStruct_ScriptMethod& myStruct, FString val);

	UFUNCTION(BlueprintCallable, meta = (ScriptMethod, ScriptMethodMutable))
	static void SetStringOnStructViaRef(UPARAM(ref) FMyPythonStruct_ScriptMethod& myStruct, FString val);

public:
	UFUNCTION(BlueprintCallable, meta = (ScriptMethod))
	static FMyPythonStruct_ScriptMethod AppendStringOnStruct(const FMyPythonStruct_ScriptMethod& myStruct, FString val);

	UFUNCTION(BlueprintCallable, meta = (ScriptMethod, ScriptMethodSelfReturn))
	static FMyPythonStruct_ScriptMethod AppendStringOnStructReturn(const FMyPythonStruct_ScriptMethod& myStruct, FString val);

	UFUNCTION(BlueprintCallable, meta = (ScriptMethod, ScriptMethodMutable))
	static FMyPythonStruct_ScriptMethod AppendStringOnStructViaRef(UPARAM(ref) FMyPythonStruct_ScriptMethod& myStruct, FString val);

	/*UFUNCTION(BlueprintCallable, meta = (ScriptMethod, ScriptMethodMutable,ScriptMethodSelfReturn))
	static FMyPythonStruct_ScriptMethod AppendStringOnStructViaRefReturn(UPARAM(ref) FMyPythonStruct_ScriptMethod& myStruct, FString val);*/

	UFUNCTION(BlueprintCallable, meta = (ScriptMethod, ScriptOperator = "+;+="))
	static FMyPythonStruct_ScriptMethod AppendStringOperator(const FMyPythonStruct_ScriptMethod& InStruct, FString val)
	{
		FMyPythonStruct_ScriptMethod Result = InStruct;
		Result.MyString += val;
		return Result;
	}
};

