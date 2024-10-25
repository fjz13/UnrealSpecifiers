# DetailsOnly

- **Function Description:** Specifies that the attribute under FRigUnit is displayed only in the Details panel.
- **Use Location:** UPROPERTY
- **Engine Module:** RigVMStruct
- **Metadata Type:** Boolean
- **Restriction Type:** Attributes within FRigUnit
- **Associated Items:** [Input](../Input/Input.md)
- **Usage Frequency:** ★★★

Specifies that this attribute under FRigUnit is to be displayed exclusively in the Details panel.

## Test Code:

```cpp
	UPROPERTY(meta = (Input, DetailsOnly))
	float MyFloat_DetailsOnly = 456.f;
```

## Test Results:

![Untitled](Untitled.png)

## Principle:

Based on the DetailsOnly attribute, determine whether to return ShowInDetailsPanelOnly.

```cpp
bool URigVMPin::ShowInDetailsPanelOnly() const
{
#if WITH_EDITOR
	if (GetParentPin() == nullptr)
	{
		if (URigVMUnitNode* UnitNode = Cast<URigVMUnitNode>(GetNode()))
		{
			if (UScriptStruct* ScriptStruct = UnitNode->GetScriptStruct())
			{
				if (FProperty* Property = ScriptStruct->FindPropertyByName(GetFName()))
				{
					if (Property->HasMetaData(FRigVMStruct::DetailsOnlyMetaName))
					{
						return true;
					}
				}
			}
		}
		else if(const URigVMTemplateNode* TemplateNode = Cast<URigVMTemplateNode>(GetNode()))
		{
			if(const FRigVMTemplate* Template = TemplateNode->GetTemplate())
			{
				return !Template->GetArgumentMetaData(GetFName(), FRigVMStruct::DetailsOnlyMetaName).IsEmpty();
			}
		}
	}
#endif
	return false;
}
```