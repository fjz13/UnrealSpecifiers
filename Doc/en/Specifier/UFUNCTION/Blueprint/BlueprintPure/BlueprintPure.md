# BlueprintPure

- **Function Description:** Designated as a pure function, typically used by Get functions to return values.
- **Metadata Type:** bool
- **Engine Module:** Blueprint
- **Functionality Mechanism:** Adds [FUNC_BlueprintCallable](../../../../Flags/EFunctionFlags/FUNC_BlueprintCallable.md) and [FUNC_BlueprintPure](../../../../Flags/EFunctionFlags/FUNC_BlueprintPure.md) to FunctionFlags
- **Common Usage:** ★★★★★

Designated as a pure function, typically used by Get functions to return values.

- Pure functions are those without execution pins, not to be confused with const functions.
- Pure functions can have multiple return values, which can be added to the function using reference parameters.
- Cannot be used for void functions; otherwise, an error will be reported: "error: BlueprintPure specifier is not allowed for functions with no return value and no output parameters."

## Test Code:

```cpp
UFUNCTION(BlueprintPure)
	int32 GetMyInt()const { return MyInt; }
private:
	int32 MyInt;
```

## Effect Display:

![Untitled](Untitled.png)