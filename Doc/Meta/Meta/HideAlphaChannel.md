# HideAlphaChannel

Usage: UPROPERTY
Feature: Editor
Type: bool
Description: 使FColor或FLinearColor属性在编辑的时候隐藏Alpha通道。
LimitedType: FColor , FLinearColor 
Status: Done
Group: Numeric Property

使FColor或FLinearColor属性在编辑的时候隐藏Alpha通道。

测试代码：

```cpp
public:
	UPROPERTY(EditAnywhere, Category = AlphaTest)
	FColor MyColor;

	UPROPERTY(EditAnywhere, Category = AlphaTest, meta = (HideAlphaChannel))
	FColor MyColor_HideAlphaChannel;

	UPROPERTY(EditAnywhere, Category = AlphaTest)
	FLinearColor MyLinearColor;

	UPROPERTY(EditAnywhere, Category = AlphaTest, meta = (HideAlphaChannel))
	FLinearColor MyLinearColor_HideAlphaChannel;
```

测试结果：

可见带有HideAlphaChannel的属性就没有了Alpha通道。

![Untitled](HideAlphaChannel/Untitled.png)

原理：

```cpp
void FColorStructCustomization::CustomizeHeader(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	bIgnoreAlpha = TypeSupportsAlpha() == false || StructPropertyHandle->GetProperty()->HasMetaData(TEXT("HideAlphaChannel"));
}

.AlphaDisplayMode(bIgnoreAlpha ? EColorBlockAlphaDisplayMode::Ignore : EColorBlockAlphaDisplayMode::Separate)

```