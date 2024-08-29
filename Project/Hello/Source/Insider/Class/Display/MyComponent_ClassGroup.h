// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyComponent_ClassGroup.generated.h"


//ClassGroup 必须是BlueprintSpawnableComponent才有效
/*
(BlueprintSpawnableComponent = , BlueprintType = true, ClassGroupNames = MyGroup|MySubGroup, IncludePath = Class/MyComponent_ClassGroup.h, IsBlueprintBase = true, ModuleRelativePath = Class/MyComponent_ClassGroup.h)
*/
UCLASS(Blueprintable,ClassGroup="MyGroup|MySubGroup", meta = (BlueprintSpawnableComponent))
class INSIDER_API UMyComponent_ClassGroup:public UActorComponent
{
	GENERATED_BODY()
public:
};


UCLASS(Blueprintable,BlueprintType,ClassGroup = "MyGroup|MySubGroup")
class UMyClass_ClassGroup :public UObject
{
	GENERATED_BODY()
public:
};


UCLASS(Blueprintable,BlueprintType,ClassGroup = "MyGroup|MySubGroup")
class AMyActor_ClassGroup :public AActor
{
	GENERATED_BODY()
public:
};
