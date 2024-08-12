# Variadic

Description: 标识一个函数可以接受任意类型的多个参数（包括input/output)．
Type: bool
Feature: Blueprint, UHT
MetaOperation: ＝””
Meta: Variadic (../../Meta/Meta/Variadic.md)
Status: Done

Marks a UFUNCTION as accepting variadic arguments. Variadic functions may have extra terms they need to emit after the main set of function arguments。These are all considered wildcards so no type checking will be performed on them。

在源码中搜索应用：然后配合UK2Node_ExecutePythonScript

```cpp
UFUNCTION(BlueprintCallable, CustomThunk, Category = "Python|Execution", meta=(Variadic, BlueprintInternalUseOnly="true"))
    static bool ExecutePythonScript(UPARAM(meta=(MultiLine=True)) const FString& PythonScript, const TArray<FString>& PythonInputs, const TArray<FString>& PythonOutputs);
	DECLARE_FUNCTION(execExecutePythonScript);
```

蓝图的效果：

![Untitled](Variadic/Untitled.png)

![Untitled](Variadic/Untitled%201.png)

CallFunc_MakeVector_ReturnValue:(X=1.000000,Y=2.000000,Z=3.000000)
CallFunc_MakeLiteralDouble_ReturnValue:456.000000

普通的CustomThunk函数还有一些限制，参数名字和个数是在UFuntion里写死的，不能支持动态的个数。

目前，想使用**Variadic**功能，需要自定义蓝图节点用C++来为**K2Node_CallFunction**添加引脚。

想必是想要开发来同时实现**K2Node**以及对应的**CustomThunk**+**Variadic**方法，来保证使用上的安全性。

BlueprintInternalUseOnly也要加上，否则会自动生成普通的蓝图函数，达不到variadic的效果。

以下是不加BlueprintInternalUseOnly自动生成的版本:

![Untitled](Variadic/Untitled%202.png)

实际应该是：

![Untitled](Variadic/Untitled%203.png)

和Ｗildcard的区别是，Ｗildcard的参数是任意类型的，但个数是固定好的．

![Untitled](Variadic/Untitled%204.png)

官方添加的和**Python**交互的功能 [Added a Blueprint node for calling Python with args](https://link.zhihu.com/?target=https%3A//github.com/EpicGames/UnrealEngine/commit/61d0f65e1cded45ed94f0422eb931f446888e972)

官方的提交：

[https://github.com/EpicGames/UnrealEngine/commit/61d0f65e1cded45ed94f0422eb931f446888e972](https://github.com/EpicGames/UnrealEngine/commit/61d0f65e1cded45ed94f0422eb931f446888e972)

Implemented variadic function support for Blueprints

`Variadic functions are required to be a CustomThunk marked with the "Variadic" meta-data. They can then be used from a custom Blueprint node to accept arbitrary arguments at the end of their parameter list (any extra pins added to the node that aren't part of the main function definition will become the variadic payload).

Variadic arguments aren't type checked, so you need other function input to tell you how many to expect, and for a nativizied function, also what type of arguments you're dealing with.

#jira UE-84932
#rb Dan.OConnor

[CL 10421401 by Jamie Dale in Dev-Editor branch]`