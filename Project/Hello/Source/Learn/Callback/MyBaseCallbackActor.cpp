// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBaseCallbackActor.h"
#include "LearnTypes.h"

AMyBaseCallbackActor::AMyBaseCallbackActor()
{
	mCppObject = new LearnDelegateClass();
}

AMyBaseCallbackActor::~AMyBaseCallbackActor()
{
	delete mCppObject;
}

void AMyBaseCallbackActor::Func_One_Param_UFUNCTION(int32 val)
{
	FString str = FString::Printf(L"%s:%d", L"UFunction", val);
	GEngine->AddOnScreenDebugMessage(-1, LearnTypes::ScreenMessageDuration, FColor::Red, str);
}

void AMyBaseCallbackActor::Func_One_Param(int32 val)
{
	FString str = FString::Printf(L"%s:%d", L"UObject", val);
	GEngine->AddOnScreenDebugMessage(-1, LearnTypes::ScreenMessageDuration, FColor::Red, str);
}


void AMyBaseCallbackActor::Func_One_Param_Static(int val)
{
	FString str = FString::Printf(L"%s:%d", L"Static", val);
	GEngine->AddOnScreenDebugMessage(-1, LearnTypes::ScreenMessageDuration, FColor::Red, str);
}


void AMyBaseCallbackActor::Func_One_Param_Delegate(int val)
{
	FString str = FString::Printf(L"%s:%d", L"Delegate", val);
	GEngine->AddOnScreenDebugMessage(-1, LearnTypes::ScreenMessageDuration, FColor::Red, str);
}


void AMyBaseCallbackActor::Func_One_Param_Static2(int val, int val2)
{
	FString str = FString::Printf(L"%s:%d %d", L"Static_WithPayload", val,val2);
	GEngine->AddOnScreenDebugMessage(-1, LearnTypes::ScreenMessageDuration, FColor::Red, str);
}
