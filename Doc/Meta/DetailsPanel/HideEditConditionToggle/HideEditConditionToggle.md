# HideEditConditionToggle

- **功能描述：** 用在使用EditCondition的属性上，表示该属性不想要其EditCondition用到的属性被隐藏起来。
- **使用位置：** UPROPERTY
- **引擎模块：** DetailsPanel
- **元数据类型：** bool
- **限制类型：** bool
- **关联项：** [EditCondition](../EditCondition/EditCondition.md)
- **常用程度：** ★★★★★

用在使用EditCondition的属性上，表示该属性不想要其EditCondition用到的属性被隐藏起来。和InlineEditConditionToggle是有相反的作用。

## 测试代码：

```cpp

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InlineEditConditionToggle, meta = (InlineEditConditionToggle))
	bool MyBool_Inline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InlineEditConditionToggle, meta = (EditCondition = "MyBool_Inline"))
	int32 MyInt_EditCondition_UseInline = 123;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InlineEditConditionToggle, meta = (HideEditConditionToggle,EditCondition = "MyBool_Inline"))
	int32 MyInt_EditCondition_UseInline_Hide = 123;
};
```

## 测试效果：

![HideEditConditionToggle.gif](HideEditConditionToggle.gif)

## 原理：

判断如果有HideEditConditionToggle，就支持不支持当前行有单选框的按钮。

```cpp

bool FPropertyNode::SupportsEditConditionToggle() const
{
	if (!Property.IsValid())
	{
		return false;
	}

	FProperty* MyProperty = Property.Get();

	static const FName Name_HideEditConditionToggle("HideEditConditionToggle");
	if (EditConditionExpression.IsValid() && !Property->HasMetaData(Name_HideEditConditionToggle))
	{
		const FBoolProperty* ConditionalProperty = EditConditionContext->GetSingleBoolProperty(EditConditionExpression);
		if (ConditionalProperty != nullptr)
		{
			// There are 2 valid states for inline edit conditions:
			// 1. The property is marked as editable and has InlineEditConditionToggle set. 
			// 2. The property is not marked as editable and does not have InlineEditConditionToggle set.
			// In both cases, the original property will be hidden and only show up as a toggle.

			static const FName Name_InlineEditConditionToggle("InlineEditConditionToggle");
			const bool bIsInlineEditCondition = ConditionalProperty->HasMetaData(Name_InlineEditConditionToggle);
			const bool bIsEditable = ConditionalProperty->HasAllPropertyFlags(CPF_Edit);

			if (bIsInlineEditCondition == bIsEditable)
			{
				return true;
			}

			if (bIsInlineEditCondition && !bIsEditable)
			{
				UE_LOG(LogPropertyNode, Warning, TEXT("Property being used as inline edit condition is not editable, but has redundant InlineEditConditionToggle flag. Field \"%s\" in class \"%s\"."), *ConditionalProperty->GetNameCPP(), *Property->GetOwnerStruct()->GetName());
				return true;
			}

			// The property is already shown, and not marked as inline edit condition.
			if (!bIsInlineEditCondition && bIsEditable)
			{
				return false;
			}
		}
	}

	return false;
}
```
