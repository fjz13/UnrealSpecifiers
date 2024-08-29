// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProperty_Get.h"

void UMyProperty_Get::RunTest()
{
	float Value1=MyFloat;

	FProperty* prop=GetClass()->FindPropertyByName(TEXT("MyFloat"));
	float Value2=0.f;

	prop->GetValue_InContainer(this,&Value2);
}
