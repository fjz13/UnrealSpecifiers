# CppFromBpEvent

使用位置: Todo
Feature: UHT
引擎模块: UHT
元数据类型: bool
Status: NotUsed
常用程度: 0

指定这是个在C++中定义的蓝图事件。

早期的UHT会使用这个元数据，不过现在的引擎版本已经不用这个了。

原理代码：

```cpp
public static class UhtFunctionParser
{
	private static UhtParseResult ParseUFunction(UhtParsingScope parentScope, UhtToken token)
	{
		if (function.MetaData.ContainsKey(UhtNames.CppFromBpEvent))
		{
						function.FunctionFlags |= EFunctionFlags.Event;
		}
	}
}
```