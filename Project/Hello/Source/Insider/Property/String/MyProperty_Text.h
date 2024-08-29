// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProperty_Text.generated.h"

USTRUCT(BlueprintType)
struct INSIDER_API FMyOptionsTest
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta = (GetOptions = "MyGetOptions_Static"))
	FString MyString_GetOptions;

	UPROPERTY(EditAnywhere, meta = (GetOptions = "MyGetOptions_Static"))
	TArray<FString> MyArray_GetOptions;

	UPROPERTY(EditAnywhere, meta = (GetOptions = "MyGetOptions_Static"))
	TSet<FString> MySet_GetOptions;

	UPROPERTY(EditAnywhere, meta = (GetOptions = "MyGetOptions_Static"))
	TMap<FString, int32> MyMap_GetOptions;
};


UCLASS(BlueprintType)
class INSIDER_API UMyProperty_Text :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	FName MyName = TEXT("Hello");

	UPROPERTY(EditAnywhere)
	FString MyString = TEXT("Hello");

	UPROPERTY(EditAnywhere)
	FText MyText = INVTEXT("Hello");
public:
	UPROPERTY(EditAnywhere, Category = PasswordTest, meta = (PasswordField = true))
	FName MyName_Password = TEXT("Hello");

	UPROPERTY(EditAnywhere, Category = PasswordTest, meta = (PasswordField = true))
	FString MyString_Password = TEXT("Hello");

	UPROPERTY(EditAnywhere, Category = PasswordTest, meta = (PasswordField = true))
	FText MyText_Password = INVTEXT("Hello");
public:
	UPROPERTY(EditAnywhere, Category = MultiLineTest, meta = (MultiLine = true))
	FName MyName_MultiLine = TEXT("Hello");

	UPROPERTY(EditAnywhere, Category = MultiLineTest, meta = (MultiLine = true))
	FString MyString_MultiLine = TEXT("Hello");

	UPROPERTY(EditAnywhere, Category = MultiLineTest, meta = (MultiLine = true))
	FText MyText_MultiLine = INVTEXT("Hello");

	UPROPERTY(EditAnywhere, Category = MultiLineTest, meta = (MultiLine = true, PasswordField = true))
	FString MyString_MultiLine_Password = TEXT("Hello");

	UPROPERTY(EditAnywhere, Category = MultiLineTest, meta = (MultiLine = true, PasswordField = true))
	FText MyText_MultiLine_Password = INVTEXT("Hello");
public:
	UPROPERTY(EditAnywhere, Category = MaxLengthTest, meta = (MaxLength = 10))
	FString MyString_MaxLength10 = TEXT("Hello");

public:
	UPROPERTY(EditAnywhere, Category = AllowedCharactersTest, meta = (AllowedCharacters = "abcde"))
	FString MyString_AllowedCharacters;
	UPROPERTY(EditAnywhere, Category = AllowedCharactersTest, meta = (AllowedCharacters = "你好"))
	FString MyString_AllowedCharacters_Chinese;

public:
	UPROPERTY(EditAnywhere, Category = PropertyValidatorTest, meta = (PropertyValidator = "MyValidateMyString"))
	FString MyString_PropertyValidator;

	UFUNCTION()
	static FText MyValidateMyString(const FString& Value);
public:
	UPROPERTY(EditAnywhere, Category = GetOptions)
	FString MyString_NoOptions;

	UPROPERTY(EditAnywhere, Category = GetOptions, meta = (GetOptions = "MyGetOptions"))
	FString MyString_GetOptions;

	UPROPERTY(EditAnywhere, Category = GetOptions, meta = (GetOptions = "MyGetOptions"))
	FName MyName_GetOptions;

	UPROPERTY(EditAnywhere, Category = GetOptions, meta = (GetOptions = "MyGetOptions"))
	FText MyText_GetOptions;

	UPROPERTY(EditAnywhere, Category = GetOptions, meta = (GetOptions = "MyGetOptions"))
	TArray<FString> MyArray_GetOptions;

	UPROPERTY(EditAnywhere, Category = GetOptions, meta = (GetOptions = "MyGetOptions"))
	TSet<FString> MySet_GetOptions;

	UPROPERTY(EditAnywhere, Category = GetOptions, meta = (GetOptions = "MyGetOptions"))
	TMap<FString, int32> MyMap_GetOptions;

	UFUNCTION()
	static TArray<FString> MyGetOptions_Static() { return TArray<FString>{"Cat", "Dog"}; }

	UFUNCTION()
	TArray<FString> MyGetOptions() { return TArray<FString>{"First", "Second", "Third"}; }
public:
	UPROPERTY(EditAnywhere, Category = GetOptionsStruct)
	FMyOptionsTest MyStruct_GetOptions;

public:
	UPROPERTY(EditAnywhere, Category = GetKeyValueOptions, meta = (GetKeyOptions = "MyGetOptions",GetValueOptions="MyGetOptions_Static"))
	TMap<FString, FName> MyMap_GetKeyValueOptions;
public:
	UFUNCTION(CallInEditor)
	void RunTest();
};

