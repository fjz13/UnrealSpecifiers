// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProperty_SerializationText.generated.h"


UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyProperty_SerializationText :public UDataAsset
{
public:
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyInt_Default= 123;
		//PropertyFlags:	CPF_Edit | CPF_BlueprintVisible | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic | CPF_SkipSerialization 
	UPROPERTY(EditAnywhere, BlueprintReadWrite,SkipSerialization)
		int32 MyInt_SkipSerialization = 123;
		//PropertyFlags:	CPF_Edit | CPF_BlueprintVisible | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_TextExportTransient | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic 
	UPROPERTY(EditAnywhere, BlueprintReadWrite,TextExportTransient)
		int32 MyInt_TextExportTransient= 123;

};

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyProperty_SerializationText_Test :public UObject
{
	GENERATED_BODY()
public:
	static void RunTest();
	static void RunExportTest();

};
