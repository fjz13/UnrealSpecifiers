// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyClass_ThreadSafe.generated.h"


//(BlueprintThreadSafe = , IncludePath = Class/Blueprint/MyClass_ThreadSafe.h, ModuleRelativePath = Class/Blueprint/MyClass_ThreadSafe.h)
UCLASS(meta=(BlueprintThreadSafe))
class INSIDER_API UMyBlueprintFunctionLibrary_ThreadSafe : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure)
	static float MyFunc_ClassThreadSafe_Default(float value) {return value+100;}

	//(ModuleRelativePath = Class/Blueprint/MyClass_ThreadSafe.h, NotBlueprintThreadSafe = )
	UFUNCTION(BlueprintPure,meta=(NotBlueprintThreadSafe))
	static float MyFunc_ClassThreadSafe_FuncNotThreadSafe(float value) {return value+100;}
};


UCLASS(meta=(NotBlueprintThreadSafe))
class INSIDER_API UMyBlueprintFunctionLibrary_NoThreadSafe : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
UFUNCTION(BlueprintPure)
	static float MyFunc_ClassNotThreadSafe_FuncDefault(float value) {return value+100;}

	//(BlueprintThreadSafe = , ModuleRelativePath = Class/Blueprint/MyClass_ThreadSafe.h)
	UFUNCTION(BlueprintPure,meta=(BlueprintThreadSafe))
	static float MyFunc_ClassDefault_FuncThreadSafe(float value) {return value+100;}

	//(ModuleRelativePath = Class/Blueprint/MyClass_ThreadSafe.h, NotBlueprintThreadSafe = )
	UFUNCTION(BlueprintPure,meta=(NotBlueprintThreadSafe))
	static float MyFunc_ClassDefault_FuncNotThreadSafe(float value) {return value+100;}


};

UCLASS()
class INSIDER_API UMyBlueprintFunctionLibrary_Default : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure)
	static float MyFunc_ClassDefault_FuncDefault(float value) {return value+100;}
};
