// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LearnDelegateClass.h"
#include "MyBaseCallbackActor.generated.h"


UCLASS(Blueprintable, Abstract)
class LEARN_API AMyBaseCallbackActor :public AActor
{
	GENERATED_BODY()
public:
	AMyBaseCallbackActor();
	~AMyBaseCallbackActor();
protected:
	static void Func_One_Param_Static(int val);
	static void Func_One_Param_Delegate(int val);

	static void Func_One_Param_Static2(int val, int val2);
	void Func_One_Param(int32 val);
	UFUNCTION()
		void Func_One_Param_UFUNCTION(int32 val);
protected:
	LearnDelegateClass* mCppObject;
	TSharedPtr<LearnDelegateClass> mCppObjectPtr;
};
