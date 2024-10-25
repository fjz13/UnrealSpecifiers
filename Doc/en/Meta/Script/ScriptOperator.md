# ScriptOperator

- **Function Description:** Wraps a static function with its first parameter as a structure into an operator for that structure.
- **Usage Location:** UFUNCTION
- **Engine Module:** Script
- **Metadata Type:** string="a;b;c"
- **Commonality:** ★★★

Wraps a static function with its first parameter as a structure into an operator for the structure.

- Can include multiple operators.

Different operators need to match different function signatures. The rules are as follows:

- bool Operator: bool
    - bool FuncName(const FMyStruct& Value); // The type of Value can be const FMyStruct& or simply FMyStruct
- Unary Operator: neg (negation)
    - FMyStruct FuncName(const FMyStruct&);
- Comparison Operators: (==, !=, <, <=, >, >=)
    - bool FuncName(const FMyStruct&, OtherType); // OtherType can be any other type
- Mathematical Operators: (+, -, *, /, %, &, |, ^, >>, <<)
    - ReturnType FuncName(const FMyStruct&, OtherType); // ReturnType and OtherType can be any other type
- Mathematical Assignment Operators: (+=, -=, *=, /=, %=, &=, |=, ^=, >>=, <<=)
    - FMyStruct FuncName(const FMyStruct&, OtherType); // OtherType can be any other type

It is evident that if a function is to support both standard mathematical operators and assignment operators, the function signature can be:

FMyStruct FuncName(const FMyStruct&, OtherType); // Here, OtherType can be any type, or even FMyStruct

This is often used in conjunction with ScriptMethod, allowing a structure to provide an operation member function, which can also be customized in name through ScriptMethod.

There are also common examples of using ScriptMethodSelfReturn in the source code, such as with the += operator. However, ScriptMethodSelfReturn is not mandatory, as the return value is naturally applied to the first parameter when using +=.

## Test Code:

```cpp
USTRUCT(BlueprintType)
struct INSIDER_API FMyPythonMathStruct
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Value = 0;
};

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyPython_Operator_Test :public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, meta = (ScriptMethod=HasValue,ScriptOperator = "bool"))
	static bool IsValid(const FMyPythonMathStruct& InStruct) { return InStruct.Value != 0; }

	UFUNCTION(BlueprintCallable, meta = (ScriptOperator = "neg"))
	static FMyPythonMathStruct Neg(const FMyPythonMathStruct& InStruct) { return { -InStruct.Value }; }

	UFUNCTION(BlueprintCallable, meta = (ScriptOperator = "=="))
	static bool IsEqual(const FMyPythonMathStruct& A, const FMyPythonMathStruct& B) { return A.Value == B.Value; }

	UFUNCTION(BlueprintCallable, meta = (ScriptOperator = "+;+="))
	static FMyPythonMathStruct AddInt(FMyPythonMathStruct InStruct, const int32 InValue) { InStruct.Value += InValue; return InStruct; }
};

```

## Generated Py Code:

It can be observed that the functions __bool__, __eq__, __add__, __iadd__, and __neg__ have been generated in Python. Additionally, with IsValid annotated with ScriptMethod, an additional has_value function is provided.

```cpp
class MyPythonMathStruct(StructBase):
    r"""
    My Python Math Struct

    **C++ Source:**

    - **Module**: Insider
    - **File**: MyPython_ScriptOperator.h

    **Editor Properties:** (see get_editor_property/set_editor_property)

    - ``value`` (int32):  [Read-Write]
    """
    def __init__(self, value: int = 0) -> None:
        ...
    @property
    def value(self) -> int:
        r"""
        (int32):  [Read-Write]
        """
        ...
    @value.setter
    def value(self, value: int) -> None:
        ...
    def has_value(self) -> bool:
        r"""
        x.has_value() -> bool
        Is Valid

        Returns:
            bool:
        """
        ...
    def __bool__(self) -> bool:
        r"""
        Is Valid
        """
        ...
    def __eq__(self, other: object) -> bool:
        r"""
        **Overloads:**

        - ``MyPythonMathStruct`` Is Equal
        """
        ...
    def __add__(self, other: MyPythonMathStruct) -> None:
        r"""
        **Overloads:**

        - ``int32`` Add Int
        """
        ...
    def __iadd__(self, other: MyPythonMathStruct) -> None:
        r"""
        **Overloads:**

        - ``int32`` Add Int
        """
        ...
    def __neg__(self) -> None:
        r"""
        Neg
        """
        ...
```

