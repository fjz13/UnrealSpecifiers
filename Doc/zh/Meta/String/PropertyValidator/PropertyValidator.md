# PropertyValidator

- **功能描述：** 用名字指定一个UFUNCTION函数来进行文本的验证
- **使用位置：** UPROPERTY
- **引擎模块：** String/Text Property
- **元数据类型：** string="abc"
- **限制类型：** FName/FString/Fext
- **常用程度：** ★★★

用名字指定一个UFUNCTION函数来进行文本的验证。

这个函数必须是用UFUNCTION修饰的，这样才能通过名字找到。且因为搜索的范围在本类中，因此该函数必须定义在本类中。否则会报错：“LogPropertyNode: Warning: PropertyValidator ufunction 'MyValidateMyString' on UMyProperty_Text::MyString_PropertyValidator not found.”

函数的签名见如下代码。返回空的FText代表没有错误，否则即是错误信息。

## 测试代码：

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

## 测试效果：

![Untitled](Untitled.png)

## 原理:

原理也比较简单，分为两部分。一是如何找到并创建该UFunction，二是调用该函数来验证字符串。

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