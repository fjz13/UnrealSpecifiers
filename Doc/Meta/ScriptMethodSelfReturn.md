# ScriptMethodSelfReturn

Description: 在ScriptMethod的情况下，指定把这个函数的返回值要去覆盖该函数的第一个参数。
Usage: UFUNCTION
Feature: Script
Group: Script
Type: bool
Status: Done
Parent item: ScriptMethod (ScriptMethod.md)

在ScriptMethod的情况下，指定把这个函数的返回值要去覆盖该函数的第一个参数。

这种情况下，原本的函数就没有返回值返回了。效果上形如：

```cpp
C Func(A,B) -> void A::Func2(B)
调用的时候：
从 C=A.Func(B) -> 
void A::Func2(B)
{
	A=A.Func(B)
}
```

测试代码：

注意因为AppendStringOnStructViaRef参数是引用参数，所以为了结果应用到myStruct，在函数体内就不需要创建临时值，可以直接在myStruct上面修改。如果也用临时值的话，myStruct就无法得到修改，也就失去了ref参数的意义。

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

生成的py代码：

可见append_string_on_struct_return是没有返回值了。而append_string_on_struct有返回值。append_string_on_struct_via_ref也有返回值。

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

测试代码：观察运行的结果以及对象的内存地址。

- 可以看出append_string_on_struct是有返回值的，但是改变的结果没有应用到参数a上。
- append_string_on_struct_return可以应用到参数a上，但是没有返回值。
- append_string_on_struct_via_ref可以应用到参数a上，同时也有返回值。但是注意返回值和a其实并不是同一个对象，因为内存地址不同。
- 但是注意 ScriptMethodSelfReturn和UPARAM(ref)不能混用，否则会报错：  LogPython: Error: Function 'MyPython_ScriptMethod_Test.AppendStringOnStructViaRefReturn' is marked as 'ScriptMethodSelfReturn' but the 'self' argument is also marked as UPARAM(ref). This is not allowed.

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

原理：

把输出参数的第一个当作返回参数。输出参数其实就是函数里的返回值。SelfReturn的意思是这个值之后要去覆盖掉调用对象的值，也就是发生调用的对象。

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