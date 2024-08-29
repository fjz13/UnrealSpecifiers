// Fill out your copyright notice in the Description page of Project Settings.

#include "MyFunction_Variadic.h"

FString UMyFunction_Variadic::PrintVariadicFields(const TArray<FString>& Inputs, const TArray<FString>& Outputs)
{
	check(0);
	return TEXT("");
}


DEFINE_FUNCTION(UMyFunction_Variadic::execPrintVariadicFields)
{
	FString str;

	P_GET_TARRAY_REF(FString, Inputs);
	P_GET_TARRAY_REF(FString, Outputs);

	for (const FString& PythonInput : Inputs)
	{
		Stack.MostRecentPropertyAddress = nullptr;
		Stack.MostRecentProperty = nullptr;
		Stack.StepCompiledIn<FProperty>(nullptr);
		check(Stack.MostRecentProperty && Stack.MostRecentPropertyAddress);

		FProperty* p = CastField<FProperty>(Stack.MostRecentProperty);

		FString propertyValueString;
		const void* propertyValuePtr = p->ContainerPtrToValuePtr<const void*>(Stack.MostRecentPropertyContainer);

		p->ExportTextItem_Direct(propertyValueString, propertyValuePtr, nullptr, nullptr, PPF_None);

		str += FString::Printf(TEXT("%s:%s\n"), *p->GetFName().ToString(), *propertyValueString);

	}
	P_FINISH;

	*(FString*)RESULT_PARAM = str;
}