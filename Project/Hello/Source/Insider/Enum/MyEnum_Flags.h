// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyEnum_Flags.generated.h"

/*
[enum aa7ffe06680 EMyEnum_Normal	Enum->Field->Object	/Script/Insider.EMyEnum_Normal]
(BlueprintType = true, First.Name = EMyEnum_Normal::First, ModuleRelativePath = Enum/MyEnum_Flags.h, Second.Name = EMyEnum_Normal::Second, Third.Name = EMyEnum_Normal::Third)
	ObjectFlags:	RF_Public | RF_Transient
	Outer:	Package /Script/Insider
	EnumFlags:	None
	EnumDisplayNameFn:	0
	CppType:	EMyEnum_Normal
	CppForm:	EnumClass
{
	First = 0,
	Second = 1,
	Third = 2,
	EMyEnum_MAX = 3
};
*/
UENUM(BlueprintType)
enum class EMyEnum_Normal :uint8
{
	First,
	Second,
	Third,
};



/*
[EMyEnum_Flags	Enum->Field->Object	/Script/Insider.EMyEnum_Flags]
(BlueprintType = true, First.Name = EMyEnum_Flags::First, ModuleRelativePath = Enum/MyEnum_Flags.h, Second.Name = EMyEnum_Flags::Second, Third.Name = EMyEnum_Flags::Third)
	ObjectFlags:	RF_Public | RF_Transient
	Outer:	Package /Script/Insider
	EnumFlags:	EEnumFlags::Flags
	EnumDisplayNameFn:	0
	CppType:	EMyEnum_Flags
	CppForm:	EnumClass
{
	First = 0,
	Second = 1,
	Third = 2,
	EMyEnum_MAX = 3
};
*/
UENUM(BlueprintType, Flags)
enum class EMyEnum_Flags :uint8
{
	First,
	Second,
	Third,
};



/*
[EMyEnum_BitFlags	Enum->Field->Object	/Script/Insider.EMyEnum_BitFlags]
(Bitflags = , BlueprintType = true, First.Name = EMyEnum_BitFlags::First, ModuleRelativePath = Enum/MyEnum_Flags.h, Second.Name = EMyEnum_BitFlags::Second, Third.Name = EMyEnum_BitFlags::Third)
	ObjectFlags:	RF_Public | RF_Transient
	Outer:	Package /Script/Insider
	EnumFlags:	EEnumFlags::None
	EnumDisplayNameFn:	0
	CppType:	EMyEnum_BitFlags
	CppForm:	EnumClass
{
	First = 0,
	Second = 1,
	Third = 2,
	EMyEnum_MAX = 3
};
*/
UENUM(BlueprintType, Meta = (Bitflags))
enum class EMyEnum_BitFlags :uint8
{
	First,//0
	Second,//1
	Third,//2
};

//(Bitflags = , BlueprintType = true, First.Name = EMyEnum_BitFlagsInEditor::First, ModuleRelativePath = Enum/MyEnum_Flags.h, Second.Name = EMyEnum_BitFlagsInEditor::Second, Third.Name = EMyEnum_BitFlagsInEditor::Third, 
//UseEnumValuesAsMaskValuesInEditor = true)
UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EMyEnum_BitFlagsInEditor :uint8
{
	First,//0
	Second,//1
	Third,//2
};


UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyActor_EnumBitFlags_Test :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Test")
	EMyEnum_Normal MyEnum_Normal;
	UPROPERTY(EditAnywhere, Category = "Test")
	EMyEnum_Flags MyEnum_Flags;
	UPROPERTY(EditAnywhere, Category = "Test")
	EMyEnum_BitFlags MyEnum_BitFlags;
public:

	UPROPERTY(EditAnywhere, Category = "Bitmask", Meta = (Bitmask))
	int32 MyNormalWithoutEnum;

	UPROPERTY(EditAnywhere, Category = "Bitmask", Meta = (Bitmask, BitmaskEnum = "/Script/Insider.EMyEnum_Normal"))
	int32 MyNormal;

	UPROPERTY(EditAnywhere, Category = "Bitmask", Meta = (Bitmask, BitmaskEnum = "/Script/Insider.EMyEnum_Flags"))
	int32 MyFlags;

	UPROPERTY(EditAnywhere, Category = "Bitmask", Meta = (Bitmask, BitmaskEnum = "/Script/Insider.EMyEnum_BitFlags"))
	int32 MyBitFlags;
public:
	UPROPERTY(EditAnywhere, Category = "UseEnumValuesAsMaskValuesInEditor")
	EMyEnum_BitFlagsInEditor MyBitFlagsInEditor;

public:
	static void TestFlags();
};


