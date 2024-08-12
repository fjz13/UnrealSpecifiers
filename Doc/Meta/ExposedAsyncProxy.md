# ExposedAsyncProxy

Description: 在 Async Task 节点中公开此类的一个代理对象。
Usage: UCLASS
Feature: Blueprint
Group: Blueprint
Type: string="abc"
LimitedType: Async Blueprint node
Example: meta = (ExposedAsyncProxy = AsyncObjectName)
Status: Done
Sub-item: HideSpawnParms (HideSpawnParms.md), HasDedicatedAsyncNode (HasDedicatedAsyncNode.md), HideThen (HideThen.md)

在UK2Node_BaseAsyncTask中使用，用来为蓝图异步节点暴露一个异步对象引脚，以支持对这个异步行为的进一步操作。

在源码里的用处一是UBlueprintAsyncActionBase的子类，二是UGameplayTask子类，皆是分别会有另外的UK2Node_BaseAsyncTask以及UK2Node_LatentGameplayTaskCall来解析类的声明定义并包装生成相应的异步蓝图节点。

基类都是继承自UBlueprintAsyncActionBase。利用ExposedAsyncProxy 指定异步任务对象的名字。在异步蓝图节点上继续返回异步对象，可以在之后支持取消该异步操作。

测试代码：

UCancellableAsyncAction是引擎提供的继承自UBlueprintAsyncActionBase的一个便利的子类。UMyFunction_Async 定义了一个蓝图异步节点DelayLoop。

```cpp
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDelayOutputPin);
UCLASS(Blueprintable, BlueprintType,meta = (ExposedAsyncProxy = MyAsyncObject))
class INSIDER_API UMyFunction_Async :public UBlueprintAsyncActionBase
{
public:
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FDelayOutputPin Loop;

	UPROPERTY(BlueprintAssignable)
	FDelayOutputPin Complete;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Flow Control")
	static UMyFunction_Async* DelayLoop(const UObject* WorldContextObject, const float DelayInSeconds, const int Iterations);

	virtual void Activate() override;

	UFUNCTION()
	static void Test();
private:
	const UObject* WorldContextObject = nullptr;
	float MyDelay = 0.f;
	int MyIterations = 0;
	bool Active = false;

	UFUNCTION()
	void ExecuteLoop();

	UFUNCTION()
	void ExecuteComplete();
};
```

默认的蓝图节点是：

如果UMyFunction_Async 直接继承自UBlueprintAsyncActionBase，并且没有设置ExposedAsyncProxy，则生成的蓝图异步节点为为下图。

![Untitled](ExposedAsyncProxy/Untitled.png)

而如果继承自UCancellableAsyncAction (提供了Cancel方法)，并且设置ExposedAsyncProxy 为自己想要的AsyncObject引脚名称。

```cpp
UCLASS(Abstract, BlueprintType, meta = (ExposedAsyncProxy = AsyncAction), MinimalAPI)
class UCancellableAsyncAction : public UBlueprintAsyncActionBase
{
	UFUNCTION(BlueprintCallable, Category = "Async Action")
	ENGINE_API virtual void Cancel();
}

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDelayOutputPin);
UCLASS(Blueprintable, BlueprintType,meta = (ExposedAsyncProxy = MyAsyncObject))
class INSIDER_API UMyFunction_Async :public UCancellableAsyncAction 
{}
```

修改后的效果如下图：修改后：

![Untitled](ExposedAsyncProxy/Untitled%201.png)

该Meta在源码中发生的位置：

```cpp
void UK2Node_BaseAsyncTask::AllocateDefaultPins()
{
	bool bExposeProxy = false;
	bool bHideThen = false;
	FText ExposeProxyDisplayName;
	for (const UStruct* TestStruct = ProxyClass; TestStruct; TestStruct = TestStruct->GetSuperStruct())
	{
		bExposeProxy |= TestStruct->HasMetaData(TEXT("ExposedAsyncProxy"));
		bHideThen |= TestStruct->HasMetaData(TEXT("HideThen"));
		if (ExposeProxyDisplayName.IsEmpty())
		{
			ExposeProxyDisplayName = TestStruct->GetMetaDataText(TEXT("ExposedAsyncProxy"));
		}
	}

	if (bExposeProxy)
	{
		UEdGraphPin* ProxyPin = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Object, ProxyClass, FBaseAsyncTaskHelper::GetAsyncTaskProxyName());
		if (!ExposeProxyDisplayName.IsEmpty())
		{
			ProxyPin->PinFriendlyName = ExposeProxyDisplayName;
		}
	}

}
```