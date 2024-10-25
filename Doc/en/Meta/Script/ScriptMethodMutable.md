# ScriptMethodMutable

- **Function description:** Modify the first const structure parameter of ScriptMethod to a reference parameter during the call. Changes made to this parameter within the function will be preserved.
- **Usage Location:** UFUNCTION
- **Engine Module:** Script
- **Metadata Type:** bool
- **Restriction Type:** The first parameter must be a structure type
- **Associated Items:** [ScriptMethod](ScriptMethod.md)
- **Commonality:** ★★

Modify the first const structure parameter of ScriptMethod to a reference parameter during the call. Changes made to this parameter within the function will be preserved.

- To alter the value of a const parameter, it is still necessary to declare it as mutable in C++.
- Although the Python code generated is identical, calling ScriptMethodMutable will actually modify the parameter's value, while a function without ScriptMethodMutable will not alter the original parameter value.
- Both ScriptMethodMutable and UPARAM(ref) can modify parameter values during function calls. However, UPARAM(ref) generates Python code that returns the first parameter as the result.

```cpp
USTRUCT(BlueprintType)
struct INSIDER_API FMyPythonStruct_ScriptMethod
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	mutable FString MyString;

};

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyPython_ScriptMethod_Test :public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, meta = (ScriptMethod))
	static void SetStringOnStruct(const FMyPythonStruct_ScriptMethod& myStruct, FString val);

	UFUNCTION(BlueprintCallable, meta = (ScriptMethod, ScriptMethodMutable))
	static void SetStringOnStructMutable(const FMyPythonStruct_ScriptMethod& myStruct, FString val);

	UFUNCTION(BlueprintCallable, meta = (ScriptMethod, ScriptMethodMutable))
	static void SetStringOnStructViaRef(UPARAM(ref) FMyPythonStruct_ScriptMethod& myStruct, FString val);
};
```

## Test Results:

Examining the generated Python code reveals consistency. When using UPARAM(ref), the generated my_func_on_struct_via_ref within MyPython_ScriptMethod_Test returns the structure MyPythonStruct_ScriptMethod to achieve the reference effect.

However, my_func_on_struct_mutable returns None, making it indistinguishable from my_func_on_struct without ScriptMethodMutable.  However, a real difference emerges during actual function calls.

```cpp
class MyPythonStruct_ScriptMethod(StructBase):
    r"""
    My Python Struct Script Method

    **C++ Source:**

    - **Module**: Insider
    - **File**: MyPython_ScriptMethod.h

    """
    def __init__(self) -> None:
        ...
    def my_func_on_struct_via_ref(self, val: str) -> None:
        r"""
        x.my_func_on_struct_via_ref(val) -> None
        My Func on Struct Via Ref

        Args:
            val (str):
        """
        ...
    def my_func_on_struct_mutable(self, val: str) -> None:
        r"""
        x.my_func_on_struct_mutable(val) -> None
        My Func on Struct Mutable

        Args:
            val (str):
        """
        ...
    def my_func_on_struct(self, val: str) -> None:
        r"""
        x.my_func_on_struct(val) -> None
        My Func on Struct

        Args:
            val (str):
        """
        ...


class MyPython_ScriptMethod_Test(Object):
    r"""
    My Python Script Method Test

    **C++ Source:**

    - **Module**: Insider
    - **File**: MyPython_ScriptMethod.h

    """
    @classmethod
    def my_func_on_struct_via_ref(cls, my_struct: MyPythonStruct_ScriptMethod, val: str) -> MyPythonStruct_ScriptMethod:
        r"""
        X.my_func_on_struct_via_ref(my_struct, val) -> MyPythonStruct_ScriptMethod
        My Func on Struct Via Ref

        Args:
            my_struct (MyPythonStruct_ScriptMethod):
            val (str):

        Returns:
            MyPythonStruct_ScriptMethod:

            my_struct (MyPythonStruct_ScriptMethod):
        """
        ...
    @classmethod
    def my_func_on_struct_mutable(cls, my_struct: MyPythonStruct_ScriptMethod, val: str) -> None:
        r"""
        X.my_func_on_struct_mutable(my_struct, val) -> None
        My Func on Struct Mutable

        Args:
            my_struct (MyPythonStruct_ScriptMethod):
            val (str):
        """
        ...
   @classmethod
    def my_func_on_struct(cls, my_struct: MyPythonStruct_ScriptMethod, val: str) -> None:
        r"""
        X.my_func_on_struct(my_struct, val) -> None
        My Func on Struct

        Args:
            my_struct (MyPythonStruct_ScriptMethod):
            val (str):
        """
        ...
```

Call records in the UE Python console and analysis of the calling sequence:

- Initially calling set_string_on_struct_mutable and then printing (a) outputs "Hello," indicating that the value is successfully set within the a structure.
- Attempting set_string_on_struct again and then printing (a) fails to produce "FFF," suggesting that the value was not set in the a structure. This implies that Python likely constructs a temporary value as the call object during the function call, and the new value after the call is not assigned to the original a object.
- Trying set_string_on_struct_via_ref followed by printing (a) outputs "First," demonstrating that UPARAM(ref) can also achieve the effect of modifying parameters.

```cpp
LogPython: a=unreal.MyPythonStruct_ScriptMethod()
LogPython: print(a)
LogPython: <Struct 'MyPythonStruct_ScriptMethod' (0x0000092D08CD6ED0) {my_string: ""}>
LogPython: a.set_string_on_struct_mutable("Hello")
LogBlueprintUserMessages: [None] UMyPython_ScriptMethod_Test::SetStringOnStructMutable
LogPython: print(a)
LogPython: <Struct 'MyPythonStruct_ScriptMethod' (0x0000092D08CD6ED0) {my_string: "Hello"}>
LogPython: a.set_string_on_struct("FFF")
LogBlueprintUserMessages: [None] UMyPython_ScriptMethod_Test::SetStringOnStruct
LogPython: print(a)
LogPython: <Struct 'MyPythonStruct_ScriptMethod' (0x0000092D08CD6ED0) {my_string: "Hello"}>
LogPython: a.set_string_on_struct_via_ref("First")
LogBlueprintUserMessages: [None] UMyPython_ScriptMethod_Test::SetStringOnStructViaRef
LogPython: print(a)
LogPython: <Struct 'MyPythonStruct_ScriptMethod' (0x0000092D08CD6ED0) {my_string: "First"}>
```

## Principle:

It is determined that if ScriptMethodMutable is present, SelfReturn is set, effectively copying the temporary value from within the function call to the original parameter value, thus achieving the desired variable reference call behavior.

```cpp
// The function may have been flagged as mutable, in which case we always consider it to need a 'self' return
if (!GeneratedWrappedDynamicMethod.SelfReturn.ParamProp && InFunc->HasMetaData(PyGenUtil::ScriptMethodMutableMetaDataKey))
{
	if (!SelfParam.ParamProp->IsA<FStructProperty>())
	{
		REPORT_PYTHON_GENERATION_ISSUE(Error, TEXT("Function '%s.%s' is marked as 'ScriptMethodMutable' but the 'self' argument is not a struct."), *InFunc->GetOwnerClass()->GetName(), *InFunc->GetName());
		return;
	}
	GeneratedWrappedDynamicMethod.SelfReturn = SelfParam;
}
```