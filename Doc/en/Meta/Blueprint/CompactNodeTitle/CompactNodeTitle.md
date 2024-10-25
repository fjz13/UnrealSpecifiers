# CompactNodeTitle

- **Function Description:** Enables the function to be displayed in a compact mode, while assigning a new abbreviated name
- **Usage Location:** UFUNCTION
- **Engine Module:** Blueprint
- **Metadata Type:** string="abc"
- **Commonality:** ★★★

Enables the function to be displayed in a compact mode, and assigns a new abbreviated name. Note that in this mode, the DisplayName data is overlooked.

## Testing Code:

```cpp
	UFUNCTION(BlueprintCallable, meta = (CompactNodeTitle = "MyCompact",DisplayName="AnotherName"))
	static int32 MyFunc_HasCompactNodeTitle(FString Name) {return 0;}

	UFUNCTION(BlueprintCallable, meta = ())
	static int32 MyFunc_NoCompactNodeTitle(FString Name) {return 0;}

	UFUNCTION(BlueprintPure, meta = (CompactNodeTitle = "MyPure",DisplayName="AnotherName"))
	static int32 MyPure_HasCompactNodeTitle(FString Name) {return 0;}

	UFUNCTION(BlueprintPure, meta = ())
	static int32 MyPure_NoCompactNodeTitle(FString Name) {return 0;}
```

## Blueprint Effect:

The display effect has significantly changed. Moreover, functions defined within the blueprint can also be transformed into a compact display mode through settings on the detail panel.

![Untitled](Untitled.png)

## Principle:

```cpp
bool UK2Node_CallFunction::ShouldDrawCompact(const UFunction* Function)
{
	return (Function != NULL) && Function->HasMetaData(FBlueprintMetadata::MD_CompactNodeTitle);
}

FString UK2Node_CallFunction::GetCompactNodeTitle(const UFunction* Function)
{
	static const FString ProgrammerMultiplicationSymbol = TEXT("*");
	static const FString CommonMultiplicationSymbol = TEXT("\xD7");

	static const FString ProgrammerDivisionSymbol = TEXT("/");
	static const FString CommonDivisionSymbol = TEXT("\xF7");

	static const FString ProgrammerConversionSymbol = TEXT("->");
	static const FString CommonConversionSymbol = TEXT("\x2022");

	const FString& OperatorTitle = Function->GetMetaData(FBlueprintMetadata::MD_CompactNodeTitle);
	if (!OperatorTitle.IsEmpty())
	{
		if (OperatorTitle == ProgrammerMultiplicationSymbol)
		{
			return CommonMultiplicationSymbol;
		}
		else if (OperatorTitle == ProgrammerDivisionSymbol)
		{
			return CommonDivisionSymbol;
		}
		else if (OperatorTitle == ProgrammerConversionSymbol)
		{
			return CommonConversionSymbol;
		}
		else
		{
			return OperatorTitle;
		}
	}

	return Function->GetName();
}
```