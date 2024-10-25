# MultiLine

- **Function Description:** Allows the text attribute editing box to support line breaks.
- **Usage Location:** UPROPERTY
- **Engine Module:** String/Text Property
- **Metadata Type:** bool
- **Restriction Type:** FName/FString/Fext
- **Commonality:** ★★★★★

Enables line breaks in the text attribute editing box. The string after line breaks is separated by "\r\n".

## Test Code:

```cpp
	UPROPERTY(EditAnywhere, Category = MultiLineTest, meta = (MultiLine = true))
	FString MyString_MultiLine = TEXT("Hello");

	UPROPERTY(EditAnywhere, Category = MultiLineTest, meta = (MultiLine = true))
	FText MyText_MultiLine = INVTEXT("Hello");

	UPROPERTY(EditAnywhere, Category = MultiLineTest, meta = (MultiLine = true, PasswordField = true))
	FString MyString_MultiLine_Password = TEXT("Hello");

	UPROPERTY(EditAnywhere, Category = MultiLineTest, meta = (MultiLine = true, PasswordField = true))
	FText MyText_MultiLine_Password  = INVTEXT("Hello");
```

## Test Results:

Press Shift+Enter to insert a line break.

![Untitled](Untitled.png)

## Principle:

The principle is quite simple, involving the creation of a specific multi-line editing control, SMultiLineEditableTextBox, based on the bIsMultiLine flag.

```cpp
void SPropertyEditorText::Construct( const FArguments& InArgs, const TSharedRef< class FPropertyEditor >& InPropertyEditor )
{
bIsMultiLine = PropertyHandle->GetBoolMetaData(NAME_MultiLine);

		if(bIsMultiLine)
		{
			ChildSlot
			[
				SAssignNew(HorizontalBox, SHorizontalBox)
				+SHorizontalBox::Slot()
				.FillWidth(1.0f)
				[
					SAssignNew(MultiLineWidget, SMultiLineEditableTextBox)
					.Text(InPropertyEditor, &FPropertyEditor::GetValueAsText)
					.Font(InArgs._Font)
					.SelectAllTextWhenFocused(false)
					.ClearKeyboardFocusOnCommit(false)
					.OnTextCommitted(this, &SPropertyEditorText::OnTextCommitted)
					.OnVerifyTextChanged(this, &SPropertyEditorText::OnVerifyTextChanged)
					.SelectAllTextOnCommit(false)
					.IsReadOnly(this, &SPropertyEditorText::IsReadOnly)
					.AutoWrapText(true)
					.ModiferKeyForNewLine(EModifierKey::Shift)
					//.IsPassword( bIsPassword )
				]
			];

			PrimaryWidget = MultiLineWidget;
		}

}
```