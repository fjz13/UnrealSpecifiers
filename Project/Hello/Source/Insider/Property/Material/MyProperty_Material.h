// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProperty_Material.generated.h"

UCLASS()
class UMyProperty_MyMaterialExpression : public UMaterialExpression
{
	GENERATED_UCLASS_BODY()
public:
	UPROPERTY()
	FExpressionInput MyInput_Default;

	UPROPERTY(meta = (RequiredInput = "true"))
	FExpressionInput MyInput_Required;

	UPROPERTY(meta = (RequiredInput = "false"))
	FExpressionInput MyInput_NotRequired;
public:
	UPROPERTY(EditAnywhere, Category = OverridingInputProperty, meta = (RequiredInput = "false"))
	FExpressionInput MyAlpha;

	/** only used if MyAlpha is not hooked up */
	UPROPERTY(EditAnywhere, Category = OverridingInputProperty, meta = (OverridingInputProperty = "MyAlpha"))
	float ConstAlpha = 1.f;

	UPROPERTY(EditAnywhere, Category = OverridingInputProperty, meta = (RequiredInput = "true"))
	FExpressionInput MyAlpha2;

	/** only used if MyAlpha is not hooked up */
	UPROPERTY(EditAnywhere, Category = OverridingInputProperty, meta = (OverridingInputProperty = "MyAlpha2"))
	float ConstAlpha2 = 1.f;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PinTest)
	float MyFloat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PinTest, meta = (ShowAsInputPin = "Primary"))
	float MyFloat_Primary;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PinTest, meta = (ShowAsInputPin = "Advanced"))
	float MyFloat_Advanced;
public:

	//~ Begin UMaterialExpression Interface
#if WITH_EDITOR
	virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;
	virtual void GetCaption(TArray<FString>& OutCaptions) const override;

	virtual bool GenerateHLSLExpression(FMaterialHLSLGenerator& Generator, UE::HLSLTree::FScope& Scope, int32 OutputIndex, UE::HLSLTree::FExpression const*& OutExpression) const override;
#endif
	//~ End UMaterialExpression Interface
};

