// Fill out your copyright notice in the Description page of Project Settings.

#include "MyFunction_ForceAsFunction.h"

void AMyFunction_ForceAsFunction::MyNativeEvent_Default_Implementation(const FString& name)
{

}

void AMyFunction_ForceAsFunction::MyNativeEvent_ForceAsFunction_Implementation(const FString& name)
{

}

bool AMyFunction_ForceAsFunction::MyNativeEvent_Output_Implementation(const FString& name,int32& OutValue)
{
	return true;
}

bool AMyFunction_ForceAsFunction::MyNativeEvent_Output_ForceAsFunction_Implementation(const FString& name, int32& OutValue)
{
	return true;
}
