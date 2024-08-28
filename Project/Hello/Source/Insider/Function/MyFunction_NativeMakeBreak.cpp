// Fill out your copyright notice in the Description page of Project Settings.

#include "MyFunction_NativeMakeBreak.h"



FMyStruct_ForNative UMyFunction_NativeMakeBreak::MakeMyStructNative(FString ValueString)
{
	return FMyStruct_ForNative{};
}

FMyStruct_ForNative UMyFunction_NativeMakeBreak::MakeMyStructNative_NoMeta(FString ValueString)
{
	return FMyStruct_ForNative{};
}

void UMyFunction_NativeMakeBreak::BreakMyStructNative(const FMyStruct_ForNative& InValue, int32& X, int32& Y, int32& Z)
{

}

void UMyFunction_NativeMakeBreak::MakeMyStructNative_Wrong(FString ValueString)
{

}
