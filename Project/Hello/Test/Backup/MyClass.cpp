// Fill out your copyright notice in the Description page of Project Settings.

#include "MyClass.h"
#include "Insider/Log.h"
#include "UObject/NameTypes.h"

UMyClass::UMyClass()
{
	myObject = CreateDefaultSubobject<UMyObject>("mySubObject123");
	myArray.Add(1);
	myArray.Add(2);
	myArray.Add(3);

}

//
//UMyClass::UMyClass(const FObjectInitializer& ObjectInitializer/*= FObjectInitializer::Get()*/)
//	:Super(ObjectInitializer)
//{
//	//my custom 
//}


int32 UMyClass::Func(float param1)
{
	return (int32)param1+1;
}

void UMyClass::VoidFunc()
{

}

void UMyClass::PostInitProperties()
{
	UObject::PostInitProperties();
}

void UMyClass::PostCDOContruct()
{
	UObject::PostCDOContruct();

}

void UMyClass::PostLoad()
{
	UObject::PostLoad();

}

void UMyClass::NativeFunc_Implementation()
{

}


//void UMyClass::NetFunc_Implementation()
//{
//
//}
//

//void UMyClass2::NetFunc()
//{
//
//}
