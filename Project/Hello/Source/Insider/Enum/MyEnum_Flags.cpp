// Fill out your copyright notice in the Description page of Project Settings.

#include "MyEnum_Flags.h"

void UMyActor_EnumBitFlags_Test::TestFlags()
{
	int value = 3;

	FString outStr_Normal = StaticEnum<EMyEnum_Normal>()->GetValueOrBitfieldAsString(value);
	FString outStr_Flags = StaticEnum<EMyEnum_Flags>()->GetValueOrBitfieldAsString(value);
	FString outStr_BitFlags = StaticEnum<EMyEnum_BitFlags>()->GetValueOrBitfieldAsString(value);

	++value;
}
