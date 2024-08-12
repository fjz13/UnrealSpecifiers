# AllowedCharacters

Description: 只允许文本框里可以输入这些字符。
Usage: UPROPERTY
Feature: Editor
Group: String/Text Property
Type: string="abc"
LimitedType: FName/FString/Fext
Status: Done

只允许文本框里可以输入这些字符。

测试代码：

```cpp
public:
	UPROPERTY(EditAnywhere, Category = AllowedCharactersTest, meta = (AllowedCharacters = "abcde"))
	FString MyString_AllowedCharacters;
	UPROPERTY(EditAnywhere, Category = AllowedCharactersTest, meta = (AllowedCharacters = "你好"))
	FString MyString_AllowedCharacters_Chinese;
```

测试效果：

可见第一个只能输入abcde，而fgh产生了报错。在测试中文的时候，如果粘贴进去对应的中文，则是OK的。否则也会产生报错，不允许输入进去。

![Untitled](AllowedCharacters/Untitled.png)

原理：

SPropertyEditorText里实际保存了FCharRangeList 的AllowedCharacters用来限制字符。同样在字符串改变的时候，验证字符是否合法。

```cpp

FCharRangeList AllowedCharacters;

AllowedCharacters.InitializeFromString(PropertyHandle->GetMetaData(NAME_AllowedCharacters));

bool SPropertyEditorText::OnVerifyTextChanged(const FText& Text, FText& OutError)
{
	const FString& TextString = Text.ToString();

	if (MaxLength > 0 && TextString.Len() > MaxLength)
	{
		OutError = FText::Format(LOCTEXT("PropertyTextTooLongError", "This value is too long ({0}/{1} characters)"), TextString.Len(), MaxLength);
		return false;
	}

	if (!AllowedCharacters.IsEmpty())
	{
		if (!TextString.IsEmpty() && !AllowedCharacters.AreAllCharsIncluded(TextString))
		{
			TSet<TCHAR> InvalidCharacters = AllowedCharacters.FindCharsNotIncluded(TextString);
			FString InvalidCharactersString;
			for (TCHAR Char : InvalidCharacters)
			{
				if (!InvalidCharactersString.IsEmpty())
				{
					InvalidCharactersString.AppendChar(TEXT(' '));
				}
				InvalidCharactersString.AppendChar(Char);
			}
			OutError = FText::Format(LOCTEXT("PropertyTextCharactersNotAllowedError", "The value may not contain the following characters: {0}"), FText::FromString(InvalidCharactersString));
			return false;
		}
	}

	if (PropertyValidatorFunc.IsBound())
	{
		FText Result = PropertyValidatorFunc.Execute(TextString); 
		if (!Result.IsEmpty())
		{
			OutError = Result;
			return false;
		}
	}

	return true;
}
```

根据FCharRangeList的定义，限制字符的格式是：

```cpp
/** Initializes this instance with the character ranges represented by the passed definition string.
*   A definition string contains characters and ranges of characters, one after another with no special separators between them.
*   Characters - and \ must be escaped like this: \- and \\
* 
*   Examples:
*       "aT._" <-- Letters 'a' and 'T', dot and underscore.
*       "a-zT._" <-- All letters from 'a' to 'z', letter 'T', dot and underscore.
*       "a-zA-Z0-9._" <-- All lowercase and uppercase letters, all digits, dot and underscore.
*       "a-zA-Z0-9\-\\._" <-- All lowercase and uppercase letters, all digits, minus sign, backslash, dot and underscore.
*/
```