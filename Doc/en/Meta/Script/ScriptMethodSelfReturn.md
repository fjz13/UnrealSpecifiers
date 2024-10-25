# ScriptMethodSelfReturn

- **Function description:** In the case of ScriptMethod , specify that the return value of this function should overwrite the first parameter of the function.
- **Usage Location:** UFUNCTION
- **Engine Module:** Script
- **Metadata Type:** bool
- **Associated Items:** [ScriptMethod](ScriptMethod.md)
- **Commonality:** ★★

In the case of ScriptMethod, specify that the return value of this function should overwrite the first parameter of the function.

In such cases, the original function does not return a value. The effect is as if:

```cpp
C Func(A,B) -> void A::Func2(B)
调用的时候：
从 C=A.Func(B) ->
void A::Func2(B)
{
	A=A.Func(B)
}
```

## Test Code:

Note that because the AppendStringOnStructViaRef parameter is a reference parameter, in order to apply the result to myStruct, there is no need to create a temporary value in the function body, and it can be modified directly on myStruct. If temporary values are also used, myStruct cannot be modified, and the meaning of the ref parameter is lost.

```cpp
public:
	UFUNCTION(BlueprintCallable, meta = (ScriptMethod))
	static FMyPythonStruct_ScriptMethod AppendStringOnStruct(const FMyPythonStruct_ScriptMethod& myStruct, FString val)
	{
		FMyPythonStruct_ScriptMethod Result = myStruct;
		Result.MyString += val;
		return Result;
	}

	UFUNCTION(BlueprintCallable, meta = (ScriptMethod,ScriptMethodSelfReturn))
	static FMyPythonStruct_ScriptMethod AppendStringOnStructReturn(const FMyPythonStruct_ScriptMethod& myStruct, FString val)
	{
		FMyPythonStruct_ScriptMethod Result = myStruct;
		Result.MyString += val;
		return Result;
	}
	UFUNCTION(BlueprintCallable, meta = (ScriptMethod, ScriptMethodMutable))
	static FMyPythonStruct_ScriptMethod AppendStringOnStructViaRef(UPARAM(ref) FMyPythonStruct_ScriptMethod& myStruct, FString val)
	{
		myStruct.MyString += val;
		return myStruct;
	}

//LogPython: Error: Function 'MyPython_ScriptMethod_Test.AppendStringOnStructViaRefReturn' is marked as 'ScriptMethodSelfReturn' but the 'self' argument is also marked as UPARAM(ref). This is not allowed.
//UFUNCTION(BlueprintCallable, meta = (ScriptMethod, ScriptMethodMutable,ScriptMethodSelfReturn))
//static FMyPythonStruct_ScriptMethod AppendStringOnStructViaRefReturn(UPARAM(ref) FMyPythonStruct_ScriptMethod& myStruct, FString val);
```

## Generated Py Code:

Visible append_string_on_struct_return There is no return value. And append_string_on_struct has a return value. append_string_on_struct_via_ref also has a return value.

```cpp
class MyPythonStruct_ScriptMethod(StructBase):
		 def append_string_on_struct_return(self, val: str) -> None:
        r"""
        x.append_string_on_struct_return(val) -> None
        Append String on Struct Return

        Args:
            val (str):

        Returns:
            MyPythonStruct_ScriptMethod:
        """
        ...
    def append_string_on_struct(self, val: str) -> MyPythonStruct_ScriptMethod:
        r"""
        x.append_string_on_struct(val) -> MyPythonStruct_ScriptMethod
        Append String on Struct

        Args:
            val (str):

        Returns:
            MyPythonStruct_ScriptMethod:
        """
        ...
	 def append_string_on_struct_via_ref(self, val: str) -> MyPythonStruct_ScriptMethod:
        r"""
        x.append_string_on_struct_via_ref(val) -> MyPythonStruct_ScriptMethod
        Append String on Struct Via Ref

        Args:
            val (str):

        Returns:
            MyPythonStruct_ScriptMethod:
        """
        ...
```

Test Code: Observe the running results and the object's memory address.

- It can be seen that append_string_on_struct has a return value, but the result of the change is not applied to parameter a.
- append_string_on_struct_return can be applied to parameter a, but there is no return value.
- append_string_on_struct_via_ref can be applied to parameter a and also has a return value. But note that the return value and a are not actually the same object because the memory addresses are different.
- But note ScriptMethodSelfReturn and UPARAM ( ref ) cannot be mixed, otherwise an error will be reported: LogPython: Error: Function ' MyPython_ScriptMethod_Test.AppendStringOnStructViaRefReturn ' is marked as ' ScriptMethodSelfReturn ' but the ' self ' argument is also marked as UPARAM ( ref ). This is not allowed .

