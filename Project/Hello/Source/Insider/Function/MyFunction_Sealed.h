// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyFunction_Sealed.generated.h"

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyFunction_Sealed :public APlayerController
{
public:
	GENERATED_BODY()
public:
	//UFUNCTION(SealedEvent)
	//void MyFunc_SealedEvent() {}

	////Error: "SealedEvent cannot be used on Blueprint events"
	//UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, SealedEvent)
	//void MyFunc_ImplementableEvent();

	////Error: "SealedEvent cannot be used on Blueprint events"
	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent, SealedEvent)
	//void MyFunc_NativeEvent();
public: //rpc
	//FunctionFlags:	FUNC_Final | FUNC_Net | FUNC_NetReliable | FUNC_Native | FUNC_Event | FUNC_Public | FUNC_NetClient | FUNC_BlueprintCallable 
	UFUNCTION(BlueprintCallable, Client, Reliable, SealedEvent)
	virtual void MyFunc_RunOnClient_SealedEvent();

	//FunctionFlags:	FUNC_Final | FUNC_Net | FUNC_NetReliable | FUNC_Native | FUNC_Event | FUNC_Public | FUNC_NetServer | FUNC_BlueprintCallable 
	UFUNCTION(BlueprintCallable, Server, Reliable, SealedEvent)
	virtual void MyFunc_RunOnServer_SealedEvent();

	//FunctionFlags:	FUNC_Net | FUNC_NetReliable | FUNC_Native | FUNC_Event | FUNC_Public | FUNC_NetClient | FUNC_BlueprintCallable 
	UFUNCTION(BlueprintCallable, Client, Reliable)
	virtual void MyFunc_RunOnClient();

	//	FunctionFlags:	FUNC_Net | FUNC_NetReliable | FUNC_Native | FUNC_Event | FUNC_Public | FUNC_NetServer | FUNC_BlueprintCallable 
	UFUNCTION(BlueprintCallable, Server, Reliable)
	virtual void MyFunc_RunOnServer();

public:
	//FunctionFlags:	FUNC_Final | FUNC_Native | FUNC_Public | FUNC_BlueprintCallable 
	UFUNCTION(BlueprintCallable)
	void MyFunc_BlueprintCallable() {}

	//FunctionFlags:	FUNC_Native | FUNC_Public | FUNC_BlueprintCallable 
	UFUNCTION(BlueprintCallable)
	virtual void MyFunc_BlueprintCallable_Virtual() {}
};


UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyFunction_Sealed_Child :public AMyFunction_Sealed
{
public:
	GENERATED_BODY()
public:

	//UFUNCTION(BlueprintCallable)// Override of UFUNCTION 'MyFunc_BlueprintCallable' in parent 'AMyFunction_Sealed' cannot have a UFUNCTION() declaration above it; it will use the same parameters as the original declaration.
	void MyFunc_BlueprintCallable() {}

	//FunctionFlags:	FUNC_Native | FUNC_Public | FUNC_BlueprintCallable 
	//UFUNCTION(BlueprintCallable)// error : Override of UFUNCTION 'MyFunc_BlueprintCallable_Virtual' in parent 'AMyFunction_Sealed' cannot have a UFUNCTION() declaration above it; it will use the same parameters as the original declaration.
	virtual void MyFunc_BlueprintCallable_Virtual() {}

public:
	virtual void MyFunc_RunOnClient_SealedEvent();

	//FunctionFlags:	FUNC_Final | FUNC_Net | FUNC_NetReliable | FUNC_Native | FUNC_Event | FUNC_Public | FUNC_NetServer | FUNC_BlueprintCallable 
	virtual void MyFunc_RunOnServer_SealedEvent();

	//FunctionFlags:	FUNC_Net | FUNC_NetReliable | FUNC_Native | FUNC_Event | FUNC_Public | FUNC_NetClient | FUNC_BlueprintCallable 
	virtual void MyFunc_RunOnClient();

	//	FunctionFlags:	FUNC_Net | FUNC_NetReliable | FUNC_Native | FUNC_Event | FUNC_Public | FUNC_NetServer | FUNC_BlueprintCallable 
	virtual void MyFunc_RunOnServer();

};