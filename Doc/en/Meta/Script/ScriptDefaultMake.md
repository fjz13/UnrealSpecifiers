# ScriptDefaultMake

- **Function description:** Disable structural HasNativeMake , do not call the NativeMake function in C++ when constructing in the script, and use the script's built-in default initialization method.
- **Use location:** USTRUCT
- **Engine module:** Script
- **Metadata type:** bool
- **Related items:** [ScriptDefaultBreak](ScriptDefaultBreak.md)
- **Frequency of use:** ★

Disable HasNativeMake on the structure, do not call the NativeMake function in C++ when constructing in the script, and use the script's built-in default initialization method.

The same goes for ScriptDefaultBreak.

## Test code:

```cpp

USTRUCT(BlueprintType, meta = (ScriptDefaultMake, ScriptDefaultBreak,HasNativeMake = "/Script/Insider.MyPython_MakeBreak_Test.MyNativeMake", HasNativeBreak = "/Script/Insider.MyPython_MakeBreak_Test.MyNativeBreak"))
struct INSIDER_API FMyPythonMBStructNative
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MyInt = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString MyString;
};

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyPython_MakeBreak_Test :public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, meta = ())
	static FMyPythonMBStructNative MyNativeMake(int32 InInt) { return FMyPythonMBStructNative{ InInt,TEXT("Hello") }; }

	UFUNCTION(BlueprintPure, meta = ())
	static void MyNativeBreak(const FMyPythonMBStructNative& InStruct, int& outInt) { outInt = InStruct.MyInt + 123;  }
};

```

## Generated Python code:

Regardless of whether ScriptDefaultMake , ScriptDefaultBreak or MyPythonMBStructNative is added py the code is actually the same. The difference lies in the result when forming the sum to_tuple .

```cpp
class MyPythonMBStructNative(StructBase):
    r"""
    My Python MBStruct Native

    **C++ Source:**

    - **Module**: Insider
    - **File**: MyPython_ScriptMakeBreak.h

    **Editor Properties:** (see get_editor_property/set_editor_property)

    - ``my_int`` (int32):  [Read-Write]
    - ``my_string`` (str):  [Read-Write]
    """
    def __init__(self, int: int = 0) -> None:
        ...
    @property
    def my_int(self) -> int:
        r"""
        (int32):  [Read-Write]
        """
        ...
    @my_int.setter
    def my_int(self, value: int) -> None:
        ...
    @property
    def my_string(self) -> str:
        r"""
        (str):  [Read-Write]
        """
        ...
    @my_string.setter
    def my_string(self, value: str) -> None:
        ...
```

## Running results:

- The second paragraph is the effect after adding ScriptDefaultMake and ScriptDefaultBreak. I deliberately made some differences in the Make and Break functions of C++, so that I can observe the functions being called in C++.
- The first paragraph is the result of calling ScriptDefaultMake and ScriptDefaultBreak (retaining HasNativeMake and HasNativeBreak) in the code. It can be seen that the Make/Break function in C++ is no longer called.

```cpp
LogPython: b=unreal.MyPythonMBStructNative()
LogPython: print(b)
LogPython: <Struct 'MyPythonMBStructNative' (0x0000085F2EE9E680) {my_int: 0, my_string: "Hello"}>
LogPython: print(b.to_tuple())
LogPython: (123,)

LogPython: b=unreal.MyPythonMBStructNative()
LogPython: print(b)
LogPython: <Struct 'MyPythonMBStructNative' (0x000005E6C3AAFDC0) {my_int: 0, my_string: ""}>
LogPython: print(b.to_tuple())
LogPython: (0, '')
```

## Principle:

In the FindMakeBreakFunction function, if a ScriptDefaultMake or ScriptDefaultBreak tag is found, the functions specified by HasNativeMake and HasNativeBreak in C++ will not be used.

In addition py The structure initialization in ! will call the default init or make function of the structure, and to_tuple equivalent to break the function will call the default each attribute to_tuple or the custom break function of the structure.

```cpp
const FName ScriptDefaultMakeMetaDataKey = TEXT("ScriptDefaultMake");
const FName ScriptDefaultBreakMetaDataKey = TEXT("ScriptDefaultBreak");

namespace UE::Python
{

/**
 * Finds the UFunction corresponding to the name specified by 'HasNativeMake' or 'HasNativeBreak' meta data key.
 * @param The structure to inspect for the 'HasNativeMake' or 'HasNativeBreak' meta data keys.
 * @param InNativeMetaDataKey The native meta data key name. Can only be 'HasNativeMake' or 'HasNativeBreak'.
 * @param InScriptDefaultMetaDataKey The script default meta data key name. Can only be 'ScriptDefaultMake' or 'ScriptDefaultBreak'.
 * @param NotFoundFn Function invoked if the structure specifies as Make or Break function, but the function couldn't be found.
 * @return The function, if the struct has the meta key and if the function was found. Null otherwise.
 */
template<typename NotFoundFuncT>
UFunction* FindMakeBreakFunction(const UScriptStruct* InStruct, const FName& InNativeMetaDataKey, const FName& InScriptDefaultMetaDataKey, const NotFoundFuncT& NotFoundFn)
{
	check(InNativeMetaDataKey == PyGenUtil::HasNativeMakeMetaDataKey || InNativeMetaDataKey == PyGenUtil::HasNativeBreakMetaDataKey);
	check(InScriptDefaultMetaDataKey == PyGenUtil::ScriptDefaultMakeMetaDataKey || InScriptDefaultMetaDataKey == PyGenUtil::ScriptDefaultBreakMetaDataKey);

	UFunction* MakeBreakFunc = nullptr;
	if (!InStruct->HasMetaData(InScriptDefaultMetaDataKey))  // <--- With default , null will be returned directly
	{
		const FString MakeBreakFunctionName = InStruct->GetMetaData(InNativeMetaDataKey);
		if (!MakeBreakFunctionName.IsEmpty())
		{
			// Find the function.
			MakeBreakFunc = FindObject<UFunction>(/*Outer*/nullptr, *MakeBreakFunctionName, /*ExactClass*/true);
			if (!MakeBreakFunc)
			{
				NotFoundFn(MakeBreakFunctionName);
			}
		}
	}
	return MakeBreakFunc;
}
}

struct FFuncs
{
	static int Init(FPyWrapperStruct* InSelf, PyObject* InArgs, PyObject* InKwds)
	{
		const int SuperResult = PyWrapperStructType.tp_init((PyObject*)InSelf, InArgs, InKwds);
		if (SuperResult != 0)
		{
			return SuperResult;
		}

		return FPyWrapperStruct::MakeStruct(InSelf, InArgs, InKwds);
	}
};

GeneratedWrappedType->PyType.tp_init = (initproc)&FFuncs::Init;

// python wrapper A to_tuple function is mapped to each type, and the break function of the type will be called to convert to tuple
	static PyObject* ToTuple(FPyWrapperStruct* InSelf)
	{
			return FPyWrapperStruct::BreakStruct(InSelf);
	}

	....
	{ "to_tuple", PyCFunctionCast(&FMethods::ToTuple), METH_NOARGS, "to_tuple(self) -> Tuple[object, ...] -- break this Unreal struct into a tuple of its properties" },
```