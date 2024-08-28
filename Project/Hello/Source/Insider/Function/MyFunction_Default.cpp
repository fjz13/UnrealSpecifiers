// Fill out your copyright notice in the Description page of Project Settings.

#include "MyFunction_Default.h"

void AMyFunction_Default::RunTest()
{
	MyFunc_NativeEvent();
}

void AMyFunction_Default::MyFunc_NativeEvent_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "MyFunc_NativeEvent_Implementation");
}

void AMyFunction_Default::MyEventAsFunction_NativeEvent_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "MyEventAsFunction_NativeEvent_Implementation");
}
