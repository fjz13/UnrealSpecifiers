# ForceAsFunction

功能描述: 把C++里用BlueprintImplementableEvent或NativeEvent定义的事件强制改为函数在子类中覆写。
使用位置: UFUNCTION
Feature: Blueprint
引擎模块: Blueprint
元数据类型: bool
Example: meta = (ForceAsFunction)
Status: Done
常用程度: 3

把C++里用BlueprintImplementableEvent或NativeEvent定义的事件强制改为函数在子类中覆写。

什么情况下需要把Event改成函数？

- 变成函数后，在实现的时候就可以定义内部的局部变量。当然也就失去了调用Delay等延时函数的能力。
- 事件不能有输出的参数，但是如果想要一个有输出的函数在蓝图类里覆写（得BlueprintImplementableEvent或NativeEvent），则默认的以事件方式重载是不行的。因此这个时候把这个事件强迫改为函数的形式，就可以正常的覆写。
- 带有输出或返回参数的Event会默认被改为function，即使没有加上ForceAsFunction。

测试代码：

```cpp

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyFunction_ForceAsFunction :public AActor
{
public:
	GENERATED_BODY()
public:
//FUNC_Native | FUNC_Event | FUNC_Public | FUNC_BlueprintCallable | FUNC_BlueprintEvent 
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void MyNativeEvent_Default(const FString& name);

	//FUNC_Event | FUNC_Public | FUNC_BlueprintCallable | FUNC_BlueprintEvent 
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void MyImplementableEvent_Default(const FString& name);

public:
	//(ForceAsFunction = , ModuleRelativePath = Function/MyFunction_ForceAsFunction.h)
	//FUNC_Native | FUNC_Event | FUNC_Public | FUNC_BlueprintCallable | FUNC_BlueprintEvent 
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta = (ForceAsFunction))
	void MyNativeEvent_ForceAsFunction(const FString& name);

	////(ForceAsFunction = , ModuleRelativePath = Function/MyFunction_ForceAsFunction.h)
	//FUNC_Event | FUNC_Public | FUNC_BlueprintCallable | FUNC_BlueprintEvent 
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, meta = (ForceAsFunction))
	void MyImplementableEvent_ForceAsFunction(const FString& name);

public:
	//FUNC_Native | FUNC_Event | FUNC_Public | FUNC_HasOutParms | FUNC_BlueprintCallable | FUNC_BlueprintEvent 
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool MyNativeEvent_Output(const FString& name, int32& OutValue);

	//FUNC_Event | FUNC_Public | FUNC_HasOutParms | FUNC_BlueprintCallable | FUNC_BlueprintEvent 
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	bool MyImplementableEvent_Output(const FString& name, int32& OutValue);

	//(ForceAsFunction = , ModuleRelativePath = Function/MyFunction_ForceAsFunction.h)
	//FUNC_Native | FUNC_Event | FUNC_Public | FUNC_HasOutParms | FUNC_BlueprintCallable | FUNC_BlueprintEvent 
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta = (ForceAsFunction))
	bool MyNativeEvent_Output_ForceAsFunction(const FString& name, int32& OutValue);

	//(ForceAsFunction = , ModuleRelativePath = Function/MyFunction_ForceAsFunction.h)
	//FUNC_Event | FUNC_Public | FUNC_HasOutParms | FUNC_BlueprintCallable | FUNC_BlueprintEvent 
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, meta = (ForceAsFunction))
	bool MyImplementableEvent_Output_ForceAsFunction(const FString& name, int32& OutValue);
};
```

蓝图中效果：

在函数上覆写的时候，会发现只有MyNativeEvent_Default和MyImplementableEvent_Default被默认覆写为事件，其他都以函数的方式被覆写。

图里展示了MyImplementableEvent_ForceAsFunction被改为函数后，可以在内部定义局部变量。

也展示了MyNativeEvent_Output这种拥有输出参数的事件被覆写成函数后的函数体。

但无论是覆写为事件还是函数，被调用的时候用法并无区别。

![Untitled](ForceAsFunction/Untitled.png)

原理：

判断一个函数是否是事件的逻辑为以下函数：

主要看第二if和最后判断，BlueprintImplementableEvent或NativeEvent的函数上都会加上FUNC_BlueprintEvent标签，因此如果带有ForceAsFunction元数据或者有输出参数（返回值也算），就只能显示为函数。

```cpp
bool UEdGraphSchema_K2::FunctionCanBePlacedAsEvent(const UFunction* InFunction)
{
	// First check we are override-able, non-static, non-const and not marked thread safe
	if (!InFunction || !CanKismetOverrideFunction(InFunction) || InFunction->HasAnyFunctionFlags(FUNC_Static|FUNC_Const) || FBlueprintEditorUtils::HasFunctionBlueprintThreadSafeMetaData(InFunction))
	{
		return false;
	}

	// Check if meta data has been set to force this to appear as blueprint function even if it doesn't return a value.
	if (InFunction->HasAllFunctionFlags(FUNC_BlueprintEvent) && InFunction->HasMetaData(FBlueprintMetadata::MD_ForceAsFunction))
	{
		return false;
	}

	// Then look to see if we have any output, return, or reference params
	return !HasFunctionAnyOutputParameter(InFunction);
}
```