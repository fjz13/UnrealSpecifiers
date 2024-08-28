// Fill out your copyright notice in the Description page of Project Settings.

#include "MyFunction_Custom.h"

int32 UMyFunction_Custom::MyFunc_CustomDivide(int32 A, int32 B /*= 1*/)
{
	check(0);
	return 1;
}

DEFINE_FUNCTION(UMyFunction_Custom::execMyFunc_CustomDivide)
{
	P_GET_PROPERTY(FIntProperty, A);
	P_GET_PROPERTY(FIntProperty, B);

	P_FINISH;

	if (B == 0)
	{
		FFrame::KismetExecutionMessage(*FString::Printf(TEXT("Modulo by zero detected: %d %% 0\n%s"), A, *Stack.GetStackTrace()), ELogVerbosity::Warning);
		*(int32*)RESULT_PARAM = 0;
		return;
	}

	*(int32*)RESULT_PARAM = A/B;
}

DEFINE_FUNCTION(UMyFunction_Custom::execPrintStructFields)
{
	FString result;
	Stack.MostRecentPropertyAddress = nullptr;
	Stack.StepCompiledIn<FStructProperty>(nullptr);

	void* StructData = Stack.MostRecentPropertyAddress;
	FStructProperty* StructProperty = CastField<FStructProperty>(Stack.MostRecentProperty);
	UScriptStruct* ScriptStruct = StructProperty->Struct;
	P_FINISH;
	P_NATIVE_BEGIN;

	result = Generic_PrintStructFields(ScriptStruct, StructData);

	P_NATIVE_END;
	*(FString*)RESULT_PARAM = result;
}



FString UMyFunction_Custom::Generic_PrintStructFields(const UScriptStruct* ScriptStruct, const void* StructData)
{
	FString str;
	for (TFieldIterator<FProperty> i(ScriptStruct); i; ++i)
	{
		FString propertyValueString;
		const void* propertyValuePtr = i->ContainerPtrToValuePtr<const void*>(StructData);
		i->ExportTextItem_Direct(propertyValueString, propertyValuePtr, nullptr, (UObject*)ScriptStruct, PPF_None);

		str += FString::Printf(TEXT("%s:%s\n"), *i->GetFName().ToString(), *propertyValueString);
	}

	return str;
}
