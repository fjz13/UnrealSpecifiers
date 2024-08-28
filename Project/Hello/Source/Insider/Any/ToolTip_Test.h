// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ToolTip_Test.generated.h"

//(BlueprintType = true, IncludePath = Any/ToolTip_Test.h, IsBlueprintBase = true, ModuleRelativePath = Any/ToolTip_Test.h, ToolTip = This is a ToolTip within Class. There're so so so so so so so many words I want to say, but here's too narrow.)

// This is a ToolTip out of Class.There're so so so so so so so many words I want to say, but here's too narrow.
UCLASS(BlueprintType, Blueprintable, meta = (ToolTip = "This is a ToolTip within Class. There're so so so so so so so many words I want to say, but here's too narrow."))
class INSIDER_API UMyClass_ToolTip :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ToolTip = "This is a ToolTip within Property.There're so so so so so so so many words I want to say, but here's too narrow."))
	float MyFloat_WithToolTip;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString MyString;


	UFUNCTION(BlueprintCallable, meta = (ToolTip = "This is a ToolTip within Function.There're so so so so so so so many words I want to say, but here's too narrow."))
	void MyFunc_WithToolTip() {}

	UFUNCTION(BlueprintCallable)
	void MyFunc() {}
};

/*(BlueprintType = true, IncludePath = Any / ToolTip_Test.h, IsBlueprintBase = true, ModuleRelativePath = Any / ToolTip_Test.h, ShortToolTip = This is a ShortToolTip within Class., ToolTip = This is a ToolTip within Class.There're so so so so so so so many words I want to say, but here's too narrow.
This is a new line.)*/


// This is a ToolTip out of Class.There're so so so so so so so many words I want to say, but here's too narrow.
UCLASS(BlueprintType, Blueprintable, meta = (ToolTip = "This is a ToolTip within Class. There're so so so so so so so many words I want to say, but here's too narrow.", ShortToolTip = "This is a ShortToolTip within Class."))
class INSIDER_API UMyClass_WithAllToolTip :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ToolTip = "This is a ToolTip within Property. There're so so so so so so so many words I want to say, but here's too narrow."))
	float MyFloat_WithToolTip;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ToolTip = "This is a ToolTip within Property. There're so so so so so so so many words I want to say, but here's too narrow.\nThis is a new line.",ShortToolTip = "This is a ShortToolTip within Property."))
	float MyFloat_WithAllToolTip;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString MyString;


	UFUNCTION(BlueprintCallable, meta = (ToolTip = "This is a ToolTip within Function. There're so so so so so so so many words I want to say, but here's too narrow.",ShortToolTip = "This is a ShortToolTip within Function."))
	void MyFunc_WithAllToolTip() {}

	UFUNCTION(BlueprintCallable, meta = (ToolTip = "This is a ToolTip within Function. There're so so so so so so so many words I want to say, but here's too narrow."))
	void MyFunc_WithToolTip() {}
};


/*
(BlueprintType = true, Comment = // This is a ToolTip out of Class.There're so so so so so so so many words I want to say, but here's too narrow.
, IncludePath = Any/ToolTip_Test.h, IsBlueprintBase = true, ModuleRelativePath = Any/ToolTip_Test.h, ToolTip = This is a ToolTip out of Class.There're so so so so so so so many words I want to say, but here's too narrow.)
*/

// This is a ToolTip out of Class.There're so so so so so so so many words I want to say, but here's too narrow.
UCLASS(BlueprintType, Blueprintable)
class INSIDER_API UMyClass_ToolTip_TypeA :public UObject
{
	GENERATED_BODY()
};


//[MyClass_ToolTip_TypeB	Class->Struct->Field->Object	/Script/Insider.MyClass_ToolTip_TypeB]
//(BlueprintType = true, Comment = /**
//*	This is a ToolTip out of Class.
//*	There're so so so so so so so many words I want to say, but here's too narrow.
//*	Please read this tooltip before you use this class. 
//*/, IncludePath = Any/ToolTip_Test.h, IsBlueprintBase = true, ModuleRelativePath = Any/ToolTip_Test.h, ToolTip = This is a ToolTip out of Class.
//There're so so so so so so so many words I want to say, but here's too narrow.
//Please read this tooltip before you use this class.)

/**
*	This is a ToolTip out of Class.
*	There're so so so so so so so many words I want to say, but here's too narrow.
*	Please read this tooltip before you use this class. 
*/
UCLASS(BlueprintType, Blueprintable)
class INSIDER_API UMyClass_ToolTip_TypeB :public UObject
{
	GENERATED_BODY()
};


USTRUCT(BlueprintType, Blueprintable, meta = (ToolTip = "This is a ToolTip within Struct. There're so so so so so so so many words I want to say, but here's too narrow."))
struct INSIDER_API FMyStruct_ToolTip
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MyFloat=0.f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString MyString;
};


UENUM(BlueprintType, meta = (ToolTip = "This is a ToolTip within Struct."))
enum class EMyEnum_ToolTip :uint8
{
	First,
	Second,
	Third,
};

