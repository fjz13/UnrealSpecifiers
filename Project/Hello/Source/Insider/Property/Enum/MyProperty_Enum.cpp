// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProperty_Enum.h"

TArray<FString> UMyProperty_Enum::MyGetRestrictedEnumValues() const
{
	return TArray<FString>{"Second","Third"};
}
