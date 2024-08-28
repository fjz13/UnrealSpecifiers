// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProperty_Get.generated.h"


UCLASS(BlueprintType)
class INSIDER_API UMyProperty_Get :public UObject
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintPure, meta = (GetByRef))
	TArray<int>& GetMyArray() { return Items; }
private:
	TArray<int> Items;


public:
	//(BlueprintGetter = , Category = Blueprint, ModuleRelativePath = Property/MyProperty_Test.h)
	UFUNCTION(BlueprintGetter, Category = Blueprint)	//or BlueprintPure
		int32 MyInt_Getter()const { return MyInt_WithGetter * 2; }
private:
	//(BlueprintGetter = MyInt_Getter, Category = Blueprint, ModuleRelativePath = Property/MyProperty_Test.h)
	//PropertyFlags:	CPF_BlueprintVisible | CPF_BlueprintReadOnly | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPrivate 
	UPROPERTY(BlueprintGetter = MyInt_Getter, Category = Blueprint)
	int32 MyInt_WithGetter = 123;

public:
	//GetterFunc:	Has Native Getter
	UPROPERTY(BlueprintReadWrite, Getter)
	float MyFloat = 1.0f;

	//GetterFunc:	Has Native Getter
	UPROPERTY(BlueprintReadWrite, Getter = GetMyCustomFloat)
	float MyFloat2 = 1.0f;
public:
	float GetMyFloat()const { return MyFloat + 100.f; }

	float GetMyCustomFloat()const { return MyFloat2 + 100.f; }
public:
	UFUNCTION(BlueprintCallable)
	void RunTest();
};

