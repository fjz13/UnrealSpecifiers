// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyInterface_Test.generated.h"

//(BlueprintType = true, IsBlueprintBase = true, ModuleRelativePath = Interface/MyInterface_Test.h)
//ClassFlags:	CLASS_Abstract | CLASS_MatchedSerializers | CLASS_Native | CLASS_Interface | CLASS_MinimalAPI | CLASS_TokenStreamAssembled | CLASS_Intrinsic | CLASS_Constructed 
UINTERFACE(Blueprintable,MinimalAPI)
class UMyInterface_Blueprintable:public UInterface
{
	GENERATED_UINTERFACE_BODY()
};


class INSIDER_API IMyInterface_Blueprintable
{
	GENERATED_IINTERFACE_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Func_ImplementableEvent() const;

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void Func_NativeEvent() const;
};


//(IsBlueprintBase = false, ModuleRelativePath = Interface/MyInterface_Test.h)
//ClassFlags:	CLASS_Abstract | CLASS_MatchedSerializers | CLASS_Native | CLASS_Interface | CLASS_MinimalAPI | CLASS_TokenStreamAssembled | CLASS_Intrinsic | CLASS_Constructed 
UINTERFACE(NotBlueprintable,MinimalAPI)
class UMyInterface_NotBlueprintable:public UInterface
{
	GENERATED_UINTERFACE_BODY()
};


class INSIDER_API IMyInterface_NotBlueprintable
{
	GENERATED_IINTERFACE_BODY()
public:
};

//(CannotImplementInterfaceInBlueprint = , ModuleRelativePath = Interface/MyInterface_Test.h)
UINTERFACE(meta=(CannotImplementInterfaceInBlueprint))
class UMyInterface_OnlyCpp:public UInterface
{
	GENERATED_UINTERFACE_BODY()
};


class INSIDER_API IMyInterface_OnlyCpp
{
	GENERATED_IINTERFACE_BODY()
public:
	//Interfaces that are not implementable in blueprints cannot have Blueprint Event members.
	/*UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Func_ImplementableEvent() const;*/

	//Interfaces that are not implementable in blueprints cannot have Blueprint Event members.
	//	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	//void Func_NativeEvent() const;

	UFUNCTION(BlueprintCallable)
	virtual void Func() const{}
};