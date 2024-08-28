// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyClass_MinimalAPI.generated.h"

UCLASS()
class UMyClass_NotMinimalAPI :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MyProperty;
	UFUNCTION(BlueprintCallable)
	void MyFunc();
};

UCLASS(MinimalAPI)
class UMyClass_MinimalAPI :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MyProperty;
	UFUNCTION(BlueprintCallable)
	void MyFunc();
};

UCLASS(MinimalAPI, BlueprintType)
class UMyClass_MinimalAPI_BlueprintType :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MyProperty;
	UFUNCTION(BlueprintCallable)
	void MyFunc() {}
};


UCLASS(MinimalAPI)
class UMyClass_MinimalAPI_BlueprintFunctionLibary :public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	static void MyFuncInMinimalAPI();

	UFUNCTION(BlueprintCallable)
	static INSIDER_API void MyFuncInMinimalAPIWithAPI();
};



UCLASS()
class INSIDER_API UMyClass_DefaultExport :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MyProperty;
	UFUNCTION(BlueprintCallable)
	void MyFunc();
};


/*
class UClass * __ptr64 __cdecl StaticClass<class UMyClass_MinimalAPI>(void)
class UClass * __ptr64 __cdecl StaticClass<class UMyClass_MinimalAPI_BlueprintFunctionLibary>(void)
class UClass * __ptr64 __cdecl StaticClass<class UMyClass_MinimalAPI_BlueprintType>(void)
class UClass * __ptr64 __cdecl StaticClass<class UMyClass_NotMinimalAPI>(void)
class UClass * __ptr64 __cdecl Z_Construct_UClass_UMyClass_MinimalAPI(void)
class UClass * __ptr64 __cdecl Z_Construct_UClass_UMyClass_MinimalAPI_BlueprintFunctionLibary(void)
class UClass * __ptr64 __cdecl Z_Construct_UClass_UMyClass_MinimalAPI_BlueprintFunctionLibary_NoRegister(void)
class UClass * __ptr64 __cdecl Z_Construct_UClass_UMyClass_MinimalAPI_BlueprintType(void)
class UClass * __ptr64 __cdecl Z_Construct_UClass_UMyClass_MinimalAPI_BlueprintType_NoRegister(void)
class UClass * __ptr64 __cdecl Z_Construct_UClass_UMyClass_MinimalAPI_NoRegister(void)
class UClass * __ptr64 __cdecl Z_Construct_UClass_UMyClass_NotMinimalAPI(void)
class UClass * __ptr64 __cdecl Z_Construct_UClass_UMyClass_NotMinimalAPI_NoRegister(void)
private: static class UClass * __ptr64 __cdecl UMyClass_MinimalAPI::GetPrivateStaticClass(void)
private: static class UClass * __ptr64 __cdecl UMyClass_MinimalAPI_BlueprintFunctionLibary::GetPrivateStaticClass(void)
private: static class UClass * __ptr64 __cdecl UMyClass_MinimalAPI_BlueprintType::GetPrivateStaticClass(void)
public: __cdecl UMyClass_MinimalAPI::UMyClass_MinimalAPI(class FObjectInitializer const & __ptr64) __ptr64
public: __cdecl UMyClass_MinimalAPI::UMyClass_MinimalAPI(class FVTableHelper & __ptr64) __ptr64
public: __cdecl UMyClass_MinimalAPI_BlueprintFunctionLibary::UMyClass_MinimalAPI_BlueprintFunctionLibary(class FObjectInitializer const & __ptr64) __ptr64
public: __cdecl UMyClass_MinimalAPI_BlueprintFunctionLibary::UMyClass_MinimalAPI_BlueprintFunctionLibary(class FVTableHelper & __ptr64) __ptr64
public: __cdecl UMyClass_MinimalAPI_BlueprintType::UMyClass_MinimalAPI_BlueprintType(class FObjectInitializer const & __ptr64) __ptr64
public: __cdecl UMyClass_MinimalAPI_BlueprintType::UMyClass_MinimalAPI_BlueprintType(class FVTableHelper & __ptr64) __ptr64
public: static void __cdecl UMyClass_MinimalAPI_BlueprintFunctionLibary::MyFuncInMinimalAPIWithAPI(void)
public: virtual __cdecl UMyClass_MinimalAPI::~UMyClass_MinimalAPI(void) __ptr64
public: virtual __cdecl UMyClass_MinimalAPI_BlueprintFunctionLibary::~UMyClass_MinimalAPI_BlueprintFunctionLibary(void) __ptr64
public: virtual __cdecl UMyClass_MinimalAPI_BlueprintType::~UMyClass_MinimalAPI_BlueprintType(void) __ptr64
public: void __cdecl UMyClass_MinimalAPI::`default constructor closure'(void) __ptr64
public: void __cdecl UMyClass_MinimalAPI_BlueprintFunctionLibary::`default constructor closure'(void) __ptr64
public: void __cdecl UMyClass_MinimalAPI_BlueprintType::`default constructor closure'(void) __ptr64

*/