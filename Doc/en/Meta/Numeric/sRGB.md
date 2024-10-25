# sRGB

- **Function Description:** Ensures that FColor or FLinearColor attributes utilize the sRGB color space during editing.
- **Usage Location:** UPROPERTY
- **Engine Module:** Numeric Property
- **Metadata Type:** bool
- **Restricted Types:** FColor, FLinearColor

Enables the FColor or FLinearColor property to use the sRGB color space when being edited.

However, it does not function as expected during testing.

## Principle:

```cpp
void FColorStructCustomization::CustomizeHeader(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{

	if (StructPropertyHandle->GetProperty()->HasMetaData(TEXT("sRGB")))
	{
		sRGBOverride = StructPropertyHandle->GetProperty()->GetBoolMetaData(TEXT("sRGB"));
	}

}

```