# MaxLength

Usage: UPROPERTY
Feature: Editor
Type: int32
Description: 在文本编辑框里限制文本的最大长度
LimitedType: FName/FString/Fext
Status: Done
Group: String/Text Property

在文本编辑框里限制文本的最大长度。但在C++或蓝图层面还是可以自己任意写入值的。

测试代码：

```cpp
	UPROPERTY(EditAnywhere, Category = MaxLengthTest, meta = (MaxLength = 10))
	FString MyString_MaxLength10 = TEXT("Hello");
```

测试效果：

![Untitled](MaxLength/Untitled.png)

原理：

在文本框里字符串改变的时候，检查当前的长度，超过则报错。

如果是FName属性，则会把MaxLength 继续限制在NAME_SIZE (1024)以内。

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