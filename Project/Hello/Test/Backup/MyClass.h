// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyInterface.h"
#include "MyDelegate.h"
#include "MyStruct.h"
#include "MyObject.h"

#include "MyClass.generated.h"

UCLASS(BlueprintType, Blueprintable)
class HELLO_API UMyClass :public UObject, public IMyInterface
{
	GENERATED_BODY()
public:
	UMyClass();
public:
	UPROPERTY(BlueprintReadWrite)
		float Score;

	UPROPERTY(BlueprintReadWrite)
		TSubclassOf<UObject> classObj;

	UPROPERTY(BlueprintReadWrite)
		FSoftClassPath path;
	UPROPERTY(BlueprintReadWrite)
		TWeakObjectPtr<UObject> weakObj;
	UPROPERTY()
		TLazyObjectPtr< UObject> lazyObj;
	UFUNCTION(BlueprintNativeEvent, Category = "Hello")
		void NativeFunc();  //C++实现默认版本，蓝图可重载实现

	UPROPERTY(BlueprintReadWrite)
		FSoftObjectPath softObj;

	UPROPERTY(BlueprintReadWrite)
		TScriptInterface<IMyInterface> interfaceObj;

	UPROPERTY(BlueprintReadWrite)
		FMyStruct myStruct;

	UPROPERTY(BlueprintReadWrite)
		UMyObject* myObject;

	UPROPERTY(BlueprintReadWrite)
		TArray<int> myArray;
public:
	UFUNCTION(BlueprintCallable, Category = "Hello")
		virtual int32 Func(float param1);    //C++实现，蓝图调用

	
	UFUNCTION(BlueprintCallable, Category = "Hello")
		virtual void VoidFunc();    //C++实现，蓝图调用


	UFUNCTION(BlueprintImplementableEvent, Category = "Hello")
		void ImplementableFunc();   //C++不实现，蓝图实现

	//UFUNCTION(NetMulticast, Reliable)
	//	virtual void NetFunc();

public:
	virtual void PostInitProperties()override;
	virtual void PostCDOContruct()override;
	virtual void PostLoad()override;

public:
	/*UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void BPFunc() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void Func_NativeEvent() const;*/
};
