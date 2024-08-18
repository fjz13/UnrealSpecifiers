# AnimGetter

功能描述: 指定UAnimInstance及子类的该函数成为一个AnimGetter函数。
使用位置: UFUNCTION
Feature: Blueprint
引擎模块: AnimationGraph
元数据类型: bool
限制类型: UAnimInstance及子类的函数
Status: Done
Sub-item: GetterContext (GetterContext.md)
常用程度: 3

指定UAnimInstance及子类的该函数成为一个AnimGetter函数。

- 在一些情况下会继承UAnimInstance创建自己的动画蓝图子类，然后里面可以自己做一些优化，或者添加一些自己的功能函数。
- 所谓的AnimGetter，其实就是会被UK2Node_AnimGetter识别并包装成该蓝图节点的函数。识别的范围是在UAnimInstance及子类（就是动画蓝图）的C++函数。
- AnimGetter还有两个额外功能：一是会自动根据当前上下文填充函数里的AssetPlayerIndex，MachineIndex，StateIndex，TransitionIndex和参数。二是会根据GetterContext把该函数限定只能在某些蓝图里调用。普通的蓝图函数不具有这些便利的功能和检查，用起来就不够智能。
- 要成为AnimGetter还必须具有：
    - AnimGetter，自然不必说
    - BlueprintThreadSafe，才能在动画蓝图里调用，多线程安全
    - BlueprintPure，成为一个存获取值的函数
    - BlueprintInternalUseOnly = "true”，避免再生成一个默认的蓝图节点，只用UK2Node_AnimGetter包装而成的那个。

测试代码：

```cpp
UCLASS(BlueprintType)
class INSIDER_API UMyAnimInstance :public UAnimInstance
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "Animation|Insider", meta = (BlueprintInternalUseOnly = "true", AnimGetter, BlueprintThreadSafe))
	float MyGetAnimationLength_AnimGetter(int32 AssetPlayerIndex);

	UFUNCTION(BlueprintPure, Category = "Animation|Insider", meta = (BlueprintThreadSafe))
	float MyGetAnimationLength(int32 AssetPlayerIndex);
public:
	UFUNCTION(BlueprintPure, Category = "Animation|Insider", meta = (BlueprintInternalUseOnly = "true", AnimGetter, BlueprintThreadSafe))
	float MyGetStateWeight_AnimGetter(int32 MachineIndex, int32 StateIndex);

	UFUNCTION(BlueprintPure, Category = "Animation|Insider", meta = (BlueprintThreadSafe))
	float MyGetStateWeight(int32 MachineIndex, int32 StateIndex);
public:
	UFUNCTION(BlueprintPure, Category = "Animation|Insider", meta = (BlueprintInternalUseOnly = "true", AnimGetter, BlueprintThreadSafe))
	float MyGetTransitionTimeElapsed_AnimGetter(int32 MachineIndex, int32 TransitionIndex);

	UFUNCTION(BlueprintPure, Category = "Animation|Insider", meta = (BlueprintThreadSafe))
	float MyGetTransitionTimeElapsed(int32 MachineIndex, int32 TransitionIndex);
};

```

测试效果：

分别定义使用了AssetPlayerIndex，MachineIndex，StateIndex，TransitionIndex的AnimGetter函数以及普通蓝图函数作为对比。分别查看在动画蓝图里几个作用域里的用法。

- 可见在不管什么作用域，普通蓝图函数都可以调用（毕竟没有做Context的检查）。另外AssetPlayerIndex等参数都没有被自动填充，这几乎是没法用的，因为用户其实并不太懂如何去手填这些Index，最好是交给编译器来填充。
- 图里高亮的是可以调用的AnimGetter函数。细看的话，可以分析发现规则是只有能正确填充AssetPlayerIndex等参数的才能调用。因此在Transition里能调用的最多，因为这个时候最叶子节点，有动画，又有状态机和Transition节点。

![Untitled](AnimGetter/Untitled.png)

原理：

分析函数上的AnimGetter标记并且生成蓝图节点的功能基本都在UK2Node_AnimGetter这个类里。大家可自行查看。

```cpp
void UK2Node_AnimGetter::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
			TArray<UFunction*> AnimGetters;
			for(TFieldIterator<UFunction> FuncIter(BPClass) ; FuncIter ; ++FuncIter)
			{
				UFunction* Func = *FuncIter;

				if(Func->HasMetaData(TEXT("AnimGetter")) && Func->HasAnyFunctionFlags(FUNC_Native))
				{
					AnimGetters.Add(Func);
				}
			}
}
```