# CustomThunk

- **Function Description:** Instruct UHT not to generate an auxiliary function for blueprint invocation for this function, instead requiring the user to define it manually.
- **Metadata Type:** bool
- **Engine Module:** UHT
- **Functionality Mechanism:** Include [CustomThunk](../../../../Meta/UHT/CustomThunk.md) in the Meta section
- **Common Usage:** ★★★

Specifies that UHT should not generate an auxiliary function for blueprint invocation for this function, necessitating user-defined implementation.

Thunk refers to a function analogous to execFoo, which requires user-defined implementation.

"CustomThunk" is typically employed in scenarios where function parameters are indeterminate, such as with various wildcard characters, or when a more nuanced, custom logic processing is necessary.

## Test Code;

```cpp
UFUNCTION(BlueprintPure, CustomThunk)
static int32 MyFunc_CustomDivide(int32 A, int32 B = 1);

DECLARE_FUNCTION(execMyFunc_CustomDivide);

int32 UMyFunction_Custom::MyFunc_CustomDivide(int32 A, int32 B /*= 1*/)
{
	return 1;
}

DEFINE_FUNCTION(UMyFunction_Custom::execMyFunc_CustomDivide)
{
	P_GET_PROPERTY(FIntProperty, A);
	P_GET_PROPERTY(FIntProperty, B);

	P_FINISH;

	if (B == 0)
	{
		FFrame::KismetExecutionMessage(*FString::Printf(TEXT("Modulo by zero detected: %d %% 0\n%s"), A, *Stack.GetStackTrace()), ELogVerbosity::Warning);
		*(int32*)RESULT_PARAM = 0;
		return;
	}

	*(int32*)RESULT_PARAM = A/B;
}
```

## Blueprint Outcome:

![Untitled](Untitled.png)

It can be observed that even with a division by zero, a custom error message can be defined.

Significantly, examining .gen.cpp reveals that the execFoo function is no longer generated internally.