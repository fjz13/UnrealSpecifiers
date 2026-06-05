---
title: "PropertyValidator"
id: "meta.PropertyValidator"
kind: "meta"
symbol: "PropertyValidator"
category: "String"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "用名字指定一个UFUNCTION函数来进行文本的验证"
usage: "UPROPERTY"
---

# PropertyValidator

## Decision Summary

- **Use when:** `PropertyValidator` metadata 的 `UPROPERTY` 场景需要：用名字指定一个UFUNCTION函数来进行文本的验证。
- **Do not use when:** 目标声明不属于 `UPROPERTY`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 用名字指定一个UFUNCTION函数来进行文本的验证
- **使用位置：** UPROPERTY
- **引擎模块：** String/Text Property
- **元数据类型：** string="abc"
- **限制类型：** FName/FString/Fext
- **常用程度：** ★★★

用名字指定一个UFUNCTION函数来进行文本的验证。

这个函数必须是用UFUNCTION修饰的，这样才能通过名字找到。且因为搜索的范围在本类中，因此该函数必须定义在本类中。否则会报错：“LogPropertyNode: Warning: PropertyValidator ufunction 'MyValidateMyString' on UMyProperty_Text::MyString_PropertyValidator not found.”

函数的签名见如下代码。返回空的FText代表没有错误，否则即是错误信息。
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。

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
