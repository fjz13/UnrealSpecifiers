// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "MyClass_Intrinsic.generated.h"


//UCLASS(Intrinsic)
//class INSIDER_API UMyClass_Intrinsic :public UObject	//syntax error: missing ';' before '<class-head>'
//{
//	GENERATED_BODY()
//
//};


/*
[MyClass_Intrinsic	Class->Struct->Field->Object	/Script/Insider.MyClass_Intrinsic]
	ObjectFlags:	RF_Public | RF_Standalone | RF_Transient
	Outer:	Package /Script/Insider
	ClassFlags:	CLASS_MatchedSerializers | CLASS_Native | CLASS_TokenStreamAssembled | CLASS_Intrinsic
	Size:	48
	{
public: void ExecuteUbergraph(int32 EntryPoint);
	};
*/
class INSIDER_API UMyClass_Intrinsic :public UObject
{
	DECLARE_CLASS_INTRINSIC(UMyClass_Intrinsic, UObject, CLASS_MatchedSerializers, TEXT("/Script/Insider"))
};


class INSIDER_API UMyClass_NoUCLASS :public UObject
{
	
};


