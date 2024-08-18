# CustomThunk

功能描述: 指定UHT不为该函数生成蓝图调用的辅助函数，而需要用户自定义编写。
元数据类型: bool
引擎模块: UHT
MetaOperation: =true
Meta: CustomThunk (../../Meta/Meta/CustomThunk.md)
Status: Done
常用程度: 3

指定UHT不为该函数生成蓝图调用的辅助函数，而需要用户自定义编写。

这里Thunk的意思就是类似execFoo的函数，需要用户自己定义。

CustomThunk一般是用于配合函数参数不定的情况，如各种通配符，或者需要自己更细致的自定义的逻辑处理。

测试代码；

```cpp
UFUNCTION(BlueprintPure, CustomThunk)
static int32 MyFunc_CustomDivide(int32 A, int32 B = 1);

DECLARE_FUNCTION(execMyFunc_CustomDivide);

int32 UMyFunction_Custom::MyFunc_CustomDivide(int32 A, int32 B /*= 1*/)
{
	return 1;
}

DEFINE_FUNCTION(UMyFunction_Custom::execMyFunc_CustomDivide)
{
	P_GET_PROPERTY(FIntProperty, A);
	P_GET_PROPERTY(FIntProperty, B);

	P_FINISH;

	if (B == 0)
	{
		FFrame::KismetExecutionMessage(*FString::Printf(TEXT("Modulo by zero detected: %d %% 0\n%s"), A, *Stack.GetStackTrace()), ELogVerbosity::Warning);
		*(int32*)RESULT_PARAM = 0;
		return;
	}

	*(int32*)RESULT_PARAM = A/B;
}
```

蓝图效果：

![Untitled](CustomThunk/Untitled.png)

可以看到，即使是用除以0，可以自定义报错信息。

最重要的是如果观察.gen.cpp，可以对比发现内部不再生成execFoo的函数。