// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Units/RigUnit.h"
#include "Common/CommonTypes.h"
#include "MyRig_Test.generated.h"



USTRUCT(meta = (DisplayName = "MyRig"))
struct INSIDER_API FRigUnit_MyRig : public FRigUnit
{
	GENERATED_BODY()

	FRigUnit_MyRig()
	{
	}
	RIGVM_METHOD()
		virtual void Execute() override;

public:
	UPROPERTY(meta = (Output))
	float MyFloat_Output = 123.f;
public:
	/*UPROPERTY()
	float MyFloat_Normal = 123.f;

	UPROPERTY(meta = (Input))
	float MyFloat_Input = 123.f;

	UPROPERTY(meta = (Output))
	float MyFloat_Output = 123.f;

	UPROPERTY(meta = (Input, Output))
	float MyFloat_IO = 123.f;

	UPROPERTY(meta = (Hidden))
	float MyFloat_Hidden = 123.f;

	UPROPERTY(meta = (Visible))
	float MyFloat_Visible = 123.f;

	UPROPERTY(meta = (Input, Constant))
	float MyFloat_Constant = 123.f;

	UPROPERTY(meta = (Input, DetailsOnly))
	float MyFloat_DetailsOnly = 456.f;*/
public:
	/*UPROPERTY(meta = (Input))
	TArray<float> MyArray_Normal;

	UPROPERTY(meta = (Input, ExpandByDefault,DefaultArraySize = 1))
	TArray<float> MyArray_DefaultSize;*/

	/*UPROPERTY(meta = (Input))
	TArray<float> MyArray_Normal;*/

	//UPROPERTY(meta = (Input, ExpandByDefault,DefaultArraySize = 1))
	//TArray<float> MyArray_DefaultSize;
public:

	UPROPERTY(meta = (Input))
	FMyCommonStruct MyStruct_Normal;

	UPROPERTY(meta = (Input, ExpandByDefault))
	FMyCommonStruct MyStruct_ExpandByDefault;
};


USTRUCT(meta = (DisplayName = "MyRigConstant", Constant))	//Constant not found usage
struct INSIDER_API FRigUnit_MyRigConstant : public FRigUnit
{
	GENERATED_BODY()

	RIGVM_METHOD()
		virtual void Execute() override;
public:
	UPROPERTY(meta = (Input))
	float MyFloat_Input = 123.f;

	UPROPERTY(meta = (Output))
	float MyFloat_Output = 123.f;
};

USTRUCT(meta = (DisplayName = "MyRigDeprecated", Deprecated))
struct INSIDER_API FRigUnit_MyRigDeprecated : public FRigUnit
{
	GENERATED_BODY()

	RIGVM_METHOD()
		virtual void Execute() override;

	RIGVM_METHOD()
		virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;
public:
	UPROPERTY(meta = (Input))
	float MyFloat_Input = 123.f;

	UPROPERTY(meta = (Output))
	float MyFloat_Output = 123.f;
};


USTRUCT(meta = (DisplayName = "MyRigAbstract", Abstract))
struct INSIDER_API FRigUnit_MyRigAbstract : public FRigUnit
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (Input))
	float MyFloat_Input = 123.f;

	UPROPERTY(meta = (Output))
	float MyFloat_Output = 123.f;
};

USTRUCT(meta = (DisplayName = "MyRigSuffix", MenuDescSuffix = "(MyVector)"))
struct INSIDER_API FRigUnit_MyRigSuffix : public FRigUnit
{
	GENERATED_BODY()

	RIGVM_METHOD()
		virtual void Execute() override;
public:
	UPROPERTY(meta = (Input))
	float MyFloat_Input = 123.f;

	UPROPERTY(meta = (Output))
	float MyFloat_Output = 123.f;
};

USTRUCT(meta = (DisplayName = "MyRigColor", NodeColor = "1 0 0"))
struct INSIDER_API FRigUnit_MyRigColor : public FRigUnit
{
	GENERATED_BODY()

	RIGVM_METHOD()
		virtual void Execute() override;
public:
	UPROPERTY(meta = (Input))
	float MyFloat_Input = 123.f;

	UPROPERTY(meta = (Output))
	float MyFloat_Output = 123.f;
};


USTRUCT(meta = (DisplayName = "MyRigIcon", Icon = "EditorStyle|GraphEditor.Macro.ForEach_16x"))
struct INSIDER_API FRigUnit_MyRigIcon : public FRigUnit
{
	GENERATED_BODY()

	RIGVM_METHOD()
		virtual void Execute() override;
public:
	UPROPERTY(meta = (Input))
	float MyFloat_Input = 123.f;

	UPROPERTY(meta = (Output))
	float MyFloat_Output = 123.f;
};

USTRUCT(meta = (DisplayName = "MyRigKeywords", Keywords = "MyKey,OtherWord"))
struct INSIDER_API FRigUnit_MyRigKeywords : public FRigUnit
{
	GENERATED_BODY()

	RIGVM_METHOD()
		virtual void Execute() override;
public:
	UPROPERTY(meta = (Input))
	float MyFloat_Input = 123.f;

	UPROPERTY(meta = (Output))
	float MyFloat_Output = 123.f;
};


USTRUCT(meta = (DisplayName = "MyRigAggregate"))
struct INSIDER_API FRigUnit_MyRigAggregate : public FRigUnit
{
	GENERATED_BODY()

	RIGVM_METHOD()
		virtual void Execute() override;
public:
	UPROPERTY(meta = (Input, Aggregate))
	float A = 0.f;

	UPROPERTY(meta = (Input, Aggregate))
	float B = 0.f;

	UPROPERTY(meta = (Output, Aggregate))
	float Result = 0.f;
};

UENUM(BlueprintType)
enum class ERigMyEnum : uint8
{
	First,
	Second,
	Third,
};

UENUM(BlueprintType, meta = (RigVMTypeAllowed))
enum class ERigMyEnumAllowed : uint8
{
	Cat,
	Dog,
	Tiger,
};


USTRUCT(meta = (DisplayName = "MyRigEnum"))
struct INSIDER_API FRigUnit_MyRigEnum : public FRigUnit
{
	GENERATED_BODY()

	RIGVM_METHOD()
		virtual void Execute() override;
public:
	UPROPERTY(meta = (Input))
	UEnum* MyEnum=nullptr;

	UPROPERTY(meta = (Output))
	float MyFloat_Output = 123.f;
};