# PropertyValidator

- **Function Description:** Specifies a UFUNCTION to validate text by name
- **Usage Location:** UPROPERTY
- **Engine Module:** String/Text Property
- **Metadata Type:** string="abc"
- **Restriction Type:** FName/FString/Fext
- **Commonality:** ★★★

Specifies a UFUNCTION by name to validate text.

This function must be decorated with UFUNCTION to be locatable by name. Since the search scope is within the class, the function must be defined within the class itself. Otherwise, an error will occur: "LogPropertyNode: Warning: PropertyValidator ufunction 'MyValidateMyString' on UMyProperty_Text::MyString_PropertyValidator not found."

The function signature is as shown in the following code. An empty FText return indicates no error, while a non-empty one represents an error message.

## Test Code:

```cpp
	UPROPERTY(EditAnywhere, Category = PropertyValidatorTest, meta = (PropertyValidator = "MyValidateMyString"))
	FString MyString_PropertyValidator;

	UFUNCTION()
	static FText MyValidateMyString(const FString& Value)
	{
		if (Value.Len() <= 5 && Value.Contains("A"))
		{
			return FText();
		}
		return INVTEXT("This is invalid string");
	}
```

## Test Results:

![Untitled](Untitled.png)

## Principle:

The principle is relatively straightforward, consisting of two parts: how to locate and create the UFUNCTION, and how to invoke the function to validate the string.

```cpp
const FString PropertyValidatorFunctionName = PropertyHandle->GetMetaData(NAME_PropertyValidator);
const UClass* OuterBaseClass = PropertyHandle->GetOuterBaseClass();
if (!PropertyValidatorFunctionName.IsEmpty() && OuterBaseClass)
{
	static TSet<FString> LoggedWarnings;

	UObject* ValidatorObject = OuterBaseClass->GetDefaultObject<UObject>();
	const UFunction* PropertyValidatorFunction = ValidatorObject->FindFunction(*PropertyValidatorFunctionName);
	if (PropertyValidatorFunction)
	{
		if (PropertyValidatorFunction->FunctionFlags & FUNC_Static)
		{
			PropertyValidatorFunc = FPropertyValidatorFunc::CreateUFunction(ValidatorObject, PropertyValidatorFunction->GetFName());
		}

bool SPropertyEditorText::OnVerifyTextChanged(const FText& Text, FText& OutError)
{
	const FString& TextString = Text.ToString();

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