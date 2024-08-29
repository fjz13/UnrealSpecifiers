// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProperty_Text.h"


FText UMyProperty_Text::MyValidateMyString(const FString& Value)
{
	if (Value.Len() <= 5 && Value.Contains("A"))
	{
		return FText();
	}
	return INVTEXT("This is invalid string");
}

void UMyProperty_Text::RunTest()
{
	UMyProperty_Text* obj=this;
}
