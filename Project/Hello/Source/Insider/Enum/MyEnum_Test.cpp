// Fill out your copyright notice in the Description page of Project Settings.

#include "MyEnum_Test.h"


FText GetMyEnumCustomDisplayName(int32 val)
{
	EMyEnum_CustomDisplay enumValue = (EMyEnum_CustomDisplay)val;
	switch (enumValue)
	{
	case EMyEnum_CustomDisplay::First:
		return FText::FromString(TEXT("My_First"));
	case EMyEnum_CustomDisplay::Second:
		return FText::FromString(TEXT("My_Second"));
	case EMyEnum_CustomDisplay::Third:
		return FText::FromString(TEXT("My_Third"));
	default:
		return FText::FromString(TEXT("Invalid MyEnum"));
	}
}
