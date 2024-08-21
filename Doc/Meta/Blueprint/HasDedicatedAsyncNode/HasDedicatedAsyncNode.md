# HasDedicatedAsyncNode

- **使用位置：** UCLASS
- **元数据类型：** bool
- **关联项：** [ExposedAsyncProxy](../ExposedAsyncProxy/ExposedAsyncProxy.md)

隐藏UBlueprintAsyncActionBase子类里工厂方法自动生成的蓝图异步节点，以便自己可以手动自定义创建一个相应的UK2Node_XXX。

```cpp
/**
* BlueprintCallable factory functions for classes which inherit from UBlueprintAsyncActionBase will have a special blueprint node created for it: UK2Node_AsyncAction
* You can stop this node spawning and create a more specific one by adding the UCLASS metadata "HasDedicatedAsyncNode"
*/

UCLASS(MinimalAPI)
class UBlueprintAsyncActionBase : public UObject
{}
```

## 测试代码：

```cpp
UCLASS(Blueprintable, BlueprintType,meta = (ExposedAsyncProxy = MyAsyncObject,HasDedicatedAsyncNode))
class INSIDER_API UMyFunction_Async :public UCancellableAsyncAction
{}

//可以自定义一个K2Node
UCLASS()
class INSIDER_API UK2Node_MyFunctionAsyncAction : public UK2Node_AsyncAction
{
	GENERATED_BODY()

	// UK2Node interface
	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
	virtual void AllocateDefaultPins() override;
	// End of UK2Node interface

protected:
	virtual bool HandleDelegates(
		const TArray<FBaseAsyncTaskHelper::FOutputPinAndLocalVariable>& VariableOutputs, UEdGraphPin* ProxyObjectPin,
		UEdGraphPin*& InOutLastThenPin, UEdGraph* SourceGraph, FKismetCompilerContext& CompilerContext) override;
};

void UK2Node_MyFunctionAsyncAction::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	struct GetMenuActions_Utils
	{
		static void SetNodeFunc(UEdGraphNode* NewNode, bool /*bIsTemplateNode*/, TWeakObjectPtr<UFunction> FunctionPtr)
		{
			UK2Node_MyFunctionAsyncAction* AsyncTaskNode = CastChecked<UK2Node_MyFunctionAsyncAction>(NewNode);
			if (FunctionPtr.IsValid())
			{
				UFunction* Func = FunctionPtr.Get();
				FObjectProperty* ReturnProp = CastFieldChecked<FObjectProperty>(Func->GetReturnProperty());

				AsyncTaskNode->ProxyFactoryFunctionName = Func->GetFName();
				AsyncTaskNode->ProxyFactoryClass = Func->GetOuterUClass();
				AsyncTaskNode->ProxyClass = ReturnProp->PropertyClass;
				AsyncTaskNode->NodeComment = TEXT("This is MyCustomK2Node");
			}
		}
	};

	UClass* NodeClass = GetClass();
	ActionRegistrar.RegisterClassFactoryActions<UMyFunction_Async>(FBlueprintActionDatabaseRegistrar::FMakeFuncSpawnerDelegate::CreateLambda([NodeClass](const UFunction* FactoryFunc)->UBlueprintNodeSpawner*
		{
			UBlueprintNodeSpawner* NodeSpawner = UBlueprintFunctionNodeSpawner::Create(FactoryFunc);
			check(NodeSpawner != nullptr);
			NodeSpawner->NodeClass = NodeClass;

			TWeakObjectPtr<UFunction> FunctionPtr = MakeWeakObjectPtr(const_cast<UFunction*>(FactoryFunc));
			NodeSpawner->CustomizeNodeDelegate = UBlueprintNodeSpawner::FCustomizeNodeDelegate::CreateStatic(GetMenuActions_Utils::SetNodeFunc, FunctionPtr);

			return NodeSpawner;
		}));
}

void UK2Node_MyFunctionAsyncAction::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();
}

bool UK2Node_MyFunctionAsyncAction::HandleDelegates(const TArray<FBaseAsyncTaskHelper::FOutputPinAndLocalVariable>& VariableOutputs, UEdGraphPin* ProxyObjectPin, UEdGraphPin*& InOutLastThenPin, UEdGraph* SourceGraph, FKismetCompilerContext& CompilerContext)
{
	bool bIsErrorFree = true;

	for (TFieldIterator<FMulticastDelegateProperty> PropertyIt(ProxyClass); PropertyIt && bIsErrorFree; ++PropertyIt)
	{
		UEdGraphPin* LastActivatedThenPin = nullptr;
		bIsErrorFree &= FBaseAsyncTaskHelper::HandleDelegateImplementation(*PropertyIt, VariableOutputs, ProxyObjectPin, InOutLastThenPin, LastActivatedThenPin, this, SourceGraph, CompilerContext);
	}

	return bIsErrorFree;
}

```

