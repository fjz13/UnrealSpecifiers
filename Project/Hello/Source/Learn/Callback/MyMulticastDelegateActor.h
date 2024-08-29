// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyBaseCallbackActor.h"
#include "MyMulticastDelegateActor.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FMyMulticastDelegate_One,int32);
//not support return value
//DECLARE_DELEGATE_OneParam(FMySinglecastDelegate2_One, int32);

UCLASS(Blueprintable)
class LEARN_API AMyMulticastDelegateActor :public AMyBaseCallbackActor
{
	GENERATED_BODY()
public:
	AMyMulticastDelegateActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	UFUNCTION(BlueprintCallable)
		void ExecuteCallback(int32 val);
public:
	UFUNCTION(BlueprintCallable)
		void AddStatic();
	UFUNCTION(BlueprintCallable)
		void AddStatic_WithPayload();
	UFUNCTION(BlueprintCallable)
		void AddLambda();
	UFUNCTION(BlueprintCallable)
		void AddRaw();
	UFUNCTION(BlueprintCallable)
		void AddSP();
	UFUNCTION(BlueprintCallable)
		void AddUFunction();
	UFUNCTION(BlueprintCallable)
		void AddUObject();

	UFUNCTION(BlueprintCallable)
		void AddDelegate();

	UFUNCTION(BlueprintCallable)
		void UnbindAll();
private:
	FMyMulticastDelegate_One mDelegate;

};
