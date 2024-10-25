# DevelopmentOnly

- **Function Description:** Marks a function as DevelopmentOnly, indicating that it will only execute in Development mode. This is useful for debugging purposes such as outputting debug information, but it will be skipped in the final release version.
- **Usage Location:** UFUNCTION
- **Engine Module:** Development
- **Metadata Type:** bool
- **Commonality:** ★

Marks a function as DevelopmentOnly, meaning it will only run in Development mode. This is suitable for debugging features like outputting debug information, but it will be omitted from the final release.

The most typical example in the source code is PrintString.

## Test Code:

```cpp
	UFUNCTION(BlueprintCallable,meta=(DevelopmentOnly))
	static void MyFunc_DevelopmentOnly(){}

	UFUNCTION(BlueprintCallable,meta=())
	static void MyFunc_NotDevelopmentOnly(){}
```

## Blueprint Effect:

![Untitled](Untitled.png)

## Principle:

It alters the state of the function's blueprint node to DevelopmentOnly, which consequently results in the node being passed through in shipping mode.

```cpp
void UK2Node_CallFunction::Serialize(FArchive& Ar)
{
		if (const UFunction* Function = GetTargetFunction())
		{
					// Enable as development-only if specified in metadata. This way existing functions that have the metadata added to them will get their enabled state fixed up on load.
					if (GetDesiredEnabledState() == ENodeEnabledState::Enabled && Function->HasMetaData(FBlueprintMetadata::MD_DevelopmentOnly))
					{
						SetEnabledState(ENodeEnabledState::DevelopmentOnly, /*bUserAction=*/ false);
					}
					// Ensure that if the metadata is removed, we also fix up the enabled state to avoid leaving it set as development-only in that case.
					else if (GetDesiredEnabledState() == ENodeEnabledState::DevelopmentOnly && !Function->HasMetaData(FBlueprintMetadata::MD_DevelopmentOnly))
					{
						SetEnabledState(ENodeEnabledState::Enabled, /*bUserAction=*/ false);
					}
		}
}
```