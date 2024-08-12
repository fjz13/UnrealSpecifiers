# sRGB

Description: 使FColor或FLinearColor属性在编辑的时候采用sRGB方式。
Usage: UPROPERTY
Feature: Editor
Group: Numeric Property
Type: bool
LimitedType: FColor , FLinearColor 
Status: NotWorked

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