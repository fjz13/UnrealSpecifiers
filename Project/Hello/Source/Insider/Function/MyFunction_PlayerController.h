// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyFunction_PlayerController.generated.h"

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyFunction_PlayerController :public APlayerController
{
	GENERATED_BODY()
public:
	//FunctionFlags:	FUNC_Net | FUNC_NetReliable | FUNC_Native | FUNC_Event | FUNC_Public | FUNC_NetClient | FUNC_BlueprintCallable 
	UFUNCTION(BlueprintCallable, Client, Reliable)
	void MyFunc_RunOnClient();

	//FunctionFlags:	FUNC_Net | FUNC_NetReliable | FUNC_Native | FUNC_Event | FUNC_Public | FUNC_NetServer | FUNC_BlueprintCallable | FUNC_NetValidate 
	UFUNCTION(BlueprintCallable, Server, Reliable)
	void MyFunc_RunOnServer();

public:
	//	FunctionFlags:	FUNC_Net | FUNC_NetReliable | FUNC_Native | FUNC_Event | FUNC_Public | FUNC_NetClient | FUNC_BlueprintCallable | FUNC_NetValidate 
	UFUNCTION(BlueprintCallable, Client, Reliable, WithValidation)
	void MyFunc2_RunOnClient();

	//FunctionFlags:	FUNC_Net | FUNC_NetReliable | FUNC_Native | FUNC_Event | FUNC_Public | FUNC_NetServer | FUNC_BlueprintCallable | FUNC_NetValidate 

	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation)
	void MyFunc2_RunOnServer();

public:
	//(CustomThunk = true, ModuleRelativePath = Function/MyFunction_Network.h)
	//FunctionFlags:	FUNC_Net | FUNC_NetReliable | FUNC_NetRequest | FUNC_Native | FUNC_Event | FUNC_Public | FUNC_BlueprintCallable 
	UFUNCTION(BlueprintCallable, ServiceRequest(MyEndPoint))
	void MyFunc_ServiceRequest();

	//FunctionFlags:	FUNC_Net | FUNC_NetReliable | FUNC_Native | FUNC_Event | FUNC_NetResponse | FUNC_Public | FUNC_BlueprintCallable 
	UFUNCTION(BlueprintCallable, ServiceResponse(MyEndPoint))
	void MyFunc_ServiceResponse();
};
