// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyFunction_Default.generated.h"

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyFunction_Default :public AActor
{
public:
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void RunTest();
	UFUNCTION(BlueprintCallable)
	void MyFunc_Default() {}

	//(Category = MyCategory, ModuleRelativePath = Function/MyFunction_Default.h)
	UFUNCTION(BlueprintCallable, Category = MyCategory)
	void MyFunc_WithCategory() {}

	//		(CallInEditor = true, ModuleRelativePath = Function/MyFunction_Default.h)
	UFUNCTION(CallInEditor)
	void MyFunc_CallInEditor() {}

	//			FunctionFlags:	FUNC_Final | FUNC_Native | FUNC_Public | FUNC_BlueprintCallable 
	UFUNCTION(BlueprintCallable)
	void MyFunc_BlueprintCallable() {}

	//			FunctionFlags:	FUNC_Final | FUNC_Native | FUNC_Public | FUNC_BlueprintCallable | FUNC_BlueprintPure | FUNC_Const 
	UFUNCTION(BlueprintPure)
	int32 GetMyInt()const { return MyInt; }

	//FunctionFlags:	FUNC_Event | FUNC_Public | FUNC_BlueprintCallable | FUNC_BlueprintEvent 
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void MyFunc_ImplementableEvent();

	//FunctionFlags:	FUNC_Native | FUNC_Event | FUNC_Public | FUNC_BlueprintCallable | FUNC_BlueprintEvent 
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void MyFunc_NativeEvent();


	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void MyEventAsFunction_ImplementableEvent();

	//			FunctionFlags:	FUNC_Native | FUNC_Event | FUNC_Public | FUNC_BlueprintEvent 
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void MyEventAsFunction_NativeEvent();
private:
	int32 MyInt;

};
