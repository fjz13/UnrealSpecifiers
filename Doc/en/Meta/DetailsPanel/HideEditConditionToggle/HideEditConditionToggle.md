# HideEditConditionToggle

- **Function Description:** Used on attributes utilizing EditCondition, indicating that the attribute does not wish the properties involved in its EditCondition to be hidden.
- **Usage Location:** UPROPERTY
- **Engine Module:** DetailsPanel
- **Metadata Type:** bool
- **Restriction Type:** bool
- **Associated Items:** [EditCondition](../EditCondition/EditCondition.md)
- **Commonality:** ★★★★★

Applied to properties that use EditCondition, signifying that the property does not want the properties referenced by its EditCondition to be concealed. This has an opposite effect to InlineEditConditionToggle.

## Test Code:

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

## Testing Code:

![HideEditConditionToggle](HideEditConditionToggle.gif)

## 测试效果:

Decide whether the current row supports a button with a radio button if a HideEditConditionToggle is present.

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