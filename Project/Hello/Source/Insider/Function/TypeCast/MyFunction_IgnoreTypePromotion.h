// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyFunction_IgnoreTypePromotion.generated.h"


USTRUCT(BlueprintType)
struct FGameProp
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double HP=0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double Attack=0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double Defense=0.f;
};


USTRUCT(BlueprintType)
struct FGameProp2
{
	GENERATED_BODY()
public:
	FGameProp2() = default;
	FGameProp2(double HP, double Attack, double Defense) {}
	FGameProp2(double a){}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double HP=0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double Attack=0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double Defense=0.f;
};

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyFunction_IgnoreTypePromotion :public UBlueprintFunctionLibrary
{
public:
	GENERATED_BODY()
public:
	/** Makes a GameProp struct */
	UFUNCTION(BlueprintPure, Category = "Math|GameProp", meta = (IgnoreTypePromotion, NativeMakeFunc))
	static FGameProp MakeGameProp(double HP, double Attack, double Defense) { return FGameProp(); }

	/** Breaks a GameProp into its components */
	UFUNCTION(BlueprintPure, Category = "Math|GameProp", meta = (IgnoreTypePromotion, NativeBreakFunc))
	static void BreakGameProp(FGameProp InGameProp, double& HP, double& Attack, double& Defense) {}

	/** Addition (A + B) */
	UFUNCTION(BlueprintPure, meta = (IgnoreTypePromotion, DisplayName = "GameProp + GameProp", CompactNodeTitle = "+", Keywords = "+ add plus"), Category = "Math|GameProp")
	static FGameProp Add_GameProp(FGameProp A, FGameProp B);

	/** Subtraction (A - B) */
	UFUNCTION(BlueprintPure, meta = (IgnoreTypePromotion, DisplayName = "GameProp - GameProp", CompactNodeTitle = "-", Keywords = "- subtract minus"), Category = "Math|GameProp")
	static FGameProp Subtract_GameProp(FGameProp A, FGameProp B) { return FGameProp(); }

	/** Returns true if the values are equal (A == B) */
	UFUNCTION(BlueprintPure, meta = (IgnoreTypePromotion, DisplayName = "Equal (GameProp)", CompactNodeTitle = "==", Keywords = "== equal"), Category = "Math|GameProp")
	static bool EqualEqual_GameProp(FGameProp A, FGameProp B) { return true; }

	/** Returns true if the values are not equal (A != B) */
	UFUNCTION(BlueprintPure, meta = (IgnoreTypePromotion, DisplayName = "Not Equal (GameProp)", CompactNodeTitle = "!=", Keywords = "!= not equal"), Category = "Math|GameProp")
	static bool NotEqual_GameProp(FGameProp A, FGameProp B) { return true; }

	/** Returns true if A is greater than B (A > B) */
	UFUNCTION(BlueprintPure, meta = (IgnoreTypePromotion, DisplayName = "GameProp > GameProp", CompactNodeTitle = ">", Keywords = "> greater"), Category = "Math|GameProp")
	static bool Greater_GameProp(FGameProp A, FGameProp B) { return true; }

	/** Returns true if A is greater than or equal to B (A >= B) */
	UFUNCTION(BlueprintPure, meta = (IgnoreTypePromotion, DisplayName = "GameProp >= GameProp", CompactNodeTitle = ">=", Keywords = ">= greater"), Category = "Math|GameProp")
	static bool GreaterEqual_GameProp(FGameProp A, FGameProp B) { return true; }

	/** Returns true if A is less than B (A < B) */
	UFUNCTION(BlueprintPure, meta = (IgnoreTypePromotion, DisplayName = "GameProp < GameProp", CompactNodeTitle = "<", Keywords = "< less"), Category = "Math|GameProp")
	static bool Less_GameProp(FGameProp A, FGameProp B) { return true; }

	/** Returns true if A is less than or equal to B (A <= B) */
	UFUNCTION(BlueprintPure, meta = (IgnoreTypePromotion, DisplayName = "GameProp <= GameProp", CompactNodeTitle = "<=", Keywords = "<= less"), Category = "Math|GameProp")
	static bool LessEqual_GameProp(FGameProp A, FGameProp B) { return true; }

public:
	/** Makes a GameProp2 struct */
	UFUNCTION(BlueprintPure, Category = "Math|GameProp2", meta = (NativeMakeFunc))
	static FGameProp2 MakeGameProp2(double HP, double Attack, double Defense) { return FGameProp2(); }

	/** Breaks a GameProp2 into its components */
	UFUNCTION(BlueprintPure, Category = "Math|GameProp2", meta = (NativeBreakFunc))
	static void BreakGameProp2(FGameProp2 InGameProp2, double& HP, double& Attack, double& Defense) {}

	/** Addition (A + B) */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "GameProp2 + GameProp2", CompactNodeTitle = "+", Keywords = "+ add plus"), Category = "Math|GameProp2")
	static FGameProp2 Add_GameProp2(FGameProp2 A, FGameProp2 B);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "GameProp2 + double", CompactNodeTitle = "+", Keywords = "+ add plus"), Category = "Math|GameProp2")
	static FGameProp2 Add_GameProp2_double(FGameProp2 A, double B) { return FGameProp2(); }

	/** Subtraction (A - B) */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "GameProp2 - GameProp2", CompactNodeTitle = "-", Keywords = "- subtract minus"), Category = "Math|GameProp2")
	static FGameProp2 Subtract_GameProp2(FGameProp2 A, FGameProp2 B) { return FGameProp2(); }

	/** Returns true if the values are equal (A == B) */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (GameProp2)", CompactNodeTitle = "==", Keywords = "== equal"), Category = "Math|GameProp2")
	static bool EqualEqual_GameProp2(FGameProp2 A, FGameProp2 B) { return true; }

	/** Returns true if the values are not equal (A != B) */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Not Equal (GameProp2)", CompactNodeTitle = "!=", Keywords = "!= not equal"), Category = "Math|GameProp2")
	static bool NotEqual_GameProp2(FGameProp2 A, FGameProp2 B) { return true; }

	/** Returns true if A is greater than B (A > B) */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "GameProp2 > GameProp2", CompactNodeTitle = ">", Keywords = "> greater"), Category = "Math|GameProp2")
	static bool Greater_GameProp2(FGameProp2 A, FGameProp2 B) { return true; }

	/** Returns true if A is greater than or equal to B (A >= B) */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "GameProp2 >= GameProp2", CompactNodeTitle = ">=", Keywords = ">= greater"), Category = "Math|GameProp2")
	static bool GreaterEqual_GameProp2(FGameProp2 A, FGameProp2 B) { return true; }

	/** Returns true if A is less than B (A < B) */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "GameProp2 < GameProp2", CompactNodeTitle = "<", Keywords = "< less"), Category = "Math|GameProp2")
	static bool Less_GameProp2(FGameProp2 A, FGameProp2 B) { return true; }

	/** Returns true if A is less than or equal to B (A <= B) */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "GameProp2 <= GameProp2", CompactNodeTitle = "<=", Keywords = "<= less"), Category = "Math|GameProp2")
	static bool LessEqual_GameProp2(FGameProp2 A, FGameProp2 B) { return true; }
};


