# DefaultGraphNode

功能描述: 标记引擎默认创建的蓝图节点。
使用位置: UCLASS
Feature: Blueprint
引擎模块: Widget Property
元数据类型: bool
Status: OnlyInternal
常用程度: 0

标记引擎默认创建的蓝图节点。

这样就可以在判断蓝图内是否有用户手动创建的节点时，过滤掉引擎自动创建的那些。

只在内部使用，用户不需要自己使用。

原理：

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