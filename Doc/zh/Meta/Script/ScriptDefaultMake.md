# ScriptDefaultMake

- **功能描述：** 禁用结构上的HasNativeMake，在脚本里构造的时候不调用C++里的NativeMake函数，而采用脚本内建的默认初始化方式。
- **使用位置：** USTRUCT
- **引擎模块：** Script
- **元数据类型：** bool
- **关联项：** [ScriptDefaultBreak](ScriptDefaultBreak.md)
- **常用程度：** ★

禁用结构上的HasNativeMake，在脚本里构造的时候不调用C++里的NativeMake函数，而采用脚本内建的默认初始化方式。

ScriptDefaultBreak也是同理。

## 测试代码：

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

## 生成的py代码：

无论有没有加ScriptDefaultMake, ScriptDefaultBreak，MyPythonMBStructNative生成的py代码其实是一样的。不同点在于构成和to_tuple时候的结果不同。

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

## 运行的结果：

- 第二段是加了ScriptDefaultMake, ScriptDefaultBreak后的效果。我故意在C++的Make和Break函数里做了一些不一样，可以观察到调用到C++里的函数。
- 第一段是在代码里加上ScriptDefaultMake, ScriptDefaultBreak后（保留HasNativeMake，HasNativeBreak）调用的结果，可见C++里的Make/Break函数就没有再被调用到了。

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

## 原理：

在FindMakeBreakFunction函数里，如果发现有ScriptDefaultMake或ScriptDefaultBreak标记，就不去使用C++里由HasNativeMake，HasNativeBreak指定的函数。

另外py里的结构初始化会调用到默认的init或者结构的make函数，而to_tuple就相当于break的作用，会调用到默认的每个属性to_tuple或者是结构的自定义break函数。

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
	if (!InStruct->HasMetaData(InScriptDefaultMetaDataKey))  // <--- 有了default, 会直接返回null
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

// python wrapper 给每个类型都映射了 to_tuple 函数，会调用类型的 break 函数转换为 tuple
	static PyObject* ToTuple(FPyWrapperStruct* InSelf)
	{
			return FPyWrapperStruct::BreakStruct(InSelf);
	}

	....
	{ "to_tuple", PyCFunctionCast(&FMethods::ToTuple), METH_NOARGS, "to_tuple(self) -> Tuple[object, ...] -- break this Unreal struct into a tuple of its properties" },
```