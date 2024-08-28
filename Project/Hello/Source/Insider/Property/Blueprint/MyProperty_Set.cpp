// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProperty_Set.h"

void UMyProperty_Set::SetMyProperty(int32 InArg)
{
	MyProperty=InArg;
}

void UMyProperty_Set::SetMyProperty2(int32 InArg)
{
	MyProperty2 = InArg;
}

void UMyProperty_Set::RunTest()
{
	float OldValue=MyFloat;

	FProperty* prop=GetClass()->FindPropertyByName(TEXT("MyFloat"));
	const float Value2=20.f;

	prop->SetValue_InContainer(this,&Value2);

	float NewValue=MyFloat;

}
