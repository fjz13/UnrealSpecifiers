# PasswordField

- **Function Description:** Enables the text attribute to be displayed as a password field
- **Usage Location:** UPROPERTY
- **Engine Module:** String/Text Property
- **Metadata Type:** bool
- **Restriction Type:** FName/FString/Fext
- **Commonality:** ★★★★★

Displays the text attribute as a password field. Note that the value of the text is stored directly in memory without encryption, so security concerns must be addressed separately.

## Test Code:

```cpp
public:
	UPROPERTY(EditAnywhere, Category = PasswordTest)
	FString MyString = TEXT("Hello");

	UPROPERTY(EditAnywhere, Category = PasswordTest)
	FText MyText = INVTEXT("Hello");
public:
	UPROPERTY(EditAnywhere, Category = PasswordTest, meta = (PasswordField = true))
	FString MyString_Password = TEXT("Hello");

	UPROPERTY(EditAnywhere, Category = PasswordTest, meta = (PasswordField = true))
	FText MyText_Password = INVTEXT("Hello");
```

## Test Results:

![Untitled](Untitled.png)

## Principle:

This attribute sets the Widget's IsPassword property to true. It is also worth noting from the source code that the PasswordField cannot be used concurrently with MultiLine, as this will render the password functionality ineffective.

```cpp
void SPropertyEditorText::Construct( const FArguments& InArgs, const TSharedRef< class FPropertyEditor >& InPropertyEditor )
{
		const bool bIsPassword = PropertyHandle->GetBoolMetaData(NAME_PasswordField);

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
		else
		{
			ChildSlot
			[
				SAssignNew(HorizontalBox, SHorizontalBox)
				+SHorizontalBox::Slot()
				.FillWidth(1.0f)
				[
					SAssignNew( SingleLineWidget, SEditableTextBox )
					.Text( InPropertyEditor, &FPropertyEditor::GetValueAsText )
					.Font( InArgs._Font )
					.SelectAllTextWhenFocused( true )
					.ClearKeyboardFocusOnCommit(false)
					.OnTextCommitted( this, &SPropertyEditorText::OnTextCommitted )
					.OnVerifyTextChanged( this, &SPropertyEditorText::OnVerifyTextChanged )
					.SelectAllTextOnCommit( true )
					.IsReadOnly(this, &SPropertyEditorText::IsReadOnly)
					.IsPassword( bIsPassword )
				]
			];

			PrimaryWidget = SingleLineWidget;
		}
}
```