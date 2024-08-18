# SequencerBindingResolverLibrary

功能描述: 把具有SequencerBindingResolverLibrary标记的UBlueprintFunctionLibrary作为动态绑定的类。
使用位置: UCLASS
Feature: Blueprint
引擎模块: Sequencer
元数据类型: bool
限制类型: UClass上，但一般是UBlueprintFunctionLibrary
Status: Done
常用程度: 2

把具有SequencerBindingResolverLibrary标记的UBlueprintFunctionLibrary作为动态绑定的类。只把它里面的函数添加到右键菜单里。

动态绑定是Sequencer的一个新功能，简单来说就是允许设定好的轨迹变化动态应用到运行时的其他Actor上，用来做Gameplay和Sequence的过度切换会很有用。更细致用法可以参考官方文档：[https://dev.epicgames.com/documentation/zh-cn/unreal-engine/dynamic-binding-in-sequencer](https://dev.epicgames.com/documentation/zh-cn/unreal-engine/dynamic-binding-in-sequencer)

测试代码：

```cpp
UCLASS(meta=(SequencerBindingResolverLibrary), MinimalAPI)
class UMySequencerBindingResolverLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/** Resolve the bound object to the player's pawn */
	UFUNCTION(BlueprintPure, Category="Sequencer|Insider", meta=(WorldContext="WorldContextObject"))
	static FMovieSceneDynamicBindingResolveResult ResolveToMyActor(UObject* WorldContextObject, FString ActorTag);
};
```

源码：

```cpp
UCLASS(meta=(SequencerBindingResolverLibrary), MinimalAPI)
class UBuiltInDynamicBindingResolverLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/** Resolve the bound object to the player's pawn */
	UFUNCTION(BlueprintPure, Category="Sequencer|Dynamic Binding", meta=(WorldContext="WorldContextObject"))
	static MOVIESCENE_API FMovieSceneDynamicBindingResolveResult ResolveToPlayerPawn(UObject* WorldContextObject, int32 PlayerControllerIndex = 0);
};

```

测试结果：

在没有定义UMySequencerBindingResolverLibrary 之前，引擎里有个内建的ResolveToPlayerPawn，可以把PlayerControllerIndex 解析为Pawn来动态绑定到玩家的Pawn。

因此我们也可以定义自己的动态绑定函数，来解析一个FString为一个Actor，如代码里ResolveToMyActor所示。

![Untitled](SequencerBindingResolverLibrary/Untitled.png)

原理：

FMovieSceneDynamicBindingCustomization会搜索引擎里的所有类，但为了缩减范围，因此只有在标有SequencerBindingResolverLibrary的类下面才去发现Resolver函数。

```cpp
void FMovieSceneDynamicBindingCustomization::CollectResolverLibraryBindActions(UBlueprint* Blueprint, FBlueprintActionMenuBuilder& MenuBuilder, bool bIsRebinding)
{
	// Add any class that has the "SequencerBindingResolverLibrary" meta as a target class.
//
// We don't consider *all* blueprint function libraries because there are many, many of them that expose
// functions that are, technically speaking, compatible with bound object resolution (i.e. they return
// a UObject pointer) but that are completely non-sensical in this context.
const static FName SequencerBindingResolverLibraryMeta("SequencerBindingResolverLibrary");
for (TObjectIterator<UClass> ClassIt; ClassIt; ++ClassIt)
{
	UClass* CurrentClass = *ClassIt;
	if (CurrentClass->HasMetaData(SequencerBindingResolverLibraryMeta))
	{
		FBlueprintActionFilter::Add(MenuFilter.TargetClasses, CurrentClass);
	}
}
}
```