## Running the Test:

It is confirmed that the mathematical += operator and boolean comparisons are indeed supported.

```cpp
LogPython: a=unreal.MyPythonMathStruct(3)
LogPython: print(a)
LogPython: <Struct 'MyPythonMathStruct' (0x0000074C90D5DCF0) {value: 3}>
LogPython: print(not a)
LogPython: False
LogPython: a+=3
LogPython: print(a)
LogPython: <Struct 'MyPythonMathStruct' (0x0000074C90D5DCF0) {value: 6}>
LogPython: print(-a)
LogPython: <Struct 'MyPythonMathStruct' (0x0000074C90D5DCF0) {value: -6}>
```

## Principle:

The specific wrapping functions are located within GenerateWrappedOperator. For those who wish to delve deeper, the details can be found there.

```cpp
auto GenerateWrappedOperator = [this, &OutGeneratedWrappedTypeReferences, &OutDirtyModules](const UFunction* InFunc, const PyGenUtil::FGeneratedWrappedMethod& InTypeMethod)
{
	// Only static functions can be hoisted onto other types
	if (!InFunc->HasAnyFunctionFlags(FUNC_Static))
	{
		REPORT_PYTHON_GENERATION_ISSUE(Error, TEXT("Non-static function '%s.%s' is marked as 'ScriptOperator' but only static functions can be hoisted."), *InFunc->GetOwnerClass()->GetName(), *InFunc->GetName());
		return;
	}

	// Get the list of operators to apply this function to
	TArray<FString> ScriptOperators;
	{
		const FString& ScriptOperatorsStr = InFunc->GetMetaData(PyGenUtil::ScriptOperatorMetaDataKey);
		ScriptOperatorsStr.ParseIntoArray(ScriptOperators, TEXT(";"));
	}

	// Go through and try and create a function for each operator, validating that the signature matches what the operator expects
	for (const FString& ScriptOperator : ScriptOperators)
	{
		PyGenUtil::FGeneratedWrappedOperatorSignature OpSignature;
		if (!PyGenUtil::FGeneratedWrappedOperatorSignature::StringToSignature(*ScriptOperator, OpSignature))
		{
			REPORT_PYTHON_GENERATION_ISSUE(Error, TEXT("Function '%s.%s' is marked as 'ScriptOperator' but uses an unknown operator type '%s'."), *InFunc->GetOwnerClass()->GetName(), *InFunc->GetName(), *ScriptOperator);
			continue;
		}

		PyGenUtil::FGeneratedWrappedOperatorFunction OpFunc;
		{
			FString SignatureError;
			if (!OpFunc.SetFunction(InTypeMethod.MethodFunc, OpSignature, &SignatureError))
			{
				REPORT_PYTHON_GENERATION_ISSUE(Error, TEXT("Function '%s.%s' is marked as 'ScriptOperator' but has an invalid signature for the '%s' operator: %s."), *InFunc->GetOwnerClass()->GetName(), *InFunc->GetName(), *ScriptOperator, *SignatureError);
				continue;
			}
		}

		// Ensure that we've generated a finalized Python type for this struct since we'll be adding this function as a operator on that type
		const UScriptStruct* HostedStruct = CastFieldChecked<const FStructProperty>(OpFunc.SelfParam.ParamProp)->Struct;
		if (GenerateWrappedStructType(HostedStruct, OutGeneratedWrappedTypeReferences, OutDirtyModules, EPyTypeGenerationFlags::ForceShouldExport))
		{
			// Find the wrapped type for the struct as that's what we'll actually add the operator to (via its meta-data)
			TSharedPtr<PyGenUtil::FGeneratedWrappedStructType> HostedStructGeneratedWrappedType = StaticCastSharedPtr<PyGenUtil::FGeneratedWrappedStructType>(GeneratedWrappedTypes.FindRef(PyGenUtil::GetTypeRegistryName(HostedStruct)));
			check(HostedStructGeneratedWrappedType.IsValid());
			StaticCastSharedPtr<FPyWrapperStructMetaData>(HostedStructGeneratedWrappedType->MetaData)->OpStacks[(int32)OpSignature.OpType].Funcs.Add(MoveTemp(OpFunc));
		}
	}
};
```