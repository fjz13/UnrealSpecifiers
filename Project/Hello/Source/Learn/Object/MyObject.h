// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <Interface/MyInterface.h>
#include "MyObject.generated.h"

UCLASS()
class LEARN_API UMyObject :public UObject
{
	GENERATED_BODY()
		UMyObject();
public:
	UPROPERTY(BlueprintReadWrite)
		float Score;
public:
	UFUNCTION(BlueprintCallable, Category = "Hello")
		void CallableFunc();    //C++ʵ�֣���ͼ����

	UFUNCTION(BlueprintNativeEvent, Category = "Hello")
		void NativeFunc();  //C++ʵ��Ĭ�ϰ汾����ͼ������ʵ��

	UFUNCTION(BlueprintImplementableEvent, Category = "Hello")
		void ImplementableFunc();   //C++��ʵ�֣���ͼʵ��

public:
	//UPROPERTY(BlueprintReadOnly)
		//class UMyClass* InnerStruct;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<TScriptInterface<IMyInterface>> MyInterface;
};
