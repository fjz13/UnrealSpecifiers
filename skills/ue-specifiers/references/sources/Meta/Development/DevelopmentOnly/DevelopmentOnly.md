---
title: "DevelopmentOnly"
id: "meta.DevelopmentOnly"
kind: "meta"
symbol: "DevelopmentOnly"
category: "Development"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "使得一个函数变为DevelopmentOnly，意味着只会在Development模式中运行。适用于调试输出之类的功能，但在最终发布版中会跳过"
usage: "UFUNCTION"
---

# DevelopmentOnly

- **功能描述：** 使得一个函数变为DevelopmentOnly，意味着只会在Development模式中运行。适用于调试输出之类的功能，但在最终发布版中会跳过。
- **使用位置：** UFUNCTION
- **引擎模块：** Development
- **元数据类型：** bool
- **常用程度：** ★

使得一个函数变为DevelopmentOnly，意味着只会在Development模式中运行。适用于调试输出之类的功能，但在最终发布版中会跳过。

源码中最典型的例子就是PrintString。
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。

## 测试代码：

```cpp
	UFUNCTION(BlueprintCallable,meta=(DevelopmentOnly))
	static void MyFunc_DevelopmentOnly(){}

	UFUNCTION(BlueprintCallable,meta=())
	static void MyFunc_NotDevelopmentOnly(){}
```

## 蓝图效果：


## 原理：

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
