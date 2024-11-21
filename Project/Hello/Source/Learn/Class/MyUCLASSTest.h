// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Class/DllExport/MyClass_MinimalAPI.h"
#include "MyUCLASSTest.generated.h"

UCLASS(BlueprintType,Blueprintable)
class LEARN_API UMyClass_MinimalAPI_Child_InOtherModule :public UMyClass_MinimalAPI
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MyProperty2;
	UFUNCTION(BlueprintCallable)
	void MyFunc2();
};