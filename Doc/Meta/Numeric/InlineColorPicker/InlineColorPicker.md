# InlineColorPicker

功能描述: 使FColor或FLinearColor属性在编辑的时候直接内联一个颜色选择器。
使用位置: UPROPERTY
Feature: Editor
引擎模块: Numeric Property
元数据类型: bool
限制类型: FColor , FLinearColor 
Status: Done
常用程度: 2

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