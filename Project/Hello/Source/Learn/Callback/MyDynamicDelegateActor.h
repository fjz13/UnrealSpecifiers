// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyDelegate.h"
#include "MyDynamicDelegateActor.generated.h"

UCLASS(Blueprintable)
class LEARN_API AMyDynamicDelegateActor :public AActor
{
	GENERATED_BODY()
public:
	AMyDynamicDelegateActor();

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
		void AddDelegate(FMyDynamicSinglecastDelegate_One Event);

	// Error: Type '{multicast delegate type}' is not supported by blueprint. AddDelegate.val
	//UFUNCTION(BlueprintCallable)
	//	void AddDelegate(FMyDynamicMulticastDelegate_One val) {}
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, BlueprintCallable)
		FMyDynamicMulticastDelegate_One OnMulticastDelegateAssignAndCall;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable)
		FMyDynamicMulticastDelegate_One OnMulticastDelegateAssign;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FMyDynamicMulticastDelegate_One OnMulticastDelegate;

	//'BlueprintCallable' is only allowed on a property when it is a multicast delegate
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintCallable)
	//	FMyDynamicSinglecastDelegate OnMyDelegate4;

	//'BlueprintAssignable' is only allowed on a property when it is a multicast delegate
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable)
		FMyDynamicSinglecastDelegate OnMyDelegate5;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FMyDynamicSinglecastDelegate_One OnSinglecastDelegate;
};