## 蓝图效果：

左侧是引擎自带的UK2Node_AsyncAction生成节点，右边是自定义的UK2Node_MyFunctionAsyncAction生成的蓝图节点，虽然功能一致，但是右边额外加了个注释以便区分。有了这个基础，你也可以在其中继续重载方法进一步自定义。

![Untitled](Untitled.png)

## 当前在源码里有两处地方使用：

```cpp
UCLASS(BlueprintType, meta = (ExposedAsyncProxy = "AsyncTask", HasDedicatedAsyncNode))
class GAMEPLAYMESSAGES_API UAsyncAction_RegisterGameplayMessageReceiver : public UBlueprintAsyncActionBase
{
	UFUNCTION(BlueprintCallable, Category = Messaging, meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
	static UAsyncAction_RegisterGameplayMessageReceiver* RegisterGameplayMessageReceiver(UObject* WorldContextObject, FEventMessageTag Channel, UScriptStruct* PayloadType, EGameplayMessageMatchType MatchType = EGameplayMessageMatchType::ExactMatch, AActor* ActorContext = nullptr);

}
//由UK2Node_GameplayMessageAsyncAction来负责创建
void UK2Node_GameplayMessageAsyncAction::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	//...
	UClass* NodeClass = GetClass();
	ActionRegistrar.RegisterClassFactoryActions<UAsyncAction_RegisterGameplayMessageReceiver>(FBlueprintActionDatabaseRegistrar::FMakeFuncSpawnerDelegate::CreateLambda([NodeClass](const UFunction* FactoryFunc)->UBlueprintNodeSpawner*
	{
		UBlueprintNodeSpawner* NodeSpawner = UBlueprintFunctionNodeSpawner::Create(FactoryFunc);
		check(NodeSpawner != nullptr);
		NodeSpawner->NodeClass = NodeClass;

		TWeakObjectPtr<UFunction> FunctionPtr = MakeWeakObjectPtr(const_cast<UFunction*>(FactoryFunc));
		NodeSpawner->CustomizeNodeDelegate = UBlueprintNodeSpawner::FCustomizeNodeDelegate::CreateStatic(GetMenuActions_Utils::SetNodeFunc, FunctionPtr);

		return NodeSpawner;
	}) );
}

UCLASS(BlueprintType, meta=(ExposedAsyncProxy = "AsyncTask", HasDedicatedAsyncNode))
class UMovieSceneAsyncAction_SequencePrediction : public UBlueprintAsyncActionBase
{
	UFUNCTION(BlueprintCallable, Category=Cinematics)
	static UMovieSceneAsyncAction_SequencePrediction* PredictWorldTransformAtTime(UMovieSceneSequencePlayer* Player, USceneComponent* TargetComponent, float TimeInSeconds);
}
```

## 生成的蓝图：

UAsyncAction_RegisterGameplayMessageReceiver由自定义的UK2Node_GameplayMessageAsyncAction来创建蓝图节点，从而提供了一个泛型的Payload输出引脚。而UMovieSceneAsyncAction_SequencePrediction 里的工厂方法PredictWorldTransformAtTime，由于隐藏了自动生成的版本，又没有加上BlueprintInternalUseOnly来抑制UHT生成的版本，因此最终呈现的是普通版本的静态函数蓝图节点。

## ![Untitled](Untitled%201.png)

## 源码里的作用机制：

可以看到，如果在类上有找到HasDedicatedAsyncNode，直接就返回nullptr，不再生成NodeSpawner，因此就阻止了蓝图节点的生成。

```cpp
void UK2Node_AsyncAction::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	ActionRegistrar.RegisterClassFactoryActions<UBlueprintAsyncActionBase>(FBlueprintActionDatabaseRegistrar::FMakeFuncSpawnerDelegate::CreateLambda([NodeClass](const UFunction* FactoryFunc)->UBlueprintNodeSpawner*
	{
		UClass* FactoryClass = FactoryFunc ? FactoryFunc->GetOwnerClass() : nullptr;
		if (FactoryClass && FactoryClass->HasMetaData(TEXT("HasDedicatedAsyncNode")))
		{
			// Wants to use a more specific blueprint node to handle the async action
			return nullptr;
		}
	
		UBlueprintNodeSpawner* NodeSpawner = UBlueprintFunctionNodeSpawner::Create(FactoryFunc);
		check(NodeSpawner != nullptr);
		NodeSpawner->NodeClass = NodeClass;
	
		TWeakObjectPtr<UFunction> FunctionPtr = MakeWeakObjectPtr(const_cast<UFunction*>(FactoryFunc));
		NodeSpawner->CustomizeNodeDelegate = UBlueprintNodeSpawner::FCustomizeNodeDelegate::CreateStatic(GetMenuActions_Utils::SetNodeFunc, FunctionPtr);
	
		return NodeSpawner;
	}) );
}
```
