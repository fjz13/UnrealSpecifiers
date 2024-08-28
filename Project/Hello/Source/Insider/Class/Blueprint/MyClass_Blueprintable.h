// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyClass_Blueprintable.generated.h"

/*
(BlueprintType = true, IncludePath = Class/MyClass_Blueprintable.h, IsBlueprintBase = true, ModuleRelativePath = Class/MyClass_Blueprintable.h)
*/
UCLASS(Blueprintable)
class INSIDER_API UMyClass_Blueprintable :public UObject
{
	GENERATED_BODY()
};

/*
(IncludePath = Class/MyClass_Blueprintable.h, IsBlueprintBase = false, ModuleRelativePath = Class/MyClass_Blueprintable.h)
*/
UCLASS(NotBlueprintable)
class INSIDER_API UMyClass_NotBlueprintable :public UObject
{
	GENERATED_BODY()
};

/*
(BlueprintType = true, IncludePath = Class/MyClass_Blueprintable.h, IsBlueprintBase = true, ModuleRelativePath = Class/MyClass_Blueprintable.h)
*/
UCLASS(Blueprintable)
class INSIDER_API UMyClass_NotBlueprintable_To_Blueprintable :public UMyClass_NotBlueprintable
{
	GENERATED_BODY()
};

/*
(IncludePath = Class/MyClass_Blueprintable.h, IsBlueprintBase = false, ModuleRelativePath = Class/MyClass_Blueprintable.h)
*/
UCLASS(NotBlueprintable)
class INSIDER_API UMyClass_Blueprintable_To_NotBlueprintable :public UMyClass_Blueprintable
{
	GENERATED_BODY()
};
