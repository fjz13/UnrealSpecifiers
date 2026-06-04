---
title: "CppFromBpEvent"
id: "meta.CppFromBpEvent"
kind: "meta"
symbol: "CppFromBpEvent"
category: "UHT"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定这是个在C++中定义的蓝图事件"
usage: "Todo"
---

# CppFromBpEvent

- **使用位置：** Todo
- **引擎模块：** UHT
- **元数据类型：** bool
- **常用程度：** 0

指定这是个在C++中定义的蓝图事件。

早期的UHT会使用这个元数据，不过现在的引擎版本已经不用这个了。
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。

## 原理代码：

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