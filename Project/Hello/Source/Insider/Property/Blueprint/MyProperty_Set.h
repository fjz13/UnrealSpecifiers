// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProperty_Set.generated.h"


UCLASS(BlueprintType)
class INSIDER_API UMyProperty_Set :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter)
	int32 MyProperty = 123;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetMyProperty2)
	int32 MyProperty2 = 123;

public:
	void SetMyProperty(int32 InArg);

	UFUNCTION(BlueprintSetter)
	void SetMyProperty2(int32 InArg);
public:
	//(BlueprintSetter = , Category = Blueprint, ModuleRelativePath = Property/MyProperty_Test.h)
	UFUNCTION(BlueprintSetter, Category = Blueprint)	//or BlueprintCallable
		void MyInt_Setter(int NewValue) { MyInt_WithSetter = NewValue / 4; }
private:
	//(BlueprintSetter = MyInt_Setter, Category = Blueprint, ModuleRelativePath = Property/MyProperty_Test.h)
	//PropertyFlags:	CPF_BlueprintVisible | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPrivate 
	UPROPERTY(BlueprintSetter = MyInt_Setter, Category = Blueprint)
	int32 MyInt_WithSetter = 123;

public:
	UPROPERTY(BlueprintReadWrite, Setter)
	float MyFloat = 1.0f;

	UPROPERTY(BlueprintReadWrite, Setter = SetMyCustomFloat)
	float MyFloat2 = 1.0f;
public:
	void SetMyFloat(float val) { MyFloat = val + 100.f; }
	void SetMyCustomFloat(float val) { MyFloat2 = val + 100.f; }

public:
	UFUNCTION(BlueprintCallable)
	void RunTest();
};

