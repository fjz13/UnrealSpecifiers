# FoldProperty

功能描述: 在动画蓝图中使得动画节点的某个属性成为FoldProperty。
使用位置: UPROPERTY
Feature: Blueprint
引擎模块: AnimationGraph
元数据类型: bool
限制类型: FAnimNode_Base下的属性
Status: Done
常用程度: 1

在动画蓝图中使得动画节点的某个属性成为FoldProperty。

- 在UI表现上PinHiddenByDefault也有同样的效果，但是FoldProperty在行为上有别的不同。
- 所谓FoldProperty，指的是这些属性往往使被WITH_EDITORONLY_DATA包起来的。记录编辑器状况下的信息。比如FAnimNode_SequencePlayer下的PlayRate数据，其就是在编辑器状态的下数据。又或者只是动画蓝图本身的信息，不管动画蓝图的多少个实例，这些属性的值其实都是同样的。这些属性就适合成为FoldProperty。
- 这些属性需要在节点上编辑，但又不想暴露成引脚，因此就在形式上和PinHiddenByDefault一样放到右侧的细节面板里。

在FAnimNodeData* FAnimNode_Base::NodeData里存储着该动画节点的所有实例所用到的“Constant/Fold”属性信息。该动画蓝图在游戏里可能有多个实例，在这些实例之间都只存一份动画节点的常量信息，也只存一份FoldProperty的信息。因此用FoldProperty标记的属性的真实数据是存在TArray<FAnimNodeData> UAnimBlueprintGeneratedClass::AnimNodeData中的。存在Class中，其实就是类似CDO的意思了。这么做的显然好处之一是节省内存。

自然的，不同的存储方式，自然要采用不同的访问方式。因此这些FoldProperty都是采用GET_ANIM_NODE_DATA来访问该数据。

测试代码：

```cpp
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FoldPropertyTest, meta = (FoldProperty))
	int32 MyInt_FoldProperty = 123;
```

测试结果：

![Untitled](FoldProperty/Untitled.png)

原理：

编译的时候会把该FoldProperty添加到FoldRecords里。如果这个属性不是动态，也没有暴露成引脚连接，则会被当作常量。

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