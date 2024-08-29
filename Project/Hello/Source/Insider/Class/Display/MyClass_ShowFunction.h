// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyClass_ShowFunction.generated.h"


UCLASS(Blueprintable, HideFunctions = (MyFunc1, MyEvent2),hideCategories= EventCategory2)
class INSIDER_API AMyClass_HideFunctions :public AActor
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
		void MyFunc1() {}

	UFUNCTION(BlueprintCallable)
		void MyFunc2() {}

	UFUNCTION(BlueprintCallable, Category = "FuncCategory1")
		void MyFuncInCategory1() {}

	UFUNCTION(BlueprintCallable, Category = "FuncCategory2")
		void MyFuncInCategory2() {}

public:
UFUNCTION(BlueprintImplementableEvent)
		void MyEvent1();

	UFUNCTION(BlueprintImplementableEvent)
		void MyEvent2();

	UFUNCTION(BlueprintImplementableEvent, Category = "EventCategory1")
		void MyEventInCategory1();

	UFUNCTION(BlueprintImplementableEvent, Category = "EventCategory2")
		void MyEventInCategory2();
};


UCLASS(Blueprintable, ShowFunctions = (MyEvent2),showCategories= EventCategory2)
class INSIDER_API AMyClass_ShowFunctions :public AMyClass_HideFunctions
{
	GENERATED_BODY()
public:

};
