// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProperty_Numeric.generated.h"

UCLASS(BlueprintType)
class INSIDER_API UMyProperty_Numeric :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpinBoxTest)
	int32 MyInt = 123;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpinBoxTest, meta = (NoSpinbox = true))
	int32 MyInt_NoSpinbox = 123;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpinBoxTest)
	float MyFloat = 123;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpinBoxTest, meta = (NoSpinbox = true))
	float MyFloat_NoSpinbox = 123;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MultipleTest)
	int32 MyInt_NoMultiple = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MultipleTest, meta = (Multiple = 5))
	int32 MyInt_HasMultiple = 100;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ArrayClampTest)
	int32 MyInt_NoArrayClamp = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ArrayClampTest, meta = (ArrayClamp = "MyIntArray"))
	int32 MyInt_HasArrayClamp = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ArrayClampTest)
	TArray<int32> MyIntArray;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MinMaxTest)
	float MyFloat_NoMinMax = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MinMaxTest, meta = (UIMin = "0", UIMax = "100"))
	float MyFloat_HasMinMax_UI = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MinMaxTest, meta = (ClampMin = "0", ClampMax = "100"))
	float MyFloat_HasMinMax_Clamp = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MinMaxTest, meta = (ClampMin = "0", ClampMax = "100", UIMin = "20", UIMax = "50"))
	float MyFloat_HasMinMax_ClampAndUI = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MinMaxTest, meta = (ClampMin = "20", ClampMax = "50", UIMin = "0", UIMax = "100"))
	float MyFloat_HasMinMax_ClampAndUI2 = 100;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SliderTest, meta = (UIMin = "0", UIMax = "1000"))
	float MyFloat_DefaultSliderExponent = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SliderTest, meta = (UIMin = "0", UIMax = "1000", SliderExponent = 5))
	float MyFloat_HasSliderExponent = 100;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WheelStepTest)
	float MyFloat_DefaultWheelStep = 50;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WheelStepTest, meta = (UIMin = "0", UIMax = "10"))
	float MyFloat_SmallWheelStep = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WheelStepTest, meta = (WheelStep = 10))
	float MyFloat_HasWheelStep = 50;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DeltaTest)
	float MyFloat_DefaultDelta = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DeltaTest, meta = (Delta = 10))
	float MyFloat_Delta10 = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DeltaTest, meta = (UIMin = "0", UIMax = "1000", Delta = 10))
	float MyFloat_Delta10_UIMinMax = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DeltaTest, meta = (Delta = 10, LinearDeltaSensitivity = 50))
	float MyFloat_Delta10_LinearDeltaSensitivity50 = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DeltaTest, meta = (UIMin = "0", UIMax = "1000", Delta = 10, LinearDeltaSensitivity = 50))
	float MyFloat_Delta10_LinearDeltaSensitivity50_UIMinMax = 100;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MultiplierTest, meta = (CtrlMultiplier = "5"))
	float MyFloat_HasCtrlMultiplier = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MultiplierTest, meta = (ShiftMultiplier = "100"))
	float MyFloat_HasShiftMultiplier = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MultiplierTest)
	FVector MyVector_NoMultiplier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MultiplierTest, meta = (CtrlMultiplier = "5"))
	FVector MyVector_HasCtrlMultiplier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MultiplierTest, meta = (ShiftMultiplier = "100"))
	FVector MyVector_HasShiftMultiplier;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DynamicSliderTest, meta = (UIMin = "0", UIMax = "1"))
	FVector4 MyVector4_NoDynamicSlider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DynamicSliderTest, meta = (UIMin = "0", UIMax = "1", SupportDynamicSliderMinValue = "true", SupportDynamicSliderMaxValue = "true"))
	FVector4 MyVector4_SupportDynamicSlider;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ColorGradingModeTest, meta = ())
	FVector4 MyVector4_NotColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ColorGradingModeTest, meta = (UIMin = "0", UIMax = "1", ColorGradingMode = "saturation"))
	FVector4 MyVector4_Saturation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ColorGradingModeTest, meta = (UIMin = "0", UIMax = "1", ColorGradingMode = "contrast"))
	FVector4 MyVector4_Contrast;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ColorGradingModeTest, meta = (UIMin = "0", UIMax = "1", ColorGradingMode = "gamma"))
	FVector4 MyVector4_Gamma;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ColorGradingModeTest, meta = (UIMin = "0", UIMax = "1", ColorGradingMode = "gain"))
	FVector4 MyVector4_Gain;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ColorGradingModeTest, meta = (UIMin = "0", UIMax = "1", ColorGradingMode = "offset"))
	FVector4 MyVector4_Offset;

public:

	UPROPERTY(EditAnywhere, Category = UnitsTest)
	float MyFloat_NoUnits = 0.0;

	UPROPERTY(EditAnywhere, Category = UnitsTest, Meta = (Units = "cm"))
	float MyFloat_HasUnits_Distance = 100.f;

	UPROPERTY(EditAnywhere, Category = UnitsTest, Meta = (ForceUnits = "cm"))
	float MyFloat_HasForceUnits_Distance = 100.f;

public:
	UPROPERTY(EditAnywhere, Category = AlphaTest)
	FColor MyColor;

	UPROPERTY(EditAnywhere, Category = AlphaTest, meta = (HideAlphaChannel))
	FColor MyColor_HideAlphaChannel;

	UPROPERTY(EditAnywhere, Category = AlphaTest)
	FLinearColor MyLinearColor;

	UPROPERTY(EditAnywhere, Category = AlphaTest, meta = (HideAlphaChannel))
	FLinearColor MyLinearColor_HideAlphaChannel;
public://sRGB Not worked

	//UPROPERTY(EditAnywhere, Category = sRGBTest, meta = (sRGB = "true"))
	//FColor MyColor_sRGB;

	//UPROPERTY(EditAnywhere, Category = sRGBTest, meta = (sRGB = "true"))
	//FLinearColor MyLinearColor_sRGB;

	//UPROPERTY(EditAnywhere, Category = sRGBTest, meta = (sRGB = "false"))
	//FColor MyColor_NosRGB;

	//UPROPERTY(EditAnywhere, Category = sRGBTest, meta = (sRGB = "false"))
	//FLinearColor MyLinearColor_NosRGB;
public:
	UPROPERTY(EditAnywhere, Category = ColorPicker, meta = (InlineColorPicker))
	FColor MyColor_InlineColorPicker;
	UPROPERTY(EditAnywhere, Category = ColorPicker, meta = (InlineColorPicker))
	FLinearColor MyLinearColor_InlineColorPicker;
public:
	UPROPERTY(EditAnywhere, Category = VectorTest)
	FVector MyVector_Default;

	UPROPERTY(EditAnywhere, Category = VectorTest, meta = (AllowPreserveRatio))
	FVector MyVector_AllowPreserveRatio;

	UPROPERTY(EditAnywhere, Category = VectorTest, meta = (ShowNormalize))
	FVector MyVector_ShowNormalize;
};

