# BlueprintInternalUseOnly

Type: bool
Feature: Blueprint, UHT
Description: 指示不应向最终用户公开此函数。蓝图内部调用，不暴露给终端用户。。。
MetaOperation: =true
Meta: BlueprintInternalUseOnly (../../Meta/Meta/BlueprintInternalUseOnly.md), BlueprintType (../../Meta/Meta/BlueprintType.md)
Status: Done

等价于meta里加上BlueprintInternalUseOnly = true，看文章和代码解释这是用在蓝图异步节点上。

用来阻止BlueprintCallable自动生成蓝图节点，因此一般配合：

- [ ]  CustomThunk阻止UHT生成exec函数，然后自己自定义execAddChooserStructInput。也有普通的函数在使用，配合DECLARE_FUNCTION(execAddChooserStructInput);自己定义，CustomThunk配合。具体见CustomChunk
- [x]  UBlueprintAsyncActionBase使用。另一种异步的方式是UFUNCTION的Latent
- [x]  类继承于UGameplayTask，meta = (ExposedAsyncProxy=AsyncTask)，也是同理被UK2Node_LatentAbilityCall里面的GetMenuActions识别然后添加工厂方法的
- [x]  普通函数，隐藏不被用户在蓝图中直接调用（指的是用户直接右键敲出函数名来调用）。已生成UFunction，但是不被蓝图调用

未知：

```cpp
UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", HideSelfPin = "true", HidePin = "Action"))
	FInputActionValue GetBoundActionValue(const UInputAction* Action) const;

UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe, BlueprintInternalUseOnly = "true", DeterminesOutputType = "ObjectClass"))
	static UObject* EvaluateChooser(const UObject* ContextObject, const UChooserTable* ChooserTable, TSubclassOf<UObject> ObjectClass);

UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UAbilityTask_PerformTargeting* PerformTargetingRequest(UGameplayAbility* OwningAbility, UTargetingPreset* InTargetingPreset, bool bAllowAsync);

UFUNCTION(BlueprintCallable, Category = "Connections", meta = (BlueprintInternalUseOnly = "true"))
	void K2_SetCurrentState(FName NewState) { SetCurrentState(NewState); }

UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category = GameplayCue, meta = (BlueprintInternalUseOnly = "true"))
void BlueprintCustomHandler(EGameplayCueEvent::Type EventType, const FGameplayCueParameters& Parameters);

UFUNCTION(BlueprintPure, meta = (BlueprintInternalUseOnly = "TRUE"), Category = "DMX")
UDMXEntityFixtureType* GetFixtureType(FDMXEntityFixtureTypeRef InFixtureType);

/** Get a DMX Subsystem, pure version */
UFUNCTION(BlueprintPure, Category = "DMX Subsystem", meta = (BlueprintInternalUseOnly = "true"))
static UDMXSubsystem* GetDMXSubsystem_Pure();

/** Get a DMX Subsystem, callable version */
UFUNCTION(BlueprintCallable, Category = "DMX Subsystem", meta = (BlueprintInternalUseOnly = "true"))
static UDMXSubsystem* GetDMXSubsystem_Callable();

UFUNCTION( BlueprintPure, BlueprintCosmetic, Category = BlueprintContext,
	           meta = ( WorldContext = "ContextObject", BlueprintInternalUseOnly = "true" ) )
	static USubsystem* GetContext( UObject* ContextObject, TSubclassOf< USubsystem > Class );
```

