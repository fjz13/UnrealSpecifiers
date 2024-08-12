# Latent

Usage: UFUNCTION
Feature: Blueprint
Type: bool
Description: 标明一个函数是一个延迟异步操作
Status: Done
Group: Blueprint
Sub-item: LatentInfo (LatentInfo.md), NeedsLatentFixup (NeedsLatentFixup.md), LatentCallbackTarget (LatentCallbackTarget.md)

标明一个函数是一个延迟异步操作，需要配合LatentInfo来使用。

会导致在逻辑执行上Then（也叫Complete）引脚需要手动触发（引擎内部触发），且函数右上角增加时钟的图标。

测试代码：

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

蓝图效果：

![Untitled](Latent/Untitled.png)

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