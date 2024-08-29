// Fill out your copyright notice in the Description page of Project Settings.

#include "MyFunctionLibrary.h"
#include "LearnTypes.h"
#include <Kismet/GameplayStatics.h>
#include <Interface/MyInterface.h>

int32 UMyFunctionLibrary::MyFunction_Call(int32 val)
{
	FString str = FString::Printf(L"%s:%d", L"MyFunction_Call", val);
	GEngine->AddOnScreenDebugMessage(-1, LearnTypes::ScreenMessageDuration, FColor::Red, str);
	return val + 1;


}

int32 UMyFunctionLibrary::MyFunction_Pure()
{
	return 123;
}

