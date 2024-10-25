# sRGB

- **功能描述：** 使FColor或FLinearColor属性在编辑的时候采用sRGB方式。
- **使用位置：** UPROPERTY
- **引擎模块：** Numeric Property
- **元数据类型：** bool
- **限制类型：** FColor , FLinearColor

使FColor或FLinearColor属性在编辑的时候采用sRGB方式。

但是在测试的时候并无法工作。

## 原理：

```cpp
void FColorStructCustomization::CustomizeHeader(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{

	if (StructPropertyHandle->GetProperty()->HasMetaData(TEXT("sRGB")))
	{
		sRGBOverride = StructPropertyHandle->GetProperty()->GetBoolMetaData(TEXT("sRGB"));
	}

}

```