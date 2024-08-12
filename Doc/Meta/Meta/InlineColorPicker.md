# InlineColorPicker

Usage: UPROPERTY
Feature: Editor
Type: bool
Description: 使FColor或FLinearColor属性在编辑的时候直接内联一个颜色选择器。
LimitedType: FColor , FLinearColor 
Status: Done
Group: Numeric Property

使FColor或FLinearColor属性在编辑的时候直接内联一个颜色选择器。

测试代码：

```cpp
public:
	UPROPERTY(EditAnywhere, Category = ColorPicker, meta = (InlineColorPicker))
	FColor MyColor_InlineColorPicker;
	UPROPERTY(EditAnywhere, Category = ColorPicker, meta = (InlineColorPicker))
	FLinearColor MyLinearColor_InlineColorPicker;
```

测试结果：

![Untitled](InlineColorPicker/Untitled.png)

原理：

根据不同的标记创建不同的的ColorWidget 。

```cpp

void FColorStructCustomization::MakeHeaderRow(TSharedRef<class IPropertyHandle>& InStructPropertyHandle, FDetailWidgetRow& Row)
{
	if (InStructPropertyHandle->HasMetaData("InlineColorPicker"))
	{
		ColorWidget = CreateInlineColorPicker(StructWeakHandlePtr);
		ContentWidth = 384.0f;
	}
	else
	{
		ColorWidget = CreateColorWidget(StructWeakHandlePtr);
	}
}
```