// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyFunction_Network.generated.h"

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyFunction_Network :public AActor
{
public:
	GENERATED_BODY()
	virtual void BeginPlay()override;
public:
	//FunctionFlags:	FUNC_Final | FUNC_Native | FUNC_Public | FUNC_BlueprintCallable 
	UFUNCTION(BlueprintCallable)
	void MyFunc_Default();

	//FunctionFlags:	FUNC_Final | FUNC_BlueprintAuthorityOnly | FUNC_Native | FUNC_Public | FUNC_BlueprintCallable 
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
	void MyFunc_BlueprintAuthorityOnly();

	//FunctionFlags:	FUNC_Final | FUNC_BlueprintCosmetic | FUNC_Native | FUNC_Public | FUNC_BlueprintCallable 
	UFUNCTION(BlueprintCallable, BlueprintCosmetic)
	void MyFunc_BlueprintCosmetic();

	//FunctionFlags:	FUNC_Net | FUNC_NetReliable | FUNC_Native | FUNC_Event | FUNC_NetMulticast | FUNC_Public | FUNC_BlueprintCallable 
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void MyFunc_NetMulticast();

	//FunctionFlags:	FUNC_Net | FUNC_NetReliable | FUNC_Native | FUNC_Event | FUNC_NetMulticast | FUNC_Public | FUNC_BlueprintCallable | FUNC_NetValidate 
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable, WithValidation)
	void MyFunc2_NetMulticast();


};