```cpp
LogPython: a=unreal.MyPythonStruct_ScriptMethod()
LogPython: print(a)
LogPython: <Struct 'MyPythonStruct_ScriptMethod' (0x000008DEBAB08ED0) {my_string: ""}>
LogPython: b=a.append_string_on_struct("Hello")
LogPython: print(b)
LogPython: <Struct 'MyPythonStruct_ScriptMethod' (0x000008DEBAB04010) {my_string: "Hello"}>
LogPython: print(a)
LogPython: <Struct 'MyPythonStruct_ScriptMethod' (0x000008DEBAB08ED0) {my_string: ""}>
LogPython: c=a.append_string_on_struct_return("Hello")
LogPython: print(c)
LogPython: None
LogPython: print(a)
LogPython: <Struct 'MyPythonStruct_ScriptMethod' (0x000008DEBAB08ED0) {my_string: "Hello"}>
LogPython: d=a.append_string_on_struct_via_ref("World")
LogPython: print(d)
LogPython: <Struct 'MyPythonStruct_ScriptMethod' (0x000008DEBAB06110) {my_string: "HelloWorld"}>
LogPython: print(a)
LogPython: <Struct 'MyPythonStruct_ScriptMethod' (0x000008DEBAB08ED0) {my_string: "HelloWorld"}>
```

## Principle:

Treat the first output parameter as the return parameter. The output parameters are actually the return values in the function. SelfReturn means that this value will later overwrite the value of the calling object, which is the object where the call occurred.

```cpp
// The function may also have been flagged as having a 'self' return
if (InFunc->HasMetaData(PyGenUtil::ScriptMethodSelfReturnMetaDataKey))
{
	if (GeneratedWrappedDynamicMethod.SelfReturn.ParamProp)
	{
		REPORT_PYTHON_GENERATION_ISSUE(Error, TEXT("Function '%s.%s' is marked as 'ScriptMethodSelfReturn' but the 'self' argument is also marked as UPARAM(ref). This is not allowed."), *InFunc->GetOwnerClass()->GetName(), *InFunc->GetName());
		return;
	}
	else if (GeneratedWrappedDynamicMethod.MethodFunc.OutputParams.Num() == 0 || !GeneratedWrappedDynamicMethod.MethodFunc.OutputParams[0].ParamProp->HasAnyPropertyFlags(CPF_ReturnParm))
	{
		REPORT_PYTHON_GENERATION_ISSUE(Error, TEXT("Function '%s.%s' is marked as 'ScriptMethodSelfReturn' but has no return value."), *InFunc->GetOwnerClass()->GetName(), *InFunc->GetName());
		return;
	}
	else if (!SelfParam.ParamProp->IsA<FStructProperty>())
	{
		REPORT_PYTHON_GENERATION_ISSUE(Error, TEXT("Function '%s.%s' is marked as 'ScriptMethodSelfReturn' but the 'self' argument is not a struct."), *InFunc->GetOwnerClass()->GetName(), *InFunc->GetName());
		return;
	}
	else if (!GeneratedWrappedDynamicMethod.MethodFunc.OutputParams[0].ParamProp->IsA<FStructProperty>())
	{
		REPORT_PYTHON_GENERATION_ISSUE(Error, TEXT("Function '%s.%s' is marked as 'ScriptMethodSelfReturn' but the return value is not a struct."), *InFunc->GetOwnerClass()->GetName(), *InFunc->GetName());
		return;
	}
	else if (CastFieldChecked<const FStructProperty>(GeneratedWrappedDynamicMethod.MethodFunc.OutputParams[0].ParamProp)->Struct != CastFieldChecked<const FStructProperty>(SelfParam.ParamProp)->Struct)
	{
		REPORT_PYTHON_GENERATION_ISSUE(Error, TEXT("Function '%s.%s' is marked as 'ScriptMethodSelfReturn' but the return value is not the same type as the 'self' argument."), *InFunc->GetOwnerClass()->GetName(), *InFunc->GetName());
		return;
	}
	else
	{
		GeneratedWrappedDynamicMethod.SelfReturn = MoveTemp(GeneratedWrappedDynamicMethod.MethodFunc.OutputParams[0]);
		GeneratedWrappedDynamicMethod.MethodFunc.OutputParams.RemoveAt(0, 1, EAllowShrinking::No);
	}
}

```