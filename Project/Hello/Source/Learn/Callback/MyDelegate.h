// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyDelegate.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FMyDynamicSinglecastDelegate_One, int32, Value);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMyDynamicMulticastDelegate_One, int32, Value);

DECLARE_MULTICAST_DELEGATE_OneParam(FMyMulticastDelegate_One, int32);

DECLARE_DELEGATE_OneParam(FMySinglecastDeleagate_One, int32);
DECLARE_DELEGATE_RetVal_OneParam(int32, FMySinglecastDeleagate_One_Ret, int32);


DECLARE_EVENT_OneParam(UMyDelegate, FMyEvent_One, int32);


UCLASS(Blueprintable, Blueprintable)
class LEARN_API UMyDelegate :public UObject
{
	GENERATED_BODY()
public:

	UMyDelegate();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, BlueprintCallable)
		FMyDynamicMulticastDelegate_One OnMulticastDelegateAssignAndCall;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable)
		FMyDynamicMulticastDelegate_One OnMulticastDelegateAssign;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FMyDynamicMulticastDelegate_One OnMulticastDelegate;

	//'BlueprintCallable' is only allowed on a property when it is a multicast delegate
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintCallable)
	//	FMyDynamicSinglecastDelegate OnMyDelegate4;

	//'BlueprintAssignable' is only allowed on a property when it is a multicast delegate
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable)
		FMyDynamicSinglecastDelegate OnMyDelegate5;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FMyDynamicSinglecastDelegate_One OnSinglecastDelegate;
private:
	FMyEvent_One mEvent;
private:
	FMyMulticastDelegate_One mMulticastDelegate;
private:
	FMySinglecastDeleagate_One mSinglecastDelegate;


};