# InlineColorPicker

- **Function Description:** Allows direct inline editing of FColor or FLinearColor properties with a color picker during the editing process.
- **Usage Location:** UPROPERTY
- **Engine Module:** Numeric Property
- **Metadata Type:** boolean
- **Restricted Types:** FColor, FLinearColor
- **Commonly Used:** ★★

Enables direct inline editing of FColor or FLinearColor properties with a color picker during the editing process.

## Test Code:

```cpp
public:
	UPROPERTY(EditAnywhere, Category = ColorPicker, meta = (InlineColorPicker))
	FColor MyColor_InlineColorPicker;
	UPROPERTY(EditAnywhere, Category = ColorPicker, meta = (InlineColorPicker))
	FLinearColor MyLinearColor_InlineColorPicker;
```

## Test Results:

![Untitled](Untitled.png)

## Principle:

creates different ColorWidgets based on various tags.

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