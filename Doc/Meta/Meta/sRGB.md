# sRGB

Usage: UPROPERTY
Feature: Editor
Type: bool
Description: 使FColor或FLinearColor属性在编辑的时候采用sRGB方式。
LimitedType: FColor , FLinearColor 
Status: NotWorked
Group: Numeric Property

使FColor或FLinearColor属性在编辑的时候采用sRGB方式。

但是在测试的时候并无法工作。

原理：

```cpp
void FColorStructCustomization::CustomizeHeader(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{

	if (StructPropertyHandle->GetProperty()->HasMetaData(TEXT("sRGB")))
	{
		sRGBOverride = StructPropertyHandle->GetProperty()->GetBoolMetaData(TEXT("sRGB"));
	}

}

```