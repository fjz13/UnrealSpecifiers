# BlueprintInternalUseOnlyHierarchical

- **功能描述：**  在BlueprintInternalUseOnly的基础上，增加了子类也不能定义新BP变量的限制。
- **元数据类型：** bool
- **引擎模块：** Blueprint
- **作用机制：** 在Meta中加入[BlueprintInternalUseOnlyHierarchical](../../../Meta/Blueprint/BlueprintInternalUseOnlyHierarchical.md)
- **常用程度：★**

在BlueprintInternalUseOnly的基础上，增加了子类也不能定义新BP变量的限制。

目前只找到一个用处，但是也依然没有子类。如果我们在C++中定义新的子类，则所有的子类都不能定义变量。注意和FTableRowBase的区别是，FTableRowBase的子类依然可以定义新变量，因为FTableRowBase的BlueprintInternalUseOnly标记只作用于自己。

## 示例代码：

```cpp
USTRUCT(BlueprintInternalUseOnlyHierarchical)
struct GAMEPLAYABILITIESEDITOR_API FGameplayAbilityAuditRow : public FTableRowBase
{}

USTRUCT(BlueprintInternalUseOnly)
struct FTableRowBase
{}
```

## 原理：

只在这个地方用到，GetBoolMetaDataHierarchical会检查结构的所有父类测试是否含有某个标记。所以只要有一个父类有一个这个标记，就不能定义新变量。

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