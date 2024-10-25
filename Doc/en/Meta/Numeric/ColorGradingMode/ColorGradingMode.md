# ColorGradingMode

- **Function Description:** Enables an FVector4 attribute to be displayed as a color
- **Usage Location:** UPROPERTY
- **Engine Module:** Numeric Property
- **Metadata Type:** string = "abc"
- **Restriction Type:** FVector4
- **Commonality:** ★★

Enables an FVector4 attribute to be displayed as a color. As FVector4 aligns perfectly with RGBA.

Must be used in conjunction with UIMin and UIMax to avoid crashes, because FColorGradingVectorCustomization directly accesses the UIMinValue.

## Test Code:

```cpp
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ColorGradingModeTest, meta = ())
	FVector4 MyVector4_NotColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ColorGradingModeTest, meta = (UIMin = "0", UIMax = "1",ColorGradingMode = "saturation"))
	FVector4 MyVector4_Saturation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ColorGradingModeTest, meta = (UIMin = "0", UIMax = "1",ColorGradingMode = "contrast"))
	FVector4 MyVector4_Contrast;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ColorGradingModeTest, meta = (UIMin = "0", UIMax = "1",ColorGradingMode = "gamma"))
	FVector4 MyVector4_Gamma;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ColorGradingModeTest, meta = (UIMin = "0", UIMax = "1",ColorGradingMode = "gain"))
	FVector4 MyVector4_Gain;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ColorGradingModeTest, meta = (UIMin = "0", UIMax = "1",ColorGradingMode = "offset"))
	FVector4 MyVector4_Offset;
```

## Test Results:

It can be observed that without ColorGradingMode, it remains a standard FVector4; otherwise, a color wheel is used for display and editing.

![Untitled](Untitled.png)

## Principle:

If the attribute is FVector4, and there is a ColorGradingMode, create FColorGradingVectorCustomization to customize the FVector for color display. Then, determine the EColorGradingModes based on the string, and ultimately create the corresponding specific UI control.

```cpp
void FVector4StructCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	FProperty* Property = StructPropertyHandle->GetProperty();
	if (Property)
	{
		const FString& ColorGradingModeString = Property->GetMetaData(TEXT("ColorGradingMode"));
		if (!ColorGradingModeString.IsEmpty())
		{
			//Create our color grading customization shared pointer
			TSharedPtr<FColorGradingVectorCustomization> ColorGradingCustomization = GetOrCreateColorGradingVectorCustomization(StructPropertyHandle);

			//Customize the childrens
			ColorGradingVectorCustomization->CustomizeChildren(StructBuilder, StructCustomizationUtils);

			// We handle the customize Children so just return here
			return;
		}
	}

	//Use the base class customize children
	FMathStructCustomization::CustomizeChildren(StructPropertyHandle, StructBuilder, StructCustomizationUtils);
}

EColorGradingModes FColorGradingVectorCustomizationBase::GetColorGradingMode() const
{
	EColorGradingModes ColorGradingMode = EColorGradingModes::Invalid;

	if (ColorGradingPropertyHandle.IsValid())
	{
		//Query all meta data we need
		FProperty* Property = ColorGradingPropertyHandle.Pin()->GetProperty();
		const FString& ColorGradingModeString = Property->GetMetaData(TEXT("ColorGradingMode"));

		if (ColorGradingModeString.Len() > 0)
		{
			if (ColorGradingModeString.Compare(TEXT("saturation")) == 0)
			{
				ColorGradingMode = EColorGradingModes::Saturation;
			}
			else if (ColorGradingModeString.Compare(TEXT("contrast")) == 0)
			{
				ColorGradingMode = EColorGradingModes::Contrast;
			}
			else if (ColorGradingModeString.Compare(TEXT("gamma")) == 0)
			{
				ColorGradingMode = EColorGradingModes::Gamma;
			}
			else if (ColorGradingModeString.Compare(TEXT("gain")) == 0)
			{
				ColorGradingMode = EColorGradingModes::Gain;
			}
			else if (ColorGradingModeString.Compare(TEXT("offset")) == 0)
			{
				ColorGradingMode = EColorGradingModes::Offset;
			}
		}
	}

	return ColorGradingMode;
}
```