参考：[https://neil3d.github.io/unreal/bp-async.html#blueprint-async-action](https://neil3d.github.io/unreal/bp-async.html#blueprint-async-action)

1，在普通函数是否加BlueprintInternalUseOnly 产生的gen.cpp对比的时候，发现产生差异的只有meta的值。

2，在源码中搜索BlueprintInternalUseOnly  meta的使用，发现

```cpp
//不允许用户调用该函数
bool UEdGraphSchema_K2::CanUserKismetCallFunction(const UFunction* Function)
{
	return Function && 
		(Function->HasAllFunctionFlags(FUNC_BlueprintCallable) && 
!Function->HasAllFunctionFlags(FUNC_Delegate) && 
!Function->GetBoolMetaData(FBlueprintMetadata::MD_BlueprintInternalUseOnly) && 

(!Function->HasMetaData(FBlueprintMetadata::MD_DeprecatedFunction) || 
GetDefault<UBlueprintEditorSettings>()->bExposeDeprecatedFunctions));
}
//不允许用户重载该函数
bool UEdGraphSchema_K2::CanKismetOverrideFunction(const UFunction* Function)
{
	return  
		Function && 
		(
			Function->HasAllFunctionFlags(FUNC_BlueprintEvent)
			&& !Function->HasAllFunctionFlags(FUNC_Delegate) && 
			!Function->GetBoolMetaData(FBlueprintMetadata::MD_BlueprintInternalUseOnly) && 
			(!Function->HasMetaData(FBlueprintMetadata::MD_DeprecatedFunction) || GetDefault<UBlueprintEditorSettings>()->bExposeDeprecatedFunctions)
		);
}
```

因此，对于测试代码：

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyFunction_Internal :public AActor
{
public:
	GENERATED_BODY()
public:
	//(BlueprintInternalUseOnly = true, BlueprintType = true, ModuleRelativePath = Function/MyFunction_Internal.h)
	//FunctionFlags:	FUNC_Final | FUNC_Native | FUNC_Public | FUNC_BlueprintCallable 
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void MyFunc_InternalOnly() {}

	//FunctionFlags:	FUNC_Final | FUNC_Native | FUNC_Public | FUNC_BlueprintCallable 
	UFUNCTION(BlueprintCallable)
	void MyFunc_Default() {}
};
```

但是在蓝图中只有MyFunc_Default是可以调用的。因此可以理解为这个函数依然暴露到蓝图，但是却又被隐藏起来了。不能让用户自己直接调用，但是可以在代码里通过查找函数名之类的间接可以调用到。但一般情况下，隐藏函数有什么作用用途吗？猜测作用是可以通过函数名反射来调用。

![Untitled](BlueprintInternalUseOnly/Untitled.png)

在源码里找到一个示例，因此这个GetLevelScriptActor函数，可以不在蓝图中被调用，但是有可以通过名字查找到。方便生成一个UFunction以被注入到别的地方作为callback

```cpp
ULevelStreaming:
UFUNCTION(BlueprintPure, meta = (BlueprintInternalUseOnly = "true"))
ENGINE_API ALevelScriptActor* GetLevelScriptActor();

然后发现：
GetLevelScriptActorNode->SetFromFunction(ULevelStreaming::StaticClass()->FindFunctionByName(GET_FUNCTION_NAME_CHECKED(ULevelStreaming, GetLevelScriptActor)));
```

默认情况下，BlueprintCallable/Pure的函数会生成UK2Node_CallFunction来调用。但BlueprintInternalUseOnly阻止了这一部分。

---

关于UBlueprintAsyncActionBase的使用，UK2Node_BaseAsyncTask的函数实现里体现了书写继承于UBlueprintAsyncActionBase的规则，简单来说就是通过static 函数来当作Factory function，然后分析这个Proxy类的Delegate property来当作Pin。

如果不加BlueprintInternalUseOnly = "true”，则会生成两个函数。下面那个是普通static函数的生成。上面那个是分析UBlueprintAsyncActionBase生成的函数。

其中识别UBlueprintAsyncActionBase里面static函数作为FactoryFunction的流程是，BlueprintActionDatabaseImpl::GetNodeSpecificActions会触发UK2Node_AsyncAction::GetMenuActions，从而ActionRegistrar.RegisterClassFactoryActions，内部再判断RegisterClassFactoryActions_Utils::IsFactoryMethod(Function, UBlueprintAsyncActionBase)会通过（判断是static函数，并且返回类型是UBlueprintAsyncActionBase的子类对象），继而继续通过回调UBlueprintFunctionNodeSpawner::Create(FactoryFunc);创建一个工厂方法的nodeSpawner。

因此总结，此时的BlueprintInternalUseOnly 就是隐藏掉默认生成的那个。

![Untitled](BlueprintInternalUseOnly/Untitled%201.png)

---

By default, all BlueprintCallable/Pure UFUNCTIONS have blueprint nodes generated for them, of type UK2Node_CallFunction. That meta flag suppresses this.

There are many other types of blueprint node though. In this case, the default behaviour has been suppressed so that a customized node can be used instead - UK2Node_AIMoveTo. The implementation of that node will provide a call to the UFUNCTION.

BlueprintInternalUseOnly is a flag that allows a function to be called from blueprint in a very specific way and not by people editing the blueprint.

Normally the engine automatically makes blueprint nodes for any blueprint callable function. There is also a special process to create special nodes for the static functions of the Async classes. These are not function calls but "latent" nodes (indicated by the little watch icon in the upper right). 有一个专门的流程来处理异步节点流程

The flag prevents the first process from creating blueprint nodes based just on the function (since as you notice they won't work). The flag is needed since the function needs to be marked as BlueprintCallable to be used by the special async node and without it there's no way for the engine to know that it should skip it.