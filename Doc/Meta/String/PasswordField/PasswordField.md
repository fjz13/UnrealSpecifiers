# PasswordField

功能描述: 使得文本属性显示为密码框
使用位置: UPROPERTY
Feature: Editor
引擎模块: String/Text Property
元数据类型: bool
限制类型: FName/FString/Fext
Status: Done
常用程度: 5

使得文本属性显示为密码框。注意该文本的值在内存里依然是直接保存的，并没有加密，因此要自己来处理安全问题。

测试代码：

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

测试效果：

![Untitled](PasswordField/Untitled.png)

原理：该属性会导致Widget的IsPassword为true，从源码也可以得知需要注意PasswordField 不能和MultiLine共用，会导致Password功能失效。

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