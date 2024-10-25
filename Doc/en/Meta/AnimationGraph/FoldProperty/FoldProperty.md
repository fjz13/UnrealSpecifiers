# FoldProperty

- **Function description:** Allows a certain attribute of an animation node to be designated as a FoldProperty within an animation blueprint.
- **Use location:** UPROPERTY
- **Engine module:** AnimationGraph
- **Metadata type:** bool
- **Restriction type:** Attributes under FAnimNode_Base
- **Commonly used:** ★

Enables a specific attribute of an animation node to be marked as a FoldProperty within an animation blueprint.

- While PinHiddenByDefault also hides properties in the UI, FoldProperty behaves differently in terms of functionality.
- FoldProperty refers to attributes that are frequently enclosed with WITH_EDITORONLY_DATA, storing information specific to the editor's state. For instance, the PlayRate data under FAnimNode_SequencePlayer is data that exists only in the editor's context. Alternatively, it may simply be information related to the animation blueprint itself, remaining consistent across all instances of the blueprint. Such attributes are suitable for being designated as FoldProperties.
- These attributes need to be edited on the node without being exposed as pins, hence they are placed in the details panel on the right side, similar to PinHiddenByDefault in appearance.

All "Constant/Fold" attribute information used by the instances of an animation node is stored in FAnimNodeData* FAnimNode_Base::NodeData. An animation blueprint may have multiple instances within a game, yet only one copy of the constant information and FoldProperty data for the animation node is maintained among these instances. Therefore, the actual data for properties marked as FoldProperty is stored in the TArray<FAnimNodeData> UAnimBlueprintGeneratedClass::AnimNodeData. This existence within the class is akin to the concept of CDO. One clear advantage of this approach is the conservation of memory.

Naturally, with different storage methods, different access approaches are required. Hence, these FoldProperties are accessed using GET_ANIM_NODE_DATA.

## Test Code:

```cpp
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FoldPropertyTest, meta = (FoldProperty))
	int32 MyInt_FoldProperty = 123;
```

## Test Results:

![Untitled](Untitled.png)

## Principle:

During compilation, the FoldProperty is added to FoldRecords. If the property is not dynamic and is not exposed for pin connections, it will be treated as a constant.

```cpp
void FAnimBlueprintCompilerContext::GatherFoldRecordsForAnimationNode(const UScriptStruct* InNodeType, FStructProperty* InNodeProperty, UAnimGraphNode_Base* InVisualAnimNode)
{
	if(SubProperty->HasMetaData(NAME_FoldProperty))
	{
		// Add folding candidate
		AddFoldedPropertyRecord(InVisualAnimNode, InNodeProperty, SubProperty, bAllPinsExposed, !bAllPinsDisconnected, bAlwaysDynamic);
	}
}

void FAnimBlueprintCompilerContext::AddFoldedPropertyRecord(UAnimGraphNode_Base* InAnimGraphNode, FStructProperty* InAnimNodeProperty, FProperty* InProperty, bool bInExposedOnPin, bool bInPinConnected, bool bInAlwaysDynamic)
{
	const bool bConstant = !bInAlwaysDynamic && (!bInExposedOnPin || (bInExposedOnPin && !bInPinConnected));

	if(!InProperty->HasAnyPropertyFlags(CPF_EditorOnly))
	{
		MessageLog.Warning(*FString::Printf(TEXT("Property %s on @@ is foldable, but not editor only"), *InProperty->GetName()), InAnimGraphNode);
	}

	// Create record and add it our lookup map
	TSharedRef<IAnimBlueprintCompilationContext::FFoldedPropertyRecord> Record = MakeShared<IAnimBlueprintCompilationContext::FFoldedPropertyRecord>(InAnimGraphNode, InAnimNodeProperty, InProperty, bConstant);
	TArray<TSharedRef<IAnimBlueprintCompilationContext::FFoldedPropertyRecord>>& Array = NodeToFoldedPropertyRecordMap.FindOrAdd(InAnimGraphNode);
	Array.Add(Record);

	// Record it in the appropriate data area
	if(bConstant)
	{
		ConstantPropertyRecords.Add(Record);
	}
	else
	{
		MutablePropertyRecords.Add(Record);
	}
}
```