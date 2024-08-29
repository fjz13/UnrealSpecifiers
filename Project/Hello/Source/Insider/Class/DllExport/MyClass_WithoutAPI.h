// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyClass_WithoutAPI.generated.h"


/*
[MyClass_WithoutAPI	Class->Struct->Field->Object	/Script/Insider.MyClass_WithoutAPI] [IncludePath = Class/MyClass_WithoutAPI.h, ModuleRelativePath = Class/MyClass_WithoutAPI.h]
ObjectFlags:	RF_Public | RF_Standalone | RF_Transient
Outer:	Package /Script/Insider
ClassFlags:	CLASS_MatchedSerializers | CLASS_Native | CLASS_TokenStreamAssembled | CLASS_Intrinsic | CLASS_Constructed
Size:	48
{
public: void ExecuteUbergraph(int32 EntryPoint);
};
*/
UCLASS()
class UMyClass_WithoutAPI :public UObject
{
	GENERATED_BODY()
public:
};
