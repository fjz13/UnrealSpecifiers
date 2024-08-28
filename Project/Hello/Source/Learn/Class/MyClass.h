// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyClass.generated.h"

/*
[class 91ae54cca80 MyClass	Class->Struct->Field->Object	/Script/Learn.MyClass]
(BlueprintType = true, IncludePath = Class/MyClass.h, IsBlueprintBase = true, ModuleRelativePath = Class/MyClass.h)
	ObjectFlags:	RF_Public | RF_Standalone | RF_Transient 
	Outer:	Package /Script/Learn
	ClassHierarchy:	MyClass:Object
	ClassFlags:	CLASS_MatchedSerializers | CLASS_Native | CLASS_RequiredAPI | CLASS_TokenStreamAssembled | CLASS_Intrinsic | CLASS_Constructed 
	Size:	56
	Within:	Object
	ClassConfigName:	Engine
{
	(Category = MyClass, ModuleRelativePath = Class/MyClass.h)
	48-[4] int32 MyProperty;
		PropertyFlags:	CPF_Edit | CPF_BlueprintVisible | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic 
		ObjectFlags:	RF_Public | RF_MarkAsNative | RF_Transient 
		Outer:	Class /Script/Learn.MyClass
		Path:	IntProperty /Script/Learn.MyClass:MyProperty
	[func 91ae5543e80 MyFunc	Function->Struct->Field->Object	/Script/Learn.MyClass:MyFunc]
	(ModuleRelativePath = Class/MyClass.h)
		ObjectFlags:	RF_Public | RF_Transient 
		Outer:	Class /Script/Learn.MyClass
		FunctionFlags:	FUNC_Final | FUNC_Native | FUNC_Public | FUNC_BlueprintCallable 
		NumParms:	2
		ParmsSize:	20
		ReturnValueOffset:	16
		RPCId:	0
		RPCResponseId:	0
		public int32 MyFunc(FString inString)final;
	{
		0-[16] FString inString;
			PropertyFlags:	CPF_Parm | CPF_ZeroConstructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic 
			ObjectFlags:	RF_Public | RF_MarkAsNative | RF_Transient 
			Outer:	Function /Script/Learn.MyClass:MyFunc
			Path:	StrProperty /Script/Learn.MyClass:MyFunc:inString
		16-[4] int32 ReturnValue;
			PropertyFlags:	CPF_Parm | CPF_OutParm | CPF_ZeroConstructor | CPF_ReturnParm | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic 
			ObjectFlags:	RF_Public | RF_MarkAsNative | RF_Transient 
			Outer:	Function /Script/Learn.MyClass:MyFunc
			Path:	IntProperty /Script/Learn.MyClass:MyFunc:ReturnValue
	};
};
*/

UCLASS(Blueprintable, BlueprintType)
class LEARN_API UMyClass :public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	int32 MyFunc(FString inString) { return 0; }
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MyProperty = 123;
};
