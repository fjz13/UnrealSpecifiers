// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyFunction_SelfPin.generated.h"

UCLASS()
class INSIDER_API UMyFunctionLibrary_SelfPinTest :public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	static FString PrintProperty_Default(UObject* myOwner,FName propertyName);

	UFUNCTION(BlueprintPure,meta=(DefaultToSelf="myOwner"))
	static FString PrintProperty_HasDefaultToSelf(UObject* myOwner,FName propertyName);

	UFUNCTION(BlueprintPure,meta=(DefaultToSelf="myOwner",hidePin="myOwner"))
	static FString PrintProperty_HasDefaultToSelf_ButHide(UObject* myOwner,FName propertyName);
public:
	UFUNCTION(BlueprintPure,meta=(DefaultToSelf="myOwner",HideSelfPin="true"))
	static FString PrintProperty_HasDefaultToSelf_AndHideSelf(UObject* myOwner,FName propertyName);	//HideSelfPin not worked

	UFUNCTION(BlueprintPure,meta=(DefaultToSelf="myOwner",InternalUseParam="myOwner"))
	static FString PrintProperty_HasDefaultToSelf_ButInternal(UObject* myOwner,FName propertyName);
};


UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyFunction_HideSelfTest :public AActor
{
public:
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void MyFunc_Default(int value){}

	UFUNCTION(BlueprintCallable,meta=(HideSelfPin="true"))
	void MyFunc_HideSelfPin(int value){}
};
