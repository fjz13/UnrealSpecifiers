# DevelopmentOnly

Usage: UFUNCTION
Feature: Blueprint
Type: bool
Description: 使得一个函数变为DevelopmentOnly，意味着只会在Development模式中运行。适用于调试输出之类的功能，但在最终发布版中会跳过。
Status: Done
Group: Development

使得一个函数变为DevelopmentOnly，意味着只会在Development模式中运行。适用于调试输出之类的功能，但在最终发布版中会跳过。

源码中最典型的例子就是PrintString。

测试代码：

```cpp
	UFUNCTION(BlueprintCallable,meta=(DevelopmentOnly))
	static void MyFunc_DevelopmentOnly(){}

	UFUNCTION(BlueprintCallable,meta=())
	static void MyFunc_NotDevelopmentOnly(){}
```

蓝图效果：

![Untitled](DevelopmentOnly/Untitled.png)

原理：

其会改变这个函数蓝图节点的状态为DevelopmentOnly，从而最终导致该node在shipping模式下被pass through。

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