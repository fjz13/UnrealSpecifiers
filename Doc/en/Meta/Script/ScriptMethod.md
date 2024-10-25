# ScriptMethod

- **Function Description:** Converts a static function into a member function with the first parameter as its owner.
- **Usage Location:** UFUNCTION
- **Engine Module:** Script
- **Metadata Type:** string="a;b;c"
- **Restriction Type:** static function
- **Associated Items:** [ScriptMethodMutable](ScriptMethodMutable.md), [ScriptMethodSelfReturn](ScriptMethodSelfReturn.md)
- **Commonliness:** ★★★

Converts a static function into a member function with the first parameter.

- Transforms func(A, B) into A.func(B), allowing the addition of member functions to object A, similar to extension methods in C#.
- An alternative name can also be provided directly to change the name of the wrapped member function. Note the distinction from ScriptName, which changes the name exported to the script, whereas ScriptMethod changes the name of the resulting member function. Changes func(A, B) to A.OtherFunc(B).

## Test Code:

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyPython_ScriptMethod :public UObject
{
	GENERATED_BODY()
public:
};

USTRUCT(BlueprintType)
struct INSIDER_API FMyPythonStruct_ScriptMethod
{
	GENERATED_BODY()
};

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyPython_ScriptMethod_Test :public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, meta = (ScriptMethod))
	static void MyFuncOnObject(UMyPython_ScriptMethod* obj, FString val);

	UFUNCTION(BlueprintCallable, meta = (ScriptMethod = "MySuperFuncOnObject;MyOtherFuncOnObject"))
	static void MyFuncOnObject2(UMyPython_ScriptMethod* obj, FString val);

public:
	UFUNCTION(BlueprintCallable, meta = (ScriptMethod))
	static void MyFuncOnStruct(const FMyPythonStruct_ScriptMethod& myStruct, FString val);;
};

```

## Test Results:

Visible in MyPythonStruct_ScriptMethod, the method my_func_on_struct has been added, and in MyPython_ScriptMethod, the method my_func_on_object has been added. Thus, in Python, these two functions can be called as if they were member functions.

Moreover, two ScriptMethod aliases are set on MyFuncOnObject2, which are also visible in MyPython_ScriptMethod.

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
    def my_func_on_struct(self, val: str) -> None:
        r"""
        x.my_func_on_struct(val) -> None
        My Func on Struct

        Args:
            val (str):
        """
        ...

class MyPython_ScriptMethod(Object):
    r"""
    My Python Script Method

    **C++ Source:**

    - **Module**: Insider
    - **File**: MyPython_ScriptMethod.h

    """
    def my_super_func_on_object(self, val: str) -> None:
        r"""
        x.my_super_func_on_object(val) -> None
        My Func on Object 2

        Args:
            val (str):
        """
        ...
     def my_other_func_on_object(self, val: str) -> None:
        r"""
        deprecated: 'my_other_func_on_object' was renamed to 'my_super_func_on_object'.
        """
        ...
    def my_func_on_object(self, val: str) -> None:
        r"""
        x.my_func_on_object(val) -> None
        My Func on Object

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
    def my_func_on_struct(cls, my_struct: MyPythonStruct_ScriptMethod, val: str) -> None:
        r"""
        X.my_func_on_struct(my_struct, val) -> None
        My Func on Struct

        Args:
            my_struct (MyPythonStruct_ScriptMethod):
            val (str):
        """
        ...
    @classmethod
    def my_func_on_object2(cls, obj: MyPython_ScriptMethod, val: str) -> None:
        r"""
        X.my_func_on_object2(obj, val) -> None
        My Func on Object 2

        Args:
            obj (MyPython_ScriptMethod):
            val (str):
        """
        ...
    @classmethod
    def my_func_on_object(cls, obj: MyPython_ScriptMethod, val: str) -> None:
        r"""
        X.my_func_on_object(obj, val) -> None
        My Func on Object

        Args:
            obj (MyPython_ScriptMethod):
            val (str):
        """
        ...
```

## Principle:

The detailed process of wrapping static functions into member functions is described in GenerateWrappedDynamicMethod. Those interested are encouraged to read further.

```cpp
PyTypeObject* FPyWrapperTypeRegistry::GenerateWrappedClassType(const UClass* InClass, FGeneratedWrappedTypeReferences& OutGeneratedWrappedTypeReferences, TSet<FName>& OutDirtyModules, const EPyTypeGenerationFlags InGenerationFlags)
{
	// Should this function also be hoisted as a struct method or operator?
	if (InFunc->HasMetaData(PyGenUtil::ScriptMethodMetaDataKey))
	{
		GenerateWrappedDynamicMethod(InFunc, GeneratedWrappedMethodCopy);
	}
}
```