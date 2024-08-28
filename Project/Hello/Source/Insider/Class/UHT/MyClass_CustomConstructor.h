// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyClass_CustomConstructor.generated.h"


UCLASS(CustomConstructor)
class INSIDER_API UMyClass_CustomConstructor :public UObject
{
	GENERATED_UCLASS_BODY()	//NO_API UMyClass_ModuleAPI(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
public:
	UMyClass_CustomConstructor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());	//可以自己自定义
public:
};



UCLASS(CustomConstructor)
class INSIDER_API UMyClass_CustomConstructor2 :public UObject
{
	GENERATED_BODY()	//会自动生成默认构造函数
public:
};


UCLASS(CustomConstructor)
class INSIDER_API UMyClass_CustomConstructor3 :public UObject
{
	GENERATED_BODY()	//会自动生成默认构造函数
public:
	UMyClass_CustomConstructor3(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());	//可以自己自定义
};

UCLASS()
class INSIDER_API UMyClass_CustomConstructor4 :public UObject
{
	GENERATED_BODY()	//会自动生成默认构造函数
public:
	UMyClass_CustomConstructor4(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());	//可以自己自定义
};
