// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyStruct_NoExport.generated.h"


USTRUCT(BlueprintType,noexport)
struct INSIDER_API FMyStruct_NoExport
{
	//GENERATED_BODY()	//missing type specifier - int assumed，..generated.h里只是定一个StaticStruct()函数

	static class UScriptStruct* StaticStruct();	//可以自己定义

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Score;

};

template<> INSIDER_API UScriptStruct* StaticStruct<struct FMyStruct_NoExport>();//可以自己定义
