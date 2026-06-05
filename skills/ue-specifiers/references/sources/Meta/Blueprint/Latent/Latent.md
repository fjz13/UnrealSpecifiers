---
title: "Latent"
id: "meta.Latent"
kind: "meta"
symbol: "Latent"
category: "Blueprint"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "标明一个函数是一个延迟异步操作"
usage: "UFUNCTION"
---

# Latent

## Decision Summary

- **Use when:** BlueprintCallable 函数是 latent action，需要暂停并稍后恢复执行流。
- **Do not use when:** 函数只是同步执行、异步回调、delegate 通知或普通 async C++ 操作。
- **Requires:** 通常需要 `LatentInfo` 参数并符合 Blueprint latent 函数约定。
- **Conflicts:** 不要和普通 pure/query 函数语义混用。
- **Prefer instead:** 简单异步通知用 delegate/event；同步命令用普通 `BlueprintCallable`。

- **功能描述：** 标明一个函数是一个延迟异步操作
- **使用位置：** UFUNCTION
- **引擎模块：** Blueprint
- **元数据类型：** bool
- **关联项：** [LatentInfo](LatentInfo.md), [NeedsLatentFixup](NeedsLatentFixup.md), [LatentCallbackTarget](LatentCallbackTarget.md)
- **常用程度：** ★★★★★

标明一个函数是一个延迟异步操作，需要配合LatentInfo来使用。

会导致在逻辑执行上Then（也叫Complete）引脚需要手动触发（引擎内部触发），且函数右上角增加时钟的图标。

## 测试代码：

```cpp
class FMySleepAction : public FPendingLatentAction
{
public:
	float TimeRemaining;
	FName ExecutionFunction;
	int32 OutputLink;
	FWeakObjectPtr CallbackTarget;

	FMySleepAction(float Duration, const FLatentActionInfo& LatentInfo)
		: TimeRemaining(Duration)
		, ExecutionFunction(LatentInfo.ExecutionFunction)
		, OutputLink(LatentInfo.Linkage)
		, CallbackTarget(LatentInfo.CallbackTarget)
	{
	}

	virtual void UpdateOperation(FLatentResponse& Response) override
	{
		TimeRemaining -= Response.ElapsedTime();
		Response.FinishAndTriggerIf(TimeRemaining <= 0.0f, ExecutionFunction, OutputLink, CallbackTarget);
	}
};

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyFunction_Latent :public UBlueprintFunctionLibrary
{
public:
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, meta = (Latent, WorldContext = "WorldContextObject", LatentInfo = "LatentInfo", Duration = "5"))
	static void	MySleep(const UObject* WorldContextObject, float Duration, FLatentActionInfo LatentInfo)
	{
			if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
			{
				FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
				if (LatentActionManager.FindExistingAction<FMySleepAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL)
				{
					LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, new FMySleepAction(Duration, LatentInfo));
				}
			}
}

	UFUNCTION(BlueprintCallable, meta = (Latent, WorldContext = "WorldContextObject", Duration = "5"))
	static void	MySleep2(const UObject* WorldContextObject, float Duration, FLatentActionInfo LatentInfo);
};
```

## 蓝图效果：


MySleep可以像Delay一样正常工作。但是MySleep2因为没有标明LatentInfo，因此LatentInfo函数参数没有被蓝图系统赋值，导致无法工作。

在源码里Latent使用的非常频繁，最常见的例子：

```cpp
UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject", Latent = "", LatentInfo = "LatentInfo", DisplayName = "Load Stream Level (by Name)"), Category="Game")
static ENGINE_API void LoadStreamLevel(const UObject* WorldContextObject, FName LevelName, bool bMakeVisibleAfterLoad, bool bShouldBlockOnLoad, FLatentActionInfo LatentInfo);

UFUNCTION(BlueprintCallable, meta = (Latent, LatentInfo = "LatentInfo", WorldContext = "WorldContextObject", BlueprintInternalUseOnly = "true"), Category = "Utilities")
static ENGINE_API void LoadAsset(const UObject* WorldContextObject, TSoftObjectPtr<UObject> Asset, FOnAssetLoaded OnLoaded, FLatentActionInfo LatentInfo);

UFUNCTION(BlueprintCallable, Category="Utilities|FlowControl", meta=(Latent, WorldContext="WorldContextObject", LatentInfo="LatentInfo", Duration="0.2", Keywords="sleep"))
static ENGINE_API void	Delay(const UObject* WorldContextObject, float Duration, struct FLatentActionInfo LatentInfo );
```

关于使用Latent还是继承自UBlueprintAsyncActionBase来创建蓝图异步节点的差异，可以在网上别的文章查看。

## 行为

UE5.8 function metadata；Blueprint latent function 标记。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `ObjectMacros.h` metadata declaration/comment
  - UE5.8 `BlueprintGraph` metadata constants or node usage

## 常见误用

参数名、属性名或目标宏写错导致 metadata 被保留但没有对应编辑器/Blueprint 行为。
