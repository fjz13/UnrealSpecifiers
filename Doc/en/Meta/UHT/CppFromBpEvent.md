# CppFromBpEvent

- **Usage Location:** To be determined
- **Engine Module:** UHT
- **Metadata Type:** boolean
- **Commonality:** 0

Indicates that this is a Blueprint event defined within C++.

Former versions of UHT utilized this metadata, but it is no longer used in the current engine versions.

## Original Code:

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