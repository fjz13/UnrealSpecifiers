// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyClass_BlueprintType.generated.h"

/*
(BlueprintType = true, IncludePath = Class/MyClass_BlueprintType.h, ModuleRelativePath = Class/MyClass_BlueprintType.h)
 */
UCLASS(BlueprintType)
class INSIDER_API UMyClass_BlueprintType :public UObject
{
	GENERATED_BODY()
};

/*
(IncludePath = Class/MyClass_BlueprintType.h, ModuleRelativePath = Class/MyClass_BlueprintType.h)
*/
UCLASS()
class INSIDER_API UMyClass_BlueprintType_Child :public UMyClass_BlueprintType
{
	GENERATED_BODY()
};


/*
(IncludePath = Class/MyClass_BlueprintType.h, ModuleRelativePath = Class/MyClass_BlueprintType.h, NotBlueprintType = true)
*/
UCLASS(NotBlueprintType)
class INSIDER_API UMyClass_NotBlueprintType :public UObject
{
	GENERATED_BODY()
};

/*
(BlueprintType = true, IncludePath = Class/MyClass_BlueprintType.h, ModuleRelativePath = Class/MyClass_BlueprintType.h)
*/
UCLASS(BlueprintType)
class INSIDER_API UMyClass_NotBlueprintType_To_BlueprintType:public UMyClass_NotBlueprintType
{
	GENERATED_BODY()
};


/*
(IncludePath = Class/MyClass_BlueprintType.h, ModuleRelativePath = Class/MyClass_BlueprintType.h, NotBlueprintType = true)
*/
UCLASS(NotBlueprintType)
class INSIDER_API UMyClass_BlueprintType_To_NotBlueprintType:public UMyClass_BlueprintType
{
	GENERATED_BODY()
};
