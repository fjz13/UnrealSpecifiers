# HasNoOpConstructor

- **Function Description:** Specifies that the structure possesses a constructor with ForceInit, allowing it to be invoked for initialization when it serves as the return value of a BP function
- **Metadata Type:** bool
- **Engine Module:** UHT
- **Restriction Type:** Used exclusively by UHT in NoExportTypes.h
- **Frequency of Use:** 0

Specifies that the structure has a constructor with ForceInit, ensuring that when it is used as a return value or parameter for a BP Function, the engine is aware of this constructor's existence for initialization purposes.

The functionality is applied within the AppendEventParameter method of UhtHeaderCodeGenerator, where glue code needs to be generated for an Event exposed to BP. For instance, FLinearColor is marked as HasNoOpConstructor. Consider the following function:

```cpp
UFUNCTION(BlueprintNativeEvent, Category = "Modifier")
FLinearColor GetVisualizationColor(FInputActionValue SampleValue, FInputActionValue FinalValue) const;
```

Generated code:

```cpp
struct InputModifier_eventGetVisualizationColor_Parms
	{
		FInputActionValue SampleValue;
		FInputActionValue FinalValue;
		FLinearColor ReturnValue;

		/** Constructor, initializes return property only **/
		InputModifier_eventGetVisualizationColor_Parms()
			: ReturnValue(ForceInit)//Enforce initialization
		{
		}
	};

static FName NAME_UInputModifier_GetVisualizationColor = FName(TEXT("GetVisualizationColor"));
	FLinearColor UInputModifier::GetVisualizationColor(FInputActionValue SampleValue, FInputActionValue FinalValue) const
	{
		InputModifier_eventGetVisualizationColor_Parms Parms;
		Parms.SampleValue=SampleValue;
		Parms.FinalValue=FinalValue;
		const_cast<UInputModifier*>(this)->ProcessEvent(FindFunctionChecked(NAME_UInputModifier_GetVisualizationColor),&Parms);
		return Parms.ReturnValue;
	}
```

Thus, the structure must have a constructor with ForceInit

```cpp
FORCEINLINE explicit FLinearColor(EForceInit)
	: R(0), G(0), B(0), A(0)
	{}
```

## Principle:

```cpp
if (ScriptStruct.HasNoOpConstructor)
{
//If true, the an argument will need to be added to the constructor
	PropertyCaps |= UhtPropertyCaps.RequiresNullConstructorArg;
}
```