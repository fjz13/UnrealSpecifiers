// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProperty_Enum.generated.h"



UENUM(BlueprintType)
enum class EMyPropertyTestEnum : uint8
{
	First,
	Second,
	Third,
	Forth,
	Fifth,
};


UENUM(BlueprintType)
namespace EMyPropertyTestEnum2
{
	enum Type : int
	{
		First,
		Second,
		Third,
		Forth,
		Fifth,
	};
}

UCLASS(BlueprintType)
class INSIDER_API UMyProperty_Enum :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMyPropertyTestEnum MyEnum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ValidEnumValues = "First,Second,Third"))
	EMyPropertyTestEnum MyEnumWithValid;	// Type 1

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ValidEnumValues = "First,Second,Third"))
	TEnumAsByte<EMyPropertyTestEnum2::Type> MyAnotherEnumWithValid;	//Type 2

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (enum = "EMyPropertyTestEnum",ValidEnumValues = "First,Second,Third"))
	FString MyStringWithEnum;	//Type 3

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (InvalidEnumValues = "First,Second,Third"))
	EMyPropertyTestEnum MyEnumWithInvalid = EMyPropertyTestEnum::Forth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (GetRestrictedEnumValues = "MyGetRestrictedEnumValues"))
	EMyPropertyTestEnum MyEnumWithRestricted;

public:
	UFUNCTION(BlueprintInternalUseOnly)
	TArray<FString> MyGetRestrictedEnumValues() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EnumValueDisplayNameOverrides = "First=Cat;Second=Dog"))
	EMyPropertyTestEnum MyEnumWithDisplayNameOverrides;
};

