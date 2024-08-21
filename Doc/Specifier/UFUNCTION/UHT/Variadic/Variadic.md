# Variadic

- **功能描述：** 标识一个函数可以接受任意类型的多个参数（包括input/output)．

- **元数据类型：** bool
- **引擎模块：** Blueprint, UHT
- **作用机制：** 在Meta中加入[Variadic](../../../../Meta/Blueprint/Variadic.md)
- **常用程度：** ★★★

标识一个函数可以接受任意类型的多个参数（包括input/output)．

在源码中搜索应用：然后配合UK2Node_ExecutePythonScript

```cpp
UFUNCTION(BlueprintCallable, CustomThunk, Category = "Python|Execution", meta=(Variadic, BlueprintInternalUseOnly="true"))
    static bool ExecutePythonScript(UPARAM(meta=(MultiLine=True)) const FString& PythonScript, const TArray<FString>& PythonInputs, const TArray<FString>& PythonOutputs);
	DECLARE_FUNCTION(execExecutePythonScript);
```

蓝图的效果：

![Untitled](Untitled.png)

## 示例代码：

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyFunction_Variadic : public UBlueprintFunctionLibrary
{
public:
	GENERATED_BODY()
public:
	/*
			[PrintVariadicFields	Function->Struct->Field->Object	/Script/Insider.MyFunction_Variadic:PrintVariadicFields]
			(BlueprintInternalUseOnly = true, BlueprintType = true, CustomThunk = true, ModuleRelativePath = Function/Variadic/MyFunction_Variadic.h, Variadic = )
	*/
	UFUNCTION(BlueprintCallable, CustomThunk, BlueprintInternalUseOnly, meta = (Variadic))
	static FString PrintVariadicFields(const TArray<FString>& Inputs, const TArray<FString>& Outputs);
	DECLARE_FUNCTION(execPrintVariadicFields);
};

FString UMyFunction_Variadic::PrintVariadicFields(const TArray<FString>& Inputs, const TArray<FString>& Outputs)
{
	check(0);
	return TEXT("");
}

DEFINE_FUNCTION(UMyFunction_Variadic::execPrintVariadicFields)
{
	FString str;

	P_GET_TARRAY_REF(FString, Inputs);
	P_GET_TARRAY_REF(FString, Outputs);

	for (const FString& PythonInput : Inputs)
	{
		Stack.MostRecentPropertyAddress = nullptr;
		Stack.MostRecentProperty = nullptr;
		Stack.StepCompiledIn<FProperty>(nullptr);
		check(Stack.MostRecentProperty && Stack.MostRecentPropertyAddress);

		FProperty* p = CastField<FProperty>(Stack.MostRecentProperty);

		FString propertyValueString;
		const void* propertyValuePtr = p->ContainerPtrToValuePtr<const void*>(Stack.MostRecentPropertyContainer);

		p->ExportTextItem_Direct(propertyValueString, propertyValuePtr, nullptr, nullptr, PPF_None);

		str += FString::Printf(TEXT("%s:%s\n"), *p->GetFName().ToString(), *propertyValueString);

	}
	P_FINISH;

	*(FString*)RESULT_PARAM = str;
}
```

## 示例效果：

![Untitled](Untitled%201.png)

打印：

CallFunc_MakeVector_ReturnValue:(X=1.000000,Y=2.000000,Z=3.000000)
CallFunc_MakeLiteralDouble_ReturnValue:456.000000

## 原理：

普通的CustomThunk函数还有一些限制，参数名字和个数是在UFuntion里写死的，不能支持动态的个数。

目前，想使用**Variadic**功能，需要自定义蓝图节点用C++来为**K2Node_CallFunction**添加引脚。

想必是想要开发来同时实现**K2Node**以及对应的**CustomThunk**+**Variadic**方法，来保证使用上的安全性。

BlueprintInternalUseOnly也要加上，否则会自动生成普通的蓝图函数，达不到variadic的效果。

以下是不加BlueprintInternalUseOnly自动生成的版本:

![Untitled](Untitled%202.png)

实际应该是：然后再手动添加参数。

![Untitled](Untitled%203.png)

和Ｗildcard的区别是，Ｗildcard的参数是任意类型的，但个数是固定好的．

![Untitled](Untitled%204.png)

官方添加的和**Python**交互的功能 [Added a Blueprint node for calling Python with args](https://link.zhihu.com/?target=https%3A//github.com/EpicGames/UnrealEngine/commit/61d0f65e1cded45ed94f0422eb931f446888e972)

官方的提交：

[https://github.com/EpicGames/UnrealEngine/commit/61d0f65e1cded45ed94f0422eb931f446888e972](https://github.com/EpicGames/UnrealEngine/commit/61d0f65e1cded45ed94f0422eb931f446888e972)

## 注释：

Implemented variadic function support for Blueprints

`Variadic functions are required to be a CustomThunk marked with the "Variadic" meta-data. They can then be used from a custom Blueprint node to accept arbitrary arguments at the end of their parameter list (any extra pins added to the node that aren't part of the main function definition will become the variadic payload).

Variadic arguments aren't type checked, so you need other function input to tell you how many to expect, and for a nativizied function, also what type of arguments you're dealing with.

#jira UE-84932
#rb Dan.OConnor

[CL 10421401 by Jamie Dale in Dev-Editor branch]`