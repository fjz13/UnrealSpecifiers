# ScriptOperator

Description: 把第一个参数为结构的静态函数包装成结构的运算符。
Usage: UFUNCTION
Feature: Script
Group: Script
Type: string="a;b;c"
Status: Done

把第一个参数为结构的静态函数包装成结构的运算符。

- 可以包含多个运算符。

不同的运算符需要匹配不同的函数签名。规则见如下：

- bool运算符：bool
    - bool FuncName(const FMyStruct& Value);    //Value的类型可以是const FMyStruct&或者直接FMyStruct
- 一元运算符：neg (取负)
    - FMyStruct FuncName(const FMyStruct&);
- 比较运算符： (==, !=, <, <=, >, >=)
    - bool FuncName(const FMyStruct, OtherType);  //OtherType可以是其他任何类型
- 数学运算符： (+, -, *, /, %, &, |, ^, >>, <<)
    - ReturnType FuncName(const FMyStruct&, OtherType);   //ReturnType 和 OtherType可以是其他任何类型
- 数学赋值运算符：(+=, -=, *=, /=, %=, &=, |=, ^=, >>=, <<=)
    - FMyStruct FuncName(const FMyStruct&, OtherType);   //OtherType可以是其他任何类型

可见，如果想一个函数同时支持普通数学运算符和赋值运算符，函数签名可以是：

FMyStruct FuncName(const FMyStruct&, OtherType);  //这里OtherType可以是任何类型，也可以是FMyStruct 

这个也常常一起配合ScriptMethod使用，这样就可以在结构中一起提供一个运算成员函数，这个函数的名字还可以通过ScriptMethod来自定义。

源码里也常见到和ScriptMethodSelfReturn使用的例子，如+=运算符上。但其实ScriptMethodSelfReturn不是必须的，在+=的时候，自然会把返回值应用到第一个参数上。

测试代码：

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

生成的py代码：

可见，在py里生成了__bool__，__eq__，__add__，__iadd__，__neg__的函数。同时IsValid加上了ScriptMethod，就有了另一个has_value函数。

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

进行运行的测试：

可见确实支持了数学+=运算符和bool的比较。

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

原理：

具体的包装函数都在GenerateWrappedOperator 里，具体想了解的可细看这里。

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