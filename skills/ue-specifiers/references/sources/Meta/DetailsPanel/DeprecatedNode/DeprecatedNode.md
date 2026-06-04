---
title: "DeprecatedNode"
id: "meta.DeprecatedNode"
kind: "meta"
symbol: "DeprecatedNode"
category: "DetailsPanel"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "用于BehaviorTreeNode或EnvQueryNode，说明该类已废弃，在编辑器中红色错误展示并有错误ToolTip提示"
usage: "UCLASS"
---

# DeprecatedNode

- **功能描述：** 用于BehaviorTreeNode或EnvQueryNode，说明该类已废弃，在编辑器中红色错误展示并有错误ToolTip提示
- **使用位置：** UCLASS
- **引擎模块：** DetailsPanel
- **元数据类型：** bool
- **限制类型：** BehaviorTreeNode，EnvQueryNode
- **常用程度：** ★★

在AI行为树或EQS的节点上设置，标记该节点已经弃用。
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。

## 源码中的例子：

```cpp
UCLASS(meta = (DeprecatedNode, DeprecationMessage = "Please use IsAtLocation decorator instead."), MinimalAPI)
class UBTDecorator_ReachedMoveGoal : public UBTDecorator
{
	GENERATED_UCLASS_BODY()
};

UCLASS(MinimalAPI, meta=(DeprecatedNode, DeprecationMessage = "This class is now deprecated, please use RunMode supporting random results instead."))
class UEnvQueryTest_Random : public UEnvQueryTest
{
	GENERATED_UCLASS_BODY()
};
```

## C++测试代码：

```cpp
UCLASS(meta = (DeprecatedNode, DeprecationMessage = "This BT node is deprecated. Don't use this anymore."), MinimalAPI)
class UBTTask_MyDeprecatedNode : public UBTTaskNode
{
	GENERATED_UCLASS_BODY()
};
```

行为树里的结果，如果加上DeprecatedNode，就会红色显示，并提示错误信息。


## 源码里测试的代码：

```cpp
FString FGraphNodeClassHelper::GetDeprecationMessage(const UClass* Class)
{
	static FName MetaDeprecated = TEXT("DeprecatedNode");
	static FName MetaDeprecatedMessage = TEXT("DeprecationMessage");
	FString DefDeprecatedMessage("Please remove it!");
	FString DeprecatedPrefix("DEPRECATED");
	FString DeprecatedMessage;

	if (Class && Class->HasAnyClassFlags(CLASS_Native) && Class->HasMetaData(MetaDeprecated))
	{
		DeprecatedMessage = DeprecatedPrefix + TEXT(": ");
		DeprecatedMessage += Class->HasMetaData(MetaDeprecatedMessage) ? Class->GetMetaData(MetaDeprecatedMessage) : DefDeprecatedMessage;
	}

	return DeprecatedMessage;
}
```
