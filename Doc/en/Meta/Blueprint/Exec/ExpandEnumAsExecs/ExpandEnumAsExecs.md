# ExpandEnumAsExecs

- **Function description:** Specifies multiple enum or bool type function parameters, automatically generating corresponding multiple input or output execution pins based on the entries, and altering the control flow according to different actual parameter values.
- **Usage location:** UFUNCTION
- **Engine module:** Blueprint
- **Metadata type:** strings = "a, b, c"
- **Related items:** [ExpandBoolAsExecs](../ExpandBoolAsExecs.md)
- **Commonly used:** ★★★★★

Specifies multiple enum or bool type function parameters, automatically generating corresponding multiple input or output execution pins based on the entries, and altering the control flow according to different actual parameter values.

Supports changing input and output Execs; only one input Exec is allowed, but multiple output ExecEnum pins can be generated. However, it cannot be used on BlueprintPure (as there are no Exec pins).

You can also use single quotes ‘|’ to separate values.

Three parameter types are supported: enum class, TEnumAsByte<EMyExecPins2::Type>, and bool. Enums must be marked with UENUM.

Reference type parameters and return values are used as output pins, while value type parameters are used as input pins.
The name "ReturnValue" can be used to specify the utilization of return value parameters.

If there are multiple output Enum parameters, they will be arranged in a sequence after the function call to trigger the output Execs one by one based on the values of the output Enums.

## Test Code:

```cpp
UENUM(BlueprintType)
enum class EMyExecPins : uint8
{
	First,
	Second,
	Third,
};

UENUM(BlueprintType)
namespace EMyExecPins2
{
	enum Type : int
	{
		Found,
		NotFound,
	};
}

UENUM(BlueprintType)
enum class EMyExecAnimalPins : uint8
{
	Cat,
	Dog,
};

public:
	UFUNCTION(BlueprintCallable, meta = (ExpandEnumAsExecs = "Pins"))
	static int32 MyEnumAsExec_Output(FString Name, EMyExecPins& Pins) { return 0; }

	UFUNCTION(BlueprintCallable, meta = (ExpandEnumAsExecs = "Pins"))
	static int32 MyEnumAsExec_Input(FString Name, TEnumAsByte<EMyExecPins2::Type> Pins) { return 0; }

	UFUNCTION(BlueprintCallable, meta = (ExpandEnumAsExecs = "ReturnValue"))
	static EMyExecPins MyEnumAsExec_Return(FString Name) { return EMyExecPins::First; }
public:
	UFUNCTION(BlueprintCallable, meta = (ExpandEnumAsExecs = "Pins"))
	static int32 MyBoolAsExec_Output(FString Name, bool& Pins) { return 0; }

	UFUNCTION(BlueprintCallable, meta = (ExpandEnumAsExecs = "Pins"))
	static int32 MyBoolAsExec_Input(FString Name, bool Pins) { return 0; }

	UFUNCTION(BlueprintCallable, meta = (ExpandEnumAsExecs = "ReturnValue"))
	static bool MyBoolAsExec_Return(FString Name) { return false; }
public:
	UFUNCTION(BlueprintCallable, meta = (ExpandEnumAsExecs = "InPins,OutAnimal|OutPins|ReturnValue"))
	static bool MyEnumAsExec_MultipleOut(FString Name, EMyExecPins InPins, EMyExecAnimalPins& OutAnimal, TEnumAsByte<EMyExecPins2::Type>& OutPins, FString& Result);
```

## Blueprint Effect:

By comparing the function prototypes and blueprint nodes mentioned above, you can find that ExpandEnumAsExecs executes 3 parameter types. It also verified that when there are multiple output Enum parameters at the same time (OutAnimal in the code|OutPins|ReturnValue), the output will be executed three times in sequence, as if connected together by Sequence nodes.

![Untitled](Untitled.png)

## Principle:

The real creation Pin is in void UK2Node_CallFunction::CreateExecPinsForFunctionCall ( const UFunction* Function ), and then the logic of these new ExecPin and matching assignment of input parameter values, and execution of different outputs based on output parameters ExecPin is in UK2Node_CallFunction::ExpandNode . There is too much code so I won’t post it.

The original function parameter pins are hidden, thus only the generated Exec pins are exposed.

The original parameter Pin of the function will be hidden, thus only the generated Exec Pin will be exposed.