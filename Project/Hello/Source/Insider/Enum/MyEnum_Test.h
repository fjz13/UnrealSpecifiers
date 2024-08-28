// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyEnum_Test.generated.h"

/*
[enum 602d0d4e680 EMyEnum_HasDisplayName	Enum->Field->Object	/Script/Insider.EMyEnum_HasDisplayName]
(BlueprintType = true, First.DisplayName = Dog, First.Name = EMyEnum_HasDisplayName::First, IsBlueprintBase = true, ModuleRelativePath = Enum/MyEnum_Test.h, Second.DisplayName = Cat, Second.Name = EMyEnum_HasDisplayName::Second, Third.DisplayName = Pig, Third.Name = EMyEnum_HasDisplayName::Third)
	ObjectFlags:	RF_Public | RF_Transient 
	Outer:	Package /Script/Insider
	EnumFlags:	None
	EnumDisplayNameFn:	0
	CppType:	EMyEnum_HasDisplayName
	CppForm:	EnumClass
{
	First = 0,
	Second = 1,
	Third = 2,
	EMyEnum_MAX = 3
};
*/
UENUM(Blueprintable)
enum class EMyEnum_HasDisplayName :uint8
{
	First UMETA(DisplayName="Dog"),
	Second UMETA(DisplayName="Cat"),
	Third UMETA(DisplayName="Pig"),
};


//[EMyEnum_CustomDisplay	Enum->Field->Object	/Script/Insider.EMyEnum_CustomDisplay]
//(BlueprintType = true, EnumDisplayNameFn = GetMyEnumCustomDisplayName, First.Name = EMyEnum_CustomDisplay::First, IsBlueprintBase = true, ModuleRelativePath = Enum/MyEnum_Test.h, Second.Name = EMyEnum_CustomDisplay::Second, Third.Name = EMyEnum_CustomDisplay::Third)
//	ObjectFlags:	RF_Public | RF_Transient 
//	Outer:	Package /Script/Insider
//	EnumFlags:	EEnumFlags::None
//	EnumDisplayNameFn:	6adb4804
//	CppType:	EMyEnum_CustomDisplay
//	CppForm:	EnumClass
//{
//	First = 0,
//	Second = 1,
//	Third = 2,
//	EMyEnum_MAX = 3
//};

UENUM(Blueprintable, meta = (EnumDisplayNameFn = "GetMyEnumCustomDisplayName"))
enum class EMyEnum_CustomDisplay :uint8
{
	First,
	Second,
	Third,
};

extern FText GetMyEnumCustomDisplayName(int32 val);


UENUM(Blueprintable,BlueprintType)
enum class EMyEnum_Spacer_Hidden :uint8
{
	MyNormal,
	MySpacer UMETA(Spacer),
	MyHidden UMETA(Hidden),
};



UCLASS(BlueprintType)
class INSIDER_API UMyEnum_Test :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	EMyEnum_HasDisplayName MyEnum_HasDisplayName;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	EMyEnum_Spacer_Hidden MyEnum_Spacer_Hidden;
};