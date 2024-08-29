// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyFunction_ForceAsFunction.generated.h"

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyFunction_ForceAsFunction :public AActor
{
public:
	GENERATED_BODY()
public:
//FUNC_Native | FUNC_Event | FUNC_Public | FUNC_BlueprintCallable | FUNC_BlueprintEvent 
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void MyNativeEvent_Default(const FString& name);

	//FUNC_Event | FUNC_Public | FUNC_BlueprintCallable | FUNC_BlueprintEvent 
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void MyImplementableEvent_Default(const FString& name);

public:
	//(ForceAsFunction = , ModuleRelativePath = Function/MyFunction_ForceAsFunction.h)
	//FUNC_Native | FUNC_Event | FUNC_Public | FUNC_BlueprintCallable | FUNC_BlueprintEvent 
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta = (ForceAsFunction))
	void MyNativeEvent_ForceAsFunction(const FString& name);

	////(ForceAsFunction = , ModuleRelativePath = Function/MyFunction_ForceAsFunction.h)
	//FUNC_Event | FUNC_Public | FUNC_BlueprintCallable | FUNC_BlueprintEvent 
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, meta = (ForceAsFunction))
	void MyImplementableEvent_ForceAsFunction(const FString& name);

public:
	//FUNC_Native | FUNC_Event | FUNC_Public | FUNC_HasOutParms | FUNC_BlueprintCallable | FUNC_BlueprintEvent 
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool MyNativeEvent_Output(const FString& name, int32& OutValue);

	//FUNC_Event | FUNC_Public | FUNC_HasOutParms | FUNC_BlueprintCallable | FUNC_BlueprintEvent 
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	bool MyImplementableEvent_Output(const FString& name, int32& OutValue);

	//(ForceAsFunction = , ModuleRelativePath = Function/MyFunction_ForceAsFunction.h)
	//FUNC_Native | FUNC_Event | FUNC_Public | FUNC_HasOutParms | FUNC_BlueprintCallable | FUNC_BlueprintEvent 
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta = (ForceAsFunction))
	bool MyNativeEvent_Output_ForceAsFunction(const FString& name, int32& OutValue);

	//(ForceAsFunction = , ModuleRelativePath = Function/MyFunction_ForceAsFunction.h)
	//FUNC_Event | FUNC_Public | FUNC_HasOutParms | FUNC_BlueprintCallable | FUNC_BlueprintEvent 
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, meta = (ForceAsFunction))
	bool MyImplementableEvent_Output_ForceAsFunction(const FString& name, int32& OutValue);
};


