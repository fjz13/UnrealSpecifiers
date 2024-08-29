// Fill out your copyright notice in the Description page of Project Settings.

#include "MyStruct_NativeMakeBreak.h"

void UMyHasNativeStructHelperLibrary::BreakMyHasNativeStruct(const FMyStruct_HasNative& myStruct, float& outValue)
{
	outValue = myStruct.MyReadWrite + myStruct.MyReadOnly + myStruct.MyNotBlueprint;
}

FMyStruct_HasNative UMyHasNativeStructHelperLibrary::MakeMyHasNativeStruct(float value)
{
	FMyStruct_HasNative result;
	result.MyReadWrite = value;
	result.MyReadOnly = value;
	result.MyNotBlueprint = value;
	return result;
}
