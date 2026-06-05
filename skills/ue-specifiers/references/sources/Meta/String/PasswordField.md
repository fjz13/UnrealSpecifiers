---
title: "PasswordField"
id: "meta.PasswordField"
kind: "meta"
symbol: "PasswordField"
category: "String"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "使得文本属性显示为密码框"
usage: "UPROPERTY"
---

# PasswordField

## Decision Summary

- **Use when:** editor 输入框需要隐藏敏感字符串显示。
- **Do not use when:** 数据需要真正安全存储或加密。
- **Requires:** 适用于支持该 metadata 的字符串属性展示。
- **Conflicts:** 只影响 UI 显示，不提供安全保护。
- **Prefer instead:** 真正敏感数据使用安全存储/凭据流程，不放普通 UPROPERTY。

- **功能描述：** 使得文本属性显示为密码框
- **使用位置：** UPROPERTY
- **引擎模块：** String/Text Property
- **元数据类型：** bool
- **限制类型：** FName/FString/Fext
- **常用程度：** ★★★★★

使得文本属性显示为密码框。注意该文本的值在内存里依然是直接保存的，并没有加密，因此要自己来处理安全问题。
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。

## 测试代码：

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

## 测试效果：


## 原理：

该属性会导致Widget的IsPassword为true，从源码也可以得知需要注意PasswordField 不能和MultiLine共用，会导致Password功能失效。

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
