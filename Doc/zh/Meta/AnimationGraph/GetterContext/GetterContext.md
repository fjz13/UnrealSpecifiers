# GetterContext

- **功能描述：** 继续限定AnimGetter函数在哪个地方才可以使用，如果不填，则默认都可以用。
- **使用位置：** UFUNCTION
- **引擎模块：** AnimationGraph
- **元数据类型：** string="abc"
- **限制类型：** UAnimInstance及子类的AnimGetter函数
- **关联项：** [AnimGetter](../AnimGetter/AnimGetter.md)
- **常用程度：** ★★

继续限定AnimGetter函数在哪个地方才可以使用，如果不填，则默认都可以用。

选项有：Transition，CustomBlend，AnimGraph。

## 源码注释：

```cpp
	 * A context string can be provided in the GetterContext metadata and can contain any (or none) of the
	 * following entries separated by a pipe (|)
	 * Transition  - Only available in a transition rule
	 * AnimGraph   - Only available in an animgraph (also covers state anim graphs)
	 * CustomBlend - Only available in a custom blend graph
```

## 测试代码：

```cpp
UFUNCTION(BlueprintPure, Category = "Animation|Insider", meta = (BlueprintThreadSafe))
float MyGetStateWeight(int32 MachineIndex, int32 StateIndex);
public:
UFUNCTION(BlueprintPure, Category = "Animation|Insider", meta = (BlueprintInternalUseOnly = "true", AnimGetter, GetterContext = "Transition", BlueprintThreadSafe))
float MyGetStateWeight_AnimGetter_OnlyTransition(int32 MachineIndex, int32 StateIndex);

UFUNCTION(BlueprintPure, Category = "Animation|Insider", meta = (BlueprintInternalUseOnly = "true", AnimGetter, GetterContext = "CustomBlend", BlueprintThreadSafe))
float MyGetTransitionTimeElapsed_AnimGetter_OnlyCustomBlend(int32 MachineIndex, int32 TransitionIndex);
```

## 测试效果：

这个图要对比AnimGetter里的图来查看。

关注点一是在AnimGraph里的MyGetStateWeight_AnimGetter_OnlyTransition，如果不标GetterContext 则是可以调用的，但标上就只能在Transition里调用。同时也发现该函数不能在CustomBlend里调用。

二是在CustomBlend里。操作步骤是在Rule上右侧细节面板改为Custom然后进入CustomBlend的蓝图。在该蓝图下，MyGetStateWeight可以调用，因为并没有填写GetterContext。而MyGetTransitionTimeElapsed_AnimGetter_OnlyCustomBlend可以开始调用了。

![Untitled](Untitled.png)

## 原理：

判断能否调用的函数如下。

```cpp
bool UK2Node_AnimGetter::IsContextValidForSchema(const UEdGraphSchema* Schema) const
{
	if(Contexts.Num() == 0)
	{
		// Valid in all graphs
		return true;
	}

	for(const FString& Context : Contexts)
	{
		UClass* ClassToCheck = nullptr;
		if(Context == TEXT("CustomBlend"))
		{
			ClassToCheck = UAnimationCustomTransitionSchema::StaticClass();
		}

		if(Context == TEXT("Transition"))
		{
			ClassToCheck = UAnimationTransitionSchema::StaticClass();
		}

		if(Context == TEXT("AnimGraph"))
		{
			ClassToCheck = UAnimationGraphSchema::StaticClass();
		}

		return Schema->GetClass() == ClassToCheck;
	}

	return false;
}
```