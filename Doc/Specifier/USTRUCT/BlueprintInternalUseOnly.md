# BlueprintInternalUseOnly

Type: bool
Feature: Blueprint
Description: 不可定义新BP变量，但可作为别的类的成员变量暴露和变量传递
MetaOperation: +=
Meta: BlueprintInternalUseOnly (../../Meta/Meta/BlueprintInternalUseOnly.md), BlueprintType (../../Meta/Meta/BlueprintType.md)
Status: Done

指明这个STRUCT会是个BlueprintType，但又不在蓝图编辑器中不能声明变量，但是可以作为别的类的成员变量暴露到蓝图中。

和不写BlueprintType的差别是什么？

不写BlueprintType则完全不能作为别的类的成员变量。BlueprintInternalUseOnly抑制了定义新变量的能力，但是可以作为变量传递。

如FTableRowBase本身并不能定义新变量，但是其子类（要加上BlueprintType）是可以定义新变量的，正常被使用。

源码里可以找到：

```cpp
USTRUCT(BlueprintInternalUseOnly)
struct FLatentActionInfo
{}

USTRUCT(BlueprintInternalUseOnly)
struct FTableRowBase
{}
```

在源码中找到

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

//Node->IsIntermediateNode()如果为true，则是作为中间节点使用，true会导致bForInternalUse为true
if (!UK2Node_MakeStruct::CanBeMade(Node->StructType, Node->IsIntermediateNode()))
```

![Untitled](BlueprintInternalUseOnly/Untitled.png)