// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/CommonTypes.h"
#include "MyFunction_TestParam.generated.h"

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyFunction_TestParam :public AActor
{
public:
	GENERATED_BODY()
public:
	//PropertyFlags:	CPF_Parm | CPF_OutParm | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic 
	UFUNCTION(BlueprintCallable)
	FString MyFuncTestParam_Default(int& refValue);

	//PropertyFlags:	CPF_Parm | CPF_OutParm | CPF_ZeroConstructor | CPF_ReferenceParm | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic 
	UFUNCTION(BlueprintCallable)
	FString MyFuncTestParam_Ref(UPARAM(ref) int& refValue);

	//PropertyFlags:	CPF_Parm | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic 
	UFUNCTION(BlueprintCallable)
	FString MyFuncTestParam_Copy(int value);

	//(DisplayName = My Other Name)
	//(DisplayName = My Return String)
	UFUNCTION(BlueprintCallable)
	UPARAM(DisplayName = "My Return String") FString MyFuncTestParam_DisplayName(UPARAM(DisplayName = "My Other Name") int value);
public:
	//PropertyFlags:	CPF_ConstParm | CPF_Parm | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic 
	UFUNCTION(BlueprintCallable)
	FString MyFuncTestParam_ConstInt(UPARAM(const) int value);

	//PropertyFlags:	CPF_ConstParm | CPF_Parm | CPF_OutParm | CPF_ZeroConstructor | CPF_ReferenceParm | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic 
	UFUNCTION(BlueprintCallable)
	FString MyFuncTestParam_ConstIntOut(UPARAM(const) int& value);

	//(NativeConst = )
	//PropertyFlags:	CPF_ConstParm | CPF_Parm | CPF_OutParm | CPF_ZeroConstructor | CPF_ReferenceParm | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic 
	UFUNCTION(BlueprintCallable)
	FString MyFuncTestParam_ConstIntRef(UPARAM(const) const int& value);

	//PropertyFlags:	CPF_Parm | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic 
	UFUNCTION(BlueprintCallable)
	FString MyFuncTestParam_NoConstInt(int value);

	//PropertyFlags:	CPF_Parm | CPF_OutParm | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic 
	UFUNCTION(BlueprintCallable)
	FString MyFuncTestParam_NoConstIntOut(int& value);

	//(NativeConst = )
	//PropertyFlags:	CPF_ConstParm | CPF_Parm | CPF_OutParm | CPF_ZeroConstructor | CPF_ReferenceParm | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic 
	UFUNCTION(BlueprintCallable)
	FString MyFuncTestParam_NoConstIntRef(const int& value);

	UFUNCTION(BlueprintCallable)
	void MyFuncTestParam_NoConstObject(UMyCommonObject* myObject) {}

	UFUNCTION(BlueprintCallable)
	void MyFuncTestParam_ConstObject(UPARAM(const) UMyCommonObject* myObject) {}

	UFUNCTION(BlueprintCallable)
	void MyFuncTestParam_NoConstStruct(FMyCommonStruct& myStruct) {}

	UFUNCTION(BlueprintCallable)
	void MyFuncTestParam_ConstStruct(UPARAM(const) FMyCommonStruct& myStruct) {}
public:
	//PropertyFlags:	CPF_Parm | CPF_ZeroConstructor | CPF_RequiredParm | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic 
	UFUNCTION(BlueprintCallable)
	FString MyFuncTestParam_RequiredObject(UPARAM(Required) UObject* objValue);

	//(CPP_Default_intValue = 123, ModuleRelativePath = Function/Param/MyFunction_TestParam.h)
	//PropertyFlags:	CPF_Parm | CPF_ZeroConstructor | CPF_RequiredParm | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic 
	UFUNCTION(BlueprintCallable)
	FString MyFuncTestParam_RequiredInt(UPARAM(Required) int intValue = 123);

public:
	//(CPP_Default_intValue = 123, CPP_Default_intValue2 = 456, ModuleRelativePath = Function/Param/MyFunction_TestParam.h)
	UFUNCTION(BlueprintCallable)
	FString MyFuncTestParam_DefaultInt2(int intValue = 123, int intValue2 = 456);

	//(CPP_Default_InLocation = 1.000000,2.000000,3.000000, ModuleRelativePath = Function/Param/MyFunction_TestParam.h)
	UFUNCTION(BlueprintCallable)
	FString MyFuncTestParam_DefaultVector(FVector InLocation = FVector(1, 2, 3));

	//	(CPP_Default_InString = Hello, ModuleRelativePath = Function/Param/MyFunction_TestParam.h)
	UFUNCTION(BlueprintCallable)
	FString MyFuncTestParam_DefaultString(FString InString = TEXT("Hello"));
public:
	//	(Location = "4,5,6", ModuleRelativePath = Function/Param/MyFunction_TestParam.h)
	UFUNCTION(BlueprintCallable, meta = (Location = "4,5,6"))
	FString MyFuncTestParam_DefaultInMeta(const UObject* WorldContextObject, FVector Location, float Size);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MyInt = 100;
};
