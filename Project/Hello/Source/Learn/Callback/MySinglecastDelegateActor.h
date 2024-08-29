// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyBaseCallbackActor.h"
#include "MySinglecastDelegateActor.generated.h"


UCLASS(Blueprintable)
class LEARN_API AMySinglecastDelegateActor :public AMyBaseCallbackActor
{
	GENERATED_BODY()
public:
	AMySinglecastDelegateActor();
	~AMySinglecastDelegateActor();
	DECLARE_DELEGATE_OneParam(FMySinglecastDeleagate_One, int32);

	DECLARE_DELEGATE_RetVal_OneParam(int32, FMySinglecastDeleagate_One_Ret, int32);
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
		void BindStatic();

	UFUNCTION(BlueprintCallable)
		void BindStatic_WithPayload();

	UFUNCTION(BlueprintCallable)
		void BindLambda();
	UFUNCTION(BlueprintCallable)
		void BindRaw();
	UFUNCTION(BlueprintCallable)
		void BindSP();
	UFUNCTION(BlueprintCallable)
		void BindUFunction();
	UFUNCTION(BlueprintCallable)
		void BindUObject();

	UFUNCTION(BlueprintCallable)
		void Unbind();
private:
	FMySinglecastDeleagate_One mDelegate;
};
