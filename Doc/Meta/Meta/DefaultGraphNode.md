# DefaultGraphNode

Usage: UCLASS
Feature: Blueprint
Type: bool
Description: K2Node_Event /Game/Property/Widget/UMG_BindTest.UMG_BindTest:EventGraph.K2Node_Event_0
Status: OnlyInternal
Group: Widget Property

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