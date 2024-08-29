// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#if 0
#include "DocumentationPolicy_Test.generated.h"


UCLASS(BlueprintType, meta = (DocumentationPolicy = Strict))
class INSIDER_API UMyClass_DocumentationPolicy :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MyFloat;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString MyString;

	//This is a float
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (UIMin = "0.0", UIMax = "100.0"))
	float MyFloat_WithValidate;

	UFUNCTION(meta = (DocumentationPolicy = Strict))
	void MyFunc() {}

	/**
	 *	Test Func for validate param
	 * 	@param keyOtherName The name of Key
	 *	@param keyValue
	 */
	UFUNCTION(BlueprintCallable, meta = (DocumentationPolicy = Strict))
	int MyFunc_ValidateParamFailed(FString keyName, int keyValue) { return 0; }

	/**
	 *	Test Func for validate param
	 *
	 *	@param keyName The name of key
	 *	@param keyValue The value of key
	 *	@return Return operation result
	 */
	UFUNCTION(meta = (DocumentationPolicy = Strict))
	int MyFunc_ValidateParam(FString keyName, int keyValue) { return 0; }
};


USTRUCT(BlueprintType, meta = (DocumentationPolicy = Strict))
struct INSIDER_API FMyStruct_DocumentationPolicy
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MyFloat;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString MyString;
};


UENUM(BlueprintType, meta = (DocumentationPolicy = Strict))
enum class EMyEnum_DocumentationPolicy :uint8
{
	First,
	Second,
	Third,
};

// This a tooltip / comment
UCLASS(BlueprintType, meta = (DocumentationPolicy = Strict))
class INSIDER_API UMyClass_DocumentationPolicy_TypeA :public UObject
{
	GENERATED_BODY()
};

/**
*	This a tooltip / comment
*
*/
UCLASS(BlueprintType, meta = (DocumentationPolicy = Strict))
class INSIDER_API UMyClass_DocumentationPolicy_TypeB :public UObject
{
	GENERATED_BODY()
};


UCLASS(BlueprintType, meta = (DocumentationPolicy = Strict, ToolTip = "This a tooltip"))	//Cannot use ShortToolTip
class INSIDER_API UMyClass_DocumentationPolicy_TypeC :public UObject
{
	GENERATED_BODY()
};

#endif
