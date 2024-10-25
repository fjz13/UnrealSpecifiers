# AdvancedDisplay

- **Function Description:** Hides some function parameters from view by collapsing them; users must manually click the dropdown arrow to expand and edit them.
- **Usage Location:** UFUNCTION
- **Engine Module:** Blueprint
- **Metadata Type:** strings = "a, b, c"
- **Commonly Used:** ★★★★★

Parameters of the function are hidden by collapsing them; users must manually click the dropdown arrow to expand and edit them.

AdvancedDisplay supports two formats: one uses "Parameter1, Parameter2, .." to explicitly specify the names of parameters to be collapsed, which is suitable for parameters that are not consecutive or located in the middle of the function parameter list. The other format uses "N" to specify a numerical sequence number, with all parameters following the Nth parameter displayed as advanced pins.

## Test Code:

```cpp
	UFUNCTION(BlueprintCallable, meta = (AdvancedDisplay = "2"))
	static int32 MyFunc_HasAdvancedDisplay_WithOrder(int32 First, int32 Second, int32 Third, int32 Fourth, int32 Fifth) { return 0; }
	UFUNCTION(BlueprintCallable, meta = (AdvancedDisplay = "Fourth,Fifth"))
	static int32 MyFunc_HasAdvancedDisplay_WithName(int32 First, int32 Second, int32 Third, int32 Fourth, int32 Fifth) { return 0; }

	UFUNCTION(BlueprintCallable, meta = ())
	static int32 MyFunc_NoAdvancedDisplay(int32 First, int32 Second, int32 Third, int32 Fourth, int32 Fifth) { return 0; }
```

## Blueprint Effect:

![Untitled](Untitled.png)

In the source code, a typical example is PrintString, where all parameters after the second parameter are collapsed.

```cpp
UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject", CallableWithoutWorldContext, Keywords = "log print", AdvancedDisplay = "2", DevelopmentOnly), Category="Development")
static ENGINE_API void PrintString(const UObject* WorldContextObject, const FString& InString = FString(TEXT("Hello")), bool bPrintToScreen = true, bool bPrintToLog = true, FLinearColor TextColor = FLinearColor(0.0f, 0.66f, 1.0f), float Duration = 2.f, const FName Key = NAME_None);
```

## Principle:

AdvancedDisplay adds the EPropertyFlags.AdvancedDisplay mark to the function parameters it annotates, causing them to be collapsed. This logic is set when UHT parses the function.

```cpp
//Supports both parameter name and numerical sequence number modes
if (_metaData.TryGetValue(UhtNames.AdvancedDisplay, out string? foundString))
{
	_parameterNames = foundString.ToString().Split(',', StringSplitOptions.RemoveEmptyEntries);
	for (int index = 0, endIndex = _parameterNames.Length; index < endIndex; ++index)
	{
		_parameterNames[index] = _parameterNames[index].Trim();
	}
	if (_parameterNames.Length == 1)
	{
		_bUseNumber = Int32.TryParse(_parameterNames[0], out _numberLeaveUnmarked);
	}
}

//Set EPropertyFlags.AdvancedDisplay
		private static void UhtFunctionParser::ParseParameterList(UhtParsingScope topScope, UhtPropertyParseOptions options)
		{
				UhtAdvancedDisplayParameterHandler advancedDisplay = new(topScope.ScopeType.MetaData);

				topScope.TokenReader.RequireList(')', ',', false, () =>
				{
					topScope.HeaderParser.GetCachedPropertyParser().Parse(topScope, disallowFlags, options, propertyCategory,
						(UhtParsingScope topScope, UhtProperty property, ref UhtToken nameToken, UhtLayoutMacroType layoutMacroType) =>
						{
							property.PropertyFlags |= EPropertyFlags.Parm;
							if (advancedDisplay.CanMarkMore() && advancedDisplay.ShouldMarkParameter(property.EngineName))
							{
								property.PropertyFlags |= EPropertyFlags.AdvancedDisplay;
							}
		}

```