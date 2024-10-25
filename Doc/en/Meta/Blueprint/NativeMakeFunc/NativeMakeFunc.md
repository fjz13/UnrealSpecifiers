# NativeMakeFunc

- **Function description:** Specifies a function to use the MakeStruct icon
- - **Use location:** UFUNCTION
- **Engine Module:** Blueprint
- **Metadata Type:** Boolean
- **Associated Items:** [NativeBreakFunc](../NativeBreakFunc.md)
- **Usage Frequency:** ★

Principle:

The sole instance found in the engine source code is as follows. Thus, there is no actual logical difference between the tags, but there is a difference in their display.

## Test Code:

```cpp
USTRUCT(BlueprintType)
struct FMyStruct_ForNative
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 X = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Y = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Z = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString MyString;
};

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyFunction_NativeMakeBreak :public UBlueprintFunctionLibrary
{
public:
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, meta = (NativeMakeFunc))
	static FMyStruct_ForNative MakeMyStructNative(FString ValueString);

	UFUNCTION(BlueprintPure)
	static FMyStruct_ForNative MakeMyStructNative_NoMeta(FString ValueString);

	UFUNCTION(BlueprintPure, meta = (NativeBreakFunc))
	static void BreakMyStructNative(const FMyStruct_ForNative& InValue, int32& X, int32& Y, int32& Z);

	UFUNCTION(BlueprintCallable, meta = (NativeMakeFunc))
	static void MakeMyStructNative_Wrong(FString ValueString);
};
```

## Effect within the Blueprint:

Observe that when "NoMeta" is present, the function's icon is the standard 'f' icon; otherwise, a different icon is displayed. Furthermore, note that a Struct can have multiple "Make" and "Break" functions, all of which can be utilized concurrently without issue.

![Untitled](Untitled.png)

## Principle:

The sole instance of this code was found within the engine's source code. Thus, while the tags do not differ logically, there is a discernible difference in their visual presentation.

Distinct icons are employed for the NativeMakeFunc and NativeBrakeFunc, indicating their unique roles.

```cpp
FSlateIcon UK2Node_CallFunction::GetPaletteIconForFunction(UFunction const* Function, FLinearColor& OutColor)
{
	static const FName NativeMakeFunc(TEXT("NativeMakeFunc"));
	static const FName NativeBrakeFunc(TEXT("NativeBreakFunc"));

	if (Function && Function->HasMetaData(NativeMakeFunc))
	{
		static FSlateIcon Icon(FAppStyle::GetAppStyleSetName(), "GraphEditor.MakeStruct_16x");
		return Icon;
	}
	else if (Function && Function->HasMetaData(NativeBrakeFunc))
	{
		static FSlateIcon Icon(FAppStyle::GetAppStyleSetName(), "GraphEditor.BreakStruct_16x");
		return Icon;
	}
	// Check to see if the function is calling an function that could be an event, display the event icon instead.
	else if (Function && UEdGraphSchema_K2::FunctionCanBePlacedAsEvent(Function))
	{
		static FSlateIcon Icon(FAppStyle::GetAppStyleSetName(), "GraphEditor.Event_16x");
		return Icon;
	}
	else
	{
		OutColor = GetPalletteIconColor(Function);

		static FSlateIcon Icon(FAppStyle::GetAppStyleSetName(), "Kismet.AllClasses.FunctionIcon");
		return Icon;
	}
}

```