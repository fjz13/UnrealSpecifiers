// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPropertyActor.h"
#include "Class/MyBlueprintableClass.h"

AMyPropertyActor::AMyPropertyActor()
{
	Float_Array_FixedSize.Add(1.f);
	Float_Array_FixedSize.Add(2.f);
	Float_Array_FixedSize.Add(3.f);

	Object_HasClear = CreateDefaultSubobject<UMyBlueprintableClass>("Object_HasClear");
	Object_NoClear = CreateDefaultSubobject<UMyBlueprintableClass>("Object_NoClear");

	Float_WithGetter = 1.f;

	String_FString = TEXT("MyString");
	String_FName = TEXT("MyString");
	String_FText = FText::FromString(TEXT("MyString"));

}