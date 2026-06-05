---
title: "DefaultGraphNode"
id: "meta.DefaultGraphNode"
kind: "meta"
symbol: "DefaultGraphNode"
category: "Widget"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "标记引擎默认创建的蓝图节点"
usage: "UCLASS"
---

# DefaultGraphNode

## Decision Summary

- **Use when:** `DefaultGraphNode` metadata 的 `UCLASS` 场景需要：标记引擎默认创建的蓝图节点。
- **Do not use when:** 目标声明不属于 `UCLASS`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 标记引擎默认创建的蓝图节点。
- **使用位置：** UCLASS
- **引擎模块：** Widget Property
- **元数据类型：** bool
- **常用程度：** 0

标记引擎默认创建的蓝图节点。

这样就可以在判断蓝图内是否有用户手动创建的节点时，过滤掉引擎自动创建的那些。

只在内部使用，用户不需要自己使用。
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。

## 原理：

```cpp

static bool BlueprintEditorImpl::GraphHasUserPlacedNodes(UEdGraph const* InGraph)
{
	bool bHasUserPlacedNodes = false;

	for (UEdGraphNode const* Node : InGraph->Nodes)
	{
		if (Node == nullptr)
		{
			continue;
		}

		if (!Node->GetOutermost()->GetMetaData()->HasValue(Node, FNodeMetadata::DefaultGraphNode))
		{
			bHasUserPlacedNodes = true;
			break;
		}
	}

	return bHasUserPlacedNodes;
}
```
