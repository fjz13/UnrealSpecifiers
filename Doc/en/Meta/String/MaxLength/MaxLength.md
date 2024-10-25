# MaxLength

- **Function Description:** Limits the maximum length of text within a text edit box
- **Usage Location:** UPROPERTY
- **Engine Module:** String/Text Property
- **Metadata Type:** int32
- **Restriction Type:** FName/FString/Fext
- **Commonality:** ★★★★★

Enforces a maximum length for text within a text edit box. However, it is still possible to input any value freely at the C++ or blueprint level.

## Test Code:

```cpp
	UPROPERTY(EditAnywhere, Category = MaxLengthTest, meta = (MaxLength = 10))
	FString MyString_MaxLength10 = TEXT("Hello");
```

## Test Code:

![Untitled](Untitled.png)

## 测试效果:

When the string in the text box is modified, the current length is checked, and an error is reported if it exceeds the limit.

For FName attributes, MaxLength is further restricted to within NAME_SIZE (1024).

```cpp
MaxLength = PropertyHandle->GetIntMetaData(NAME_MaxLength);
if (InPropertyEditor->PropertyIsA(FNameProperty::StaticClass()))
{
	MaxLength = MaxLength <= 0 ? NAME_SIZE - 1 : FMath::Min(MaxLength, NAME_SIZE - 1);
}

bool SPropertyEditorText::OnVerifyTextChanged(const FText& Text, FText& OutError)
{
		const FString& TextString = Text.ToString();

		if (MaxLength > 0 && TextString.Len() > MaxLength)
		{
			OutError = FText::Format(LOCTEXT("PropertyTextTooLongError", "This value is too long ({0}/{1} characters)"), TextString.Len(), MaxLength);
			return false;
		}
	}
```