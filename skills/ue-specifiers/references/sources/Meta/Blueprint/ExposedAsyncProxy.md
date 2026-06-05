---
title: "ExposedAsyncProxy"
id: "meta.ExposedAsyncProxy"
kind: "meta"
symbol: "ExposedAsyncProxy"
category: "Blueprint"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "在 Async Task 节点中公开此类的一个代理对象"
usage: "UCLASS"
---

# ExposedAsyncProxy

## Decision Summary

- **Use when:** `ExposedAsyncProxy` metadata 的 `UCLASS` 场景需要：在 Async Task 节点中公开此类的一个代理对象。
- **Do not use when:** 目标声明不属于 `UCLASS`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** 目标类应符合 `UBlueprintAsyncActionBase`/`UCancellableAsyncAction` 或 GameplayTask 异步节点路径；工厂函数和输出 delegate 仍需按 async action 模式声明。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 在 Async Task 节点中公开此类的一个代理对象。
- **使用位置：** UCLASS
- **引擎模块：** Blueprint
- **元数据类型：** string="abc"
- **限制类型：** Async Blueprint node
- **关联项：** [HideSpawnParms](Param/HideSpawnParms.md), [HasDedicatedAsyncNode](HasDedicatedAsyncNode.md), [HideThen](HideThen.md)
- **常用程度：** ★★★

在UK2Node_BaseAsyncTask中使用，用来为蓝图异步节点暴露一个异步对象引脚，以支持对这个异步行为的进一步操作。

在源码里的用处一是UBlueprintAsyncActionBase的子类，二是UGameplayTask子类，皆是分别会有另外的UK2Node_BaseAsyncTask以及UK2Node_LatentGameplayTaskCall来解析类的声明定义并包装生成相应的异步蓝图节点。

基类都是继承自UBlueprintAsyncActionBase。利用ExposedAsyncProxy 指定异步任务对象的名字。在异步蓝图节点上继续返回异步对象，可以在之后支持取消该异步操作。

## 测试代码：

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

## 默认的蓝图节点是：

如果UMyFunction_Async 直接继承自UBlueprintAsyncActionBase，并且没有设置ExposedAsyncProxy，则生成的蓝图异步节点为为下图。


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

## 修改后的效果如下图：


## 该Meta在源码中发生的位置：

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

## 行为

UE5.8 class metadata；用于 async task node 暴露 proxy 对象。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `ObjectMacros.h` metadata declaration/comment
  - UE5.8 `BlueprintGraph` metadata constants or node usage

## 常见误用

参数名、属性名或目标宏写错导致 metadata 被保留但没有对应编辑器/Blueprint 行为。
