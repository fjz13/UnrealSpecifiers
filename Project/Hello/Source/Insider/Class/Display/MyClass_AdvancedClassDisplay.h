// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyClass_AdvancedClassDisplay.generated.h"

/*
(AdvancedClassDisplay = true, BlueprintType = true, IncludePath = Class/Display/MyClass_AdvancedClassDisplay.h, IsBlueprintBase = true, ModuleRelativePath = Class/Display/MyClass_AdvancedClassDisplay.h)
*/

UCLASS(Blueprintable,BlueprintType,AdvancedClassDisplay)
class INSIDER_API UMyClass_AdvancedClassDisplay :public UObject
{
	GENERATED_BODY()
public:
	//PropertyFlags:	CPF_Edit | CPF_BlueprintVisible | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyProperty;
	//PropertyFlags:	CPF_Edit | CPF_BlueprintVisible | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_SimpleDisplay | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic 
	UPROPERTY(EditAnywhere, BlueprintReadWrite,SimpleDisplay)
		int32 MyProperty_Simple;
};

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyClass_NoAdvancedClassDisplay :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyProperty;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay)
		int32 MyProperty_Simple;
};

