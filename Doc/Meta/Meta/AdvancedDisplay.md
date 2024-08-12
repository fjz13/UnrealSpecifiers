# AdvancedDisplay

Usage: UFUNCTION
Feature: Blueprint
Type: strings="a，b，c"
Description: 把函数的一些参数折叠起来不显示，需要手动点开下拉箭头来展开编辑。
Example: AdvancedDisplay="Parameter1, Parameter2, ..”
AdvancedDisplay=”N”
Status: Done
Group: Blueprint

把函数的一些参数折叠起来不显示，需要手动点开下拉箭头来展开编辑。

AdvancedDisplay同时支持两种格式，一是用"Parameter1, Parameter2, ..”来显式的指定需要折叠的参数名字，适用于要折叠的参数不连续或者处在函数参数列表中中央的情况下。二是”N”指定一个数字序号，第N之后的所有参数将显示为高级引脚。

测试代码：

```cpp
	UFUNCTION(BlueprintCallable, meta = (AdvancedDisplay = "2"))
	static int32 MyFunc_HasAdvancedDisplay_WithOrder(int32 First, int32 Second, int32 Third, int32 Fourth, int32 Fifth) { return 0; }
	UFUNCTION(BlueprintCallable, meta = (AdvancedDisplay = "Fourth,Fifth"))
	static int32 MyFunc_HasAdvancedDisplay_WithName(int32 First, int32 Second, int32 Third, int32 Fourth, int32 Fifth) { return 0; }

	UFUNCTION(BlueprintCallable, meta = ())
	static int32 MyFunc_NoAdvancedDisplay(int32 First, int32 Second, int32 Third, int32 Fourth, int32 Fifth) { return 0; }
```

蓝图效果：

![Untitled](AdvancedDisplay/Untitled.png)

源码中典型的例子是PrintString，在第2个参数后的其他参数就都折叠了起来。

```cpp
UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject", CallableWithoutWorldContext, Keywords = "log print", AdvancedDisplay = "2", DevelopmentOnly), Category="Development")
static ENGINE_API void PrintString(const UObject* WorldContextObject, const FString& InString = FString(TEXT("Hello")), bool bPrintToScreen = true, bool bPrintToLog = true, FLinearColor TextColor = FLinearColor(0.0f, 0.66f, 1.0f), float Duration = 2.f, const FName Key = NAME_None);
```

## 原理：

AdvancedDisplay使得被标注的函数参数增加EPropertyFlags.AdvancedDisplay的标记，从而使得其被折叠起来。这个逻辑是在UHT对函数进行解析的时候设置的。

```cpp
//支持参数名字和数字序号两种模式
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

//设置EPropertyFlags.AdvancedDisplay
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