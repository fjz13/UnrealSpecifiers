// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyFunction_Access.generated.h"

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyFunction_Access :public AActor
{
public:
	GENERATED_BODY()
public:
	//(BlueprintProtected = true, ModuleRelativePath = Function/MyFunction_Access.h)
	//FUNC_Final | FUNC_Native | FUNC_Public | FUNC_BlueprintCallable 
	UFUNCTION(BlueprintCallable, meta = (BlueprintProtected = "true"))
	void MyNative_HasProtected() {}

	//(BlueprintPrivate = true, ModuleRelativePath = Function/MyFunction_Access.h)
	//FUNC_Final | FUNC_Native | FUNC_Public | FUNC_BlueprintCallable 
	UFUNCTION(BlueprintCallable, meta = (BlueprintPrivate = "true"))
	void MyNative_HasPrivate() {}
public:
	//FUNC_Final | FUNC_Native | FUNC_Public | FUNC_BlueprintCallable 
	UFUNCTION(BlueprintCallable)
	void MyNative_NativePublic() {}
protected:
	//FUNC_Final | FUNC_Native | FUNC_Protected | FUNC_BlueprintCallable 
	UFUNCTION(BlueprintCallable)
	void MyNative_NativeProtected() {}
private:
	//FUNC_Final | FUNC_Native | FUNC_Private | FUNC_BlueprintCallable 
	UFUNCTION(BlueprintCallable)
	void MyNative_NativePrivate() {}


public:
	//(BlueprintProtected = true, Category = MyFunction_Access, ModuleRelativePath = Function/MyFunction_Access.h)
	//CPF_BlueprintVisible | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic 
	UPROPERTY(BlueprintReadWrite, meta = (BlueprintProtected = "true"))
	int32 MyNativeInt_HasProtected;

	//(BlueprintPrivate = true, Category = MyFunction_Access, ModuleRelativePath = Function/MyFunction_Access.h)
	//CPF_BlueprintVisible | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic 
	UPROPERTY(BlueprintReadWrite, meta = (BlueprintPrivate = "true"))
	int32 MyNativeInt_HasPrivate;

public:
	//CPF_BlueprintVisible | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic 
	UPROPERTY(BlueprintReadWrite)
	int32 MyNativeInt_NativePublic;
protected:
	//CPF_BlueprintVisible | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_Protected | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierProtected 
	UPROPERTY(BlueprintReadOnly)
	int32 MyNativeInt_NativeProtected;
private:
	//CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPrivate 
	//error : BlueprintReadWrite should not be used on private members
	UPROPERTY()
	int32 MyNativeInt_NativePrivate;

	//(AllowPrivateAccess = TRUE, Category = MyFunction_Access, ModuleRelativePath = Function/MyFunction_Access.h)
	//CPF_BlueprintVisible | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPrivate 
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 MyNativeInt_NativePrivate_AllowPrivateAccess;
};

//AllowPrivateAccess