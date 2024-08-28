// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyClass_Transient.generated.h"

UCLASS(Blueprintable, Transient)
class INSIDER_API UMyClass_Transient :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MyProperty = 123;
};

UCLASS(Blueprintable, NonTransient)
class INSIDER_API UMyClass_NonTransient :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MyProperty = 123;
};


UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyClass_Transient_Test :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMyClass_Transient* MyTransientObject;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMyClass_NonTransient* MyNonTransientObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MyInt_Normal = 123;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient)
	int32 MyInt_Transient = 123;

public:
	static void CreatePackageAndSave();
	static void LoadPackageAndTest();
	static void RunTest();
};


UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyActor_Transient_Test :public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMyClass_Transient* MyTransientObject;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMyClass_NonTransient* MyNonTransientObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MyInt_Normal = 123;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient)
	int32 MyInt_Transient = 123;
};
