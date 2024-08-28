// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProperty_ExposeOnSpawn.generated.h"


UCLASS(BlueprintType)
class INSIDER_API UMyProperty_ExposeOnSpawn :public UObject
{
	GENERATED_BODY()
public:
	//	(Category = MyProperty_ExposeOnSpawn, ModuleRelativePath = Property/Blueprint/MyProperty_ExposeOnSpawn.h)
	//	PropertyFlags:	CPF_Edit | CPF_BlueprintVisible | CPF_ZeroConstructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString MyString = TEXT("First");

	//	(Category = MyProperty_ExposeOnSpawn, ExposeOnSpawn = , ModuleRelativePath = Property/Blueprint/MyProperty_ExposeOnSpawn.h)
	//	PropertyFlags:	CPF_Edit | CPF_BlueprintVisible | CPF_ZeroConstructor | CPF_ExposeOnSpawn | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn))
	FString MyString_ExposeOnSpawn = TEXT("Second");
};

