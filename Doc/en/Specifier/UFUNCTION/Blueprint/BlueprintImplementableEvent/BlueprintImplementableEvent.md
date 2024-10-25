# BlueprintImplementableEvent

- **Function Description:** Specifies a function call point that can be overridden in the blueprint.

- **Metadata Type:** bool
- **Engine Module:** Blueprint
- **Action Mechanism:** Adds [FUNC_Event](../../../../Flags/EFunctionFlags/FUNC_Event.md), [FUNC_Native](../../../../Flags/EFunctionFlags/FUNC_Native.md), [FUNC_BlueprintEvent](../../../../Flags/EFunctionFlags/FUNC_BlueprintEvent.md) to FunctionFlags
- **Commonly Used:** ★★★★★

Specifies a function call point that can be overridden in the blueprint, providing a convenient method for C++ to invoke blueprint functions.

If no implementation is provided in the blueprint, invoking the function is equivalent to calling an empty function.

BlueprintImplementableEvent must be used in conjunction with BlueprintCallable. Without BlueprintCallable, it can only be called from C++, and the Call Function node will not be found in the blueprint.

## Test Code:

```cpp
//FunctionFlags:	FUNC_Event | FUNC_Public | FUNC_BlueprintCallable | FUNC_BlueprintEvent
UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
void MyFunc_ImplementableEvent();
```

## Effect Display:

Right-click to add a custom implementation

![Untitled](Untitled.png)

## Principle:

When called in C++, the function searches for the name using FindFunctionChecked. If an implementation is found in the blueprint, it will be invoked. If called directly from the blueprint, the function also uses FindFunctionChecked to search; if a definition exists in the blueprint, it will be found directly.

```cpp
void AMyFunction_Default::MyFunc_ImplementableEvent()
{
		ProcessEvent(FindFunctionChecked(NAME_AMyFunction_Default_MyFunc_ImplementableEvent),NULL);
}
```