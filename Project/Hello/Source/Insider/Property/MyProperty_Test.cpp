// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProperty_Test.h"
#include "Class/MyClass_Default.h"

UMyProperty_Test::UMyProperty_Test(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/)
	:Super(ObjectInitializer)
{
	MyObject_Normal = CreateDefaultSubobject<UMyClass_Default>("MyObject_Normal");
	MyObject_NoClear = CreateDefaultSubobject<UMyClass_Default>("MyObject_NoClear");

	/*Float_WithGetter = 1.f;

	String_FString = TEXT("MyString");
	String_FName = TEXT("MyString");
	String_FText = FText::FromString(TEXT("MyString"));*/

}
