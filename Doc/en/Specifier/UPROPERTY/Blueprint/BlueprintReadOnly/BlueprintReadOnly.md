# BlueprintReadOnly

- **Functional Description:** This attribute can be read by Blueprints but is not modifiable.
- **Metadata Type:** bool
- **Engine Module:** Blueprint
- **Functionality Mechanism:** [CPF_BlueprintVisible](../../../../Flags/EPropertyFlags/CPF_BlueprintVisible.md) and [CPF_BlueprintReadOnly](../../../../Flags/EPropertyFlags/CPF_BlueprintReadOnly.md) are added to the PropertyFlags
- **Commonly Used:** ★★★★★

This attribute can be read by Blueprints but is not modifiable. This specifier is incompatible with the BlueprintReadWrite specifier.

## Sample Code:

```cpp
public:
	//PropertyFlags:	CPF_BlueprintVisible | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UPROPERTY(BlueprintReadWrite, Category = Blueprint)
		int32 MyInt_ReadWrite = 123;
	//PropertyFlags:	CPF_BlueprintVisible | CPF_BlueprintReadOnly | CPF_ZeroConstructor | CPF_IsPlainOldData | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UPROPERTY(BlueprintReadOnly, Category = Blueprint)
		int32 MyInt_ReadOnly = 123;
```

## Example Effect:

Specify the blueprint as read-only:

![Untitled](Untitled.png)

## Principle:

With CPF_BlueprintVisible, access is granted

After adding CPF_BlueprintReadOnly, modifications are not allowed.

```cpp
EPropertyAccessResultFlags PropertyAccessUtil::CanGetPropertyValue(const FProperty* InProp)
{
	if (!InProp->HasAnyPropertyFlags(CPF_Edit | CPF_BlueprintVisible | CPF_BlueprintAssignable))
	{
		return EPropertyAccessResultFlags::PermissionDenied | EPropertyAccessResultFlags::AccessProtected;
	}

	return EPropertyAccessResultFlags::Success;
}

FBlueprintEditorUtils::EPropertyWritableState FBlueprintEditorUtils::IsPropertyWritableInBlueprint(const UBlueprint* Blueprint, const FProperty* Property)
{
	if (Property)
	{
		if (!Property->HasAnyPropertyFlags(CPF_BlueprintVisible))
		{
			return EPropertyWritableState::NotBlueprintVisible;
		}
		if (Property->HasAnyPropertyFlags(CPF_BlueprintReadOnly))
		{
			return EPropertyWritableState::BlueprintReadOnly;
		}
		if (Property->GetBoolMetaData(FBlueprintMetadata::MD_Private))
		{
			const UClass* OwningClass = Property->GetOwnerChecked<UClass>();
			if (OwningClass->ClassGeneratedBy.Get() != Blueprint)
			{
				return EPropertyWritableState::Private;
			}
		}
	}
	return EPropertyWritableState::Writable;
}
```