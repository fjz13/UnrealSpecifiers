// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyClass_MatchedSerializers.generated.h"




UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyClass_MatchedSerializersMain :public UObject
{
public:
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MyInt_Default = 123;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMyClass_MatchedSerializersSub* SubObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UClass* TypeClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UEnum* MyProperty;

};

UCLASS(Blueprintable, BlueprintType,editinlinenew)
class INSIDER_API UMyClass_MatchedSerializersSub :public UObject
{
public:
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MyInt_Default = 123;
};

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyClass_MatchedSerializersTestAsset:public UDataAsset
{
public:
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MyInt_Default = 123;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Instanced)
	UMyClass_MatchedSerializersSub* SubObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStruct* MyStructType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UClass* MyClassType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UEnum* MyEnumType;
};


UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyClass_MatchedSerializers_Test :public UObject
{
	GENERATED_BODY()

public:
public:
	static void RunTest();
	static void RunExportTest();
	static void PrintFlagClasses();

	UFUNCTION(BlueprintCallable,CallInEditor)
	static void ApplyClassFlag();

	UFUNCTION(BlueprintCallable,CallInEditor)
	static void RemoveClassFlag();

};
