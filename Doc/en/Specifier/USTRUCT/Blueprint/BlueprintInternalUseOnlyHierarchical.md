# BlueprintInternalUseOnlyHierarchical

- **Function Description:** On top of BlueprintInternalUseOnly, it imposes the restriction that subclasses are also prohibited from defining new BP variables.
- **Metadata Type:** bool
- **Engine Module:** Blueprint
- **Action Mechanism:** Include [BlueprintInternalUseOnlyHierarchical](../../../Meta/Blueprint/BlueprintInternalUseOnlyHierarchical.md) in the Meta section
- **Commonality:** ★

Building upon BlueprintInternalUseOnly, it introduces the limitation that subclasses are not allowed to define new BP variables.

Currently, this feature is only found to have one application, and there are no subclasses. If we define new subclasses in C++, none of these subclasses will be able to define variables. It is important to note that this differs from FTableRowBase, where subclasses can still define new variables because the BlueprintInternalUseOnly attribute of FTableRowBase only applies to itself.

## Sample Code:

```cpp
USTRUCT(BlueprintInternalUseOnlyHierarchical)
struct GAMEPLAYABILITIESEDITOR_API FGameplayAbilityAuditRow : public FTableRowBase
{}

USTRUCT(BlueprintInternalUseOnly)
struct FTableRowBase
{}
```

## Principle:

Utilized exclusively in this context, GetBoolMetaDataHierarchical checks whether any of the structure's parent classes have a specific tag. If any parent class possesses this tag, the definition of new variables is prohibited.

```cpp
bool UEdGraphSchema_K2::IsAllowableBlueprintVariableType(const UScriptStruct* InStruct, const bool bForInternalUse)
{
	if (const UUserDefinedStruct* UDStruct = Cast<const UUserDefinedStruct>(InStruct))
	{
		if (EUserDefinedStructureStatus::UDSS_UpToDate != UDStruct->Status.GetValue())
		{
			return false;
		}

		// User-defined structs are always allowed as BP variable types.
		return true;
	}

	// struct needs to be marked as BP type
	if (InStruct && InStruct->GetBoolMetaDataHierarchical(FBlueprintMetadata::MD_AllowableBlueprintVariableType))
	{
		// for internal use, all BP types are allowed
		if (bForInternalUse)
		{
			return true;
		}

		// for user-facing use case, only allow structs that don't have the internal-use-only tag
		// struct itself should not be tagged
		if (!InStruct->GetBoolMetaData(FBlueprintMetadata::MD_BlueprintInternalUseOnly))
		{
			// struct's base structs should not be tagged
			if (!InStruct->GetBoolMetaDataHierarchical(FBlueprintMetadata::MD_BlueprintInternalUseOnlyHierarchical))
			{
				return true;
			}
		}
	}

	return false;
}

```