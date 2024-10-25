# BlueprintNativeEvent

- **Function description:** The implementation can be overridden entirely in Blueprints, but a default implementation is also provided in C++.

- **Metadata type:** bool
- **Engine module:** Blueprint
- **Mechanism of action:** [FUNC_Event](../../../../Flags/EFunctionFlags/FUNC_Event.md) and [FUNC_BlueprintEvent](../../../../Flags/EFunctionFlags/FUNC_BlueprintEvent.md) are added to the FunctionFlags
- **Frequency of use:** ★★★★★

The implementation can be overridden in Blueprints, but a default implementation is also provided in C++.

An additional function needs to be declared in C++ with the same name as the main function, but with "_Implementation" appended to the end. If no Blueprint override is found, the automatically generated code will invoke the "[FunctionName]_Implementation" method. This is typically used for functions like OnXXX, where C++ provides the implementation, allowing for the default C++ version to be called if no Blueprint override exists.
BlueprintNativeEvent must be accompanied by BlueprintCallable; otherwise, it can only be called within C++.

## Test Code:

```cpp
//FunctionFlags:	FUNC_Native | FUNC_Event | FUNC_Public | FUNC_BlueprintCallable | FUNC_BlueprintEvent
UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
void MyFunc_NativeEvent();

void AMyFunction_Default::MyFunc_NativeEvent_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "MyFunc_NativeEvent_Implementation");
}
```

## Effect Display:

![Untitled](Untitled.png)

## Principle:

When calling MyFunc_NativeEvent, the internal FindFunctionChecked will search for the function by name. If it is defined in a Blueprint, the Blueprint's implementation will be found; otherwise, the implementation for execMyFunc_NativeEvent will be located, thus calling MyFunc_NativeEvent_Implementation.

```cpp
DEFINE_FUNCTION(AMyFunction_Default::execMyFunc_NativeEvent)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->MyFunc_NativeEvent_Implementation();
	P_NATIVE_END;
}

void AMyFunction_Default::MyFunc_NativeEvent()
{
	ProcessEvent(FindFunctionChecked(NAME_AMyFunction_Default_MyFunc_NativeEvent),NULL);
}
```