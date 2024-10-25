# SealedEvent

- **Function description:** This function cannot be overridden in subclasses. SealedEvent Keyword can only be used for events. For non-event functions, declare them as static or final to seal them.

- **Metadata Type:** bool
- **Engine Module:** Behavior
- **Mechanism of action:** Add [FUNC_Final](../../../../Flags/EFunctionFlags/FUNC_Final.md) in FunctionFlags

Search in the source code: It is found that they are all used in network-related functions

![Untitled](Untitled.png)

## Processing in UHT:

```cpp
//First, identify the symbol
[UhtSpecifier(Extends = UhtTableNames.Function, ValueType = UhtSpecifierValueType.Legacy)]
private static void SealedEventSpecifier(UhtSpecifierContext specifierContext)
{
	UhtFunction function = (UhtFunction)specifierContext.Type;
	function.FunctionExportFlags |= UhtFunctionExportFlags.SealedEvent;
}

//Then, set the mark
// Handle the initial implicit/explicit final
// A user can still specify an explicit final after the parameter list as well.
if (automaticallyFinal || function.FunctionExportFlags.HasAnyFlags(UhtFunctionExportFlags.SealedEvent))
{
				function.FunctionFlags |= EFunctionFlags.Final;
				function.FunctionExportFlags |= UhtFunctionExportFlags.Final | UhtFunctionExportFlags.AutoFinal;
}

再验证：限定只能用在Event上。

if (FunctionExportFlags.HasAnyFlags(UhtFunctionExportFlags.SealedEvent) && !FunctionFlags.HasAnyFlags(EFunctionFlags.Event))
{
	this.LogError("SealedEvent may only be used on events");
}

if (FunctionExportFlags.HasAnyFlags(UhtFunctionExportFlags.SealedEvent) && FunctionFlags.HasAnyFlags(EFunctionFlags.BlueprintEvent))
{
	this.LogError("SealedEvent cannot be used on Blueprint events");
}

```

## Test Code:

```cpp
//Error: "SealedEvent may only be used on events"
UFUNCTION(SealedEvent)
void MyFunc_SealedEvent() {}

//Error: "SealedEvent cannot be used on Blueprint events"
UFUNCTION(BlueprintCallable,BlueprintImplementableEvent,SealedEvent)
void MyFunc_ImplementableEvent();

//Error: "SealedEvent cannot be used on Blueprint events"
UFUNCTION(BlueprintCallable,BlueprintNativeEvent,SealedEvent)
void MyFunc_NativeEvent();
```

Therefore, it is not applicable to regular functions, nor can it be used for events within blueprints. So, what is this that is both an event and not a BlueprintEvent? A look at the source code reveals that it pertains only to certain network functions.

Through comparison, we found that the difference between the Sealed functions is the addition of the FUNC_Final mark. But FUNC_Final does not necessarily have to be added with SealedEvent , exec or the ordinary BlueprintCallable function will be added. But if it is a vitural function, it will not be added. The principle in UHT is:

```cpp
private static UhtParseResult ParseUFunction(UhtParsingScope parentScope, UhtToken token)
{
		if (function.FunctionFlags.HasAnyFlags(EFunctionFlags.Net))
		{
						// Network replicated functions are always events, and are only final if sealed
						scopeName = "event";
						tokenContext.Reset(scopeName);
						automaticallyFinal = false;
		}

		// If virtual, remove the implicit final, the user can still specifying an explicit final at the end of the declaration
		if (function.FunctionExportFlags.HasAnyFlags(UhtFunctionExportFlags.Virtual))
		{
						automaticallyFinal = false;
		}
		// Handle the initial implicit/explicit final
		// A user can still specify an explicit final after the parameter list as well.
		if (automaticallyFinal || function.FunctionExportFlags.HasAnyFlags(UhtFunctionExportFlags.SealedEvent))
		{
						function.FunctionFlags |= EFunctionFlags.Final;
						function.FunctionExportFlags |= UhtFunctionExportFlags.Final | UhtFunctionExportFlags.AutoFinal;
		}

}
```

I tested it in my own C++ code and found that no compilation error would be triggered no matter how I inherited it in C++. Therefore, if you want to refuse to be inherited, you should still use the C++ standard final keyword. Add final at the end of the function.

E:\P4V\Engine\Source\Editor\KismetCompiler\Private\KismetCompiler.cpp

```cpp
const uint32 OverrideFlagsToCheck = (FUNC_FuncOverrideMatch & ~FUNC_AccessSpecifiers);
if ((Context.Function->FunctionFlags & OverrideFlagsToCheck) != (OverridenFunction->FunctionFlags & OverrideFlagsToCheck))
{
	MessageLog.Error(*LOCTEXT("IncompatibleOverrideFlags_Error", "Overriden function is not compatible with the parent function @@. Check flags: Exec, Final, Static.").ToString(), Context.EntryPoint);
}
```

During compilation, it is detected whether the function of the overloaded parent class is overloaded, but because SealedEvent does not act on ordinary functions or BlueprintEvent, it feels that it can only be inherited in C++.