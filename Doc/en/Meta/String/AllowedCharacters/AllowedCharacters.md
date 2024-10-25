# AllowedCharacters

- **Function description:** The text box only permits the input of these specific characters.
- **Usage location:** UPROPERTY
- **Engine module:** String/Text Property
- **Metadata type:** string = "abc"
- **Restriction type:** FName/FString/Fext
- **Commonality:** ★★★

Only these characters are allowed to be entered in the text box.

## Test Code:

```cpp
public:
	UPROPERTY(EditAnywhere, Category = AllowedCharactersTest, meta = (AllowedCharacters = "abcde"))
	FString MyString_AllowedCharacters;
	UPROPERTY(EditAnywhere, Category = AllowedCharactersTest, meta = (AllowedCharacters = "你好"))
	FString MyString_AllowedCharacters_Chinese;
```

## Test Code:

It is evident that the first field only accepts input of abcde; any attempt to input fgh results in an error. When testing Chinese characters, if the corresponding Chinese characters are pasted, they are accepted without issue. Otherwise, an error is generated, and input is disallowed.

![Untitled](Untitled.png)

## 测试效果:

The SPropertyEditorText actually stores an FCharRangeList named AllowedCharacters to restrict input characters. Similarly, when the string is modified, it validates whether the characters are valid.

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

Test Results:

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