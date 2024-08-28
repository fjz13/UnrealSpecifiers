// Fill out your copyright notice in the Description page of Project Settings.

#include "MyFunction_TestParam.h"

FString AMyFunction_TestParam::MyFuncTestParam_Default(int& refValue)
{
	refValue += 100;
	return FString::Printf(TEXT("%d"), refValue);
}

FString AMyFunction_TestParam::MyFuncTestParam_Ref(int& refValue)
{
	refValue += 100;
	return FString::Printf(TEXT("%d"), refValue);
}

FString AMyFunction_TestParam::MyFuncTestParam_Copy(int value)
{
	value += 100;
	return FString::Printf(TEXT("%d"), value);
}

FString AMyFunction_TestParam::MyFuncTestParam_DisplayName(int value)
{
	value += 100;
	return FString::Printf(TEXT("%d"), value);
}

FString AMyFunction_TestParam::MyFuncTestParam_ConstInt(int value)
{
	value += 100;
	return FString::Printf(TEXT("%d"), value);
}

FString AMyFunction_TestParam::MyFuncTestParam_ConstIntOut(int& value)
{
	value += 100;
	return FString::Printf(TEXT("%d"), value);
}

FString AMyFunction_TestParam::MyFuncTestParam_ConstIntRef(const int& value)
{
	return FString::Printf(TEXT("%d"), value);
}

FString AMyFunction_TestParam::MyFuncTestParam_NoConstInt(int value)
{
	value += 100;
	return FString::Printf(TEXT("%d"), value);
}

FString AMyFunction_TestParam::MyFuncTestParam_NoConstIntOut(int& value)
{
	value += 100;
	return FString::Printf(TEXT("%d"), value);
}

FString AMyFunction_TestParam::MyFuncTestParam_NoConstIntRef(const int& value)
{
	return FString::Printf(TEXT("%d"), value);
}

FString AMyFunction_TestParam::MyFuncTestParam_RequiredObject(UObject* objValue)
{
	return FString::Printf(TEXT("%x"), objValue);
}

FString AMyFunction_TestParam::MyFuncTestParam_RequiredInt(int intValue)
{
	return FString::Printf(TEXT("%d"), intValue);
}

FString AMyFunction_TestParam::MyFuncTestParam_DefaultInt2(int intValue/*=123*/, int intValue2/*=456*/)
{
	return FString::Printf(TEXT("%d"), intValue);
}

FString AMyFunction_TestParam::MyFuncTestParam_DefaultVector(FVector InLocation/*=FVector(1,2,3)*/)
{
	return TEXT("");
}

FString AMyFunction_TestParam::MyFuncTestParam_DefaultString(FString InString /*= TEXT("Hello")*/)
{
	return TEXT("");
}

FString AMyFunction_TestParam::MyFuncTestParam_DefaultInMeta(const UObject* WorldContextObject, FVector Location, float Size/*=10.f*/)
{
	return TEXT("");
}

