// Fill out your copyright notice in the Description page of Project Settings.

#include "MyFunction_AutoCast.h"

FAutoCastTo UMyFunction_AutoCast::Conv_MyTestAutoCast(const FAutoCastFrom& InValue)
{
	return FAutoCastTo{ InValue.X + InValue.Y };
}
