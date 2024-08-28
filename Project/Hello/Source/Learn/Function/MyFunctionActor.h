// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyFunctionActor.generated.h"

UCLASS(Blueprintable)
class LEARN_API AMyFunctionActor :public AActor
{
	GENERATED_BODY()
public:
	AMyFunctionActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	UFUNCTION(BlueprintCallable,Category="Test")
		void Func_Callable();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Test")
		void Func_ImplementableEvent();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Test")
		void Func_NativeEvent();

	UFUNCTION(BlueprintPure, Category = "Test")
		float Func_Pure() { return 3.f; }

	UFUNCTION(CallInEditor, Category = "Test")
		static void Func_CallInEditor();
};
