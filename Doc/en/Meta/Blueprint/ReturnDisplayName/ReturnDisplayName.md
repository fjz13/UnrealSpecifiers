# ReturnDisplayName

- **Function Description:** Modify the name of the function's return value, with the default being ReturnValue
- **Usage Location:** UFUNCTION
- **Engine Module:** Blueprint
- **Metadata Type:** string="abc"
- **Commonliness:** ★★★★★

The default name for the function's return value pin is ReturnValue. If you wish to provide a more descriptive name, you can use ReturnDisplayName to customize it.

## Test Code:

```cpp
	UFUNCTION(BlueprintCallable, meta = (ReturnDisplayName = "IsSuccess"))
	static bool MyFunc_HasReturnDisplayName(FString Name) { return true; }

	UFUNCTION(BlueprintCallable, meta = ())
	static bool MyFunc_NoReturnDisplayName(FString Name) { return true; }
```

## Blueprint Effect:

The effect can be confirmed by comparing the names of the return values.

![Untitled](Untitled.png)

## Principle:

The principle is quite straightforward; it involves checking the Meta on the Pin and setting the PinFriendlyName

```cpp
if (Function->GetReturnProperty() == Param && Function->HasMetaData(FBlueprintMetadata::MD_ReturnDisplayName))
{
	Pin->PinFriendlyName = Function->GetMetaDataText(FBlueprintMetadata::MD_ReturnDisplayName);
}
```