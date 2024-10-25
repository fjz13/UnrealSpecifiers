# ScriptName

- **Function Description:** The name used when exporting to script
- **Usage Location:** Any
- **Engine Module:** Script
- **Metadata Type:** string="abc"
- **Commonly Used:** ★★★

Specify the name to be used when exporting to script.

- Can be used with UCLASS, USTRUCT, UENUM, UFUNCTION, and UPROPERTY to change the exported script name.
- If no custom name is provided using ScriptName, the exported name will be the default Pythonized name. For instance, MyFunc() becomes my_func().

When testing Python, remember to enable the Python plugin.

You can find numerous pre-written test cases in \UnrealEngine\Engine\Plugins\Experimental\PythonScriptPlugin\Source\PythonScriptPlugin\Private\PyTest.h.

## Test Code:

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyPythonTestLibary2 :public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
};

UCLASS(Blueprintable, BlueprintType,meta=(ScriptName="MyPythonLib"))
class INSIDER_API UMyPythonTestLibary :public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	//unreal.MyPythonLib.my_script_func_default()
	UFUNCTION(BlueprintCallable,meta=())
	static void MyScriptFuncDefault()
	{
		UInsiderSubsystem::Get().PrintStringEx(nullptr, TEXT("MyScriptFuncDefault"));
	}

	//unreal.MyPythonLib.my_script_func()
	UFUNCTION(BlueprintCallable,meta=(ScriptName="MyScriptFunc"))
	static void MyScriptFunc_ScriptName()
	{
		UInsiderSubsystem::Get().PrintStringEx(nullptr, TEXT("MyScriptFunc_ScriptName"));
	}
};

```

## Test Results:

After opening the editor, the engine will automatically generate the corresponding export-to-Python glue code based on type data reflection. You can view the exported script code for the classes we define in C++ in \Intermediate\PythonStub\[unreal.py](http://unreal.py/).

For the class mentioned above, the Python code generated in unreal.py is as follows:

- As seen, UMyPythonTestLibary2 does not have a ScriptName and retains the default name, while UMyPythonTestLibary's name is changed to MyPythonLib.
- The export script name for MyScriptFuncDefault is my_script_func_default, and because MyScriptFunc_ScriptName has a ScriptName specified, it becomes MyScriptFunc

```cpp

class MyPythonTestLibary2(BlueprintFunctionLibrary):
    r"""
    My Python Test Libary 2

    **C++ Source:**

    - **Module**: Insider
    - **File**: MyPythonTest.h

    """
    ...

class MyPythonLib(BlueprintFunctionLibrary):
    r"""
    My Python Test Libary

    **C++ Source:**

    - **Module**: Insider
    - **File**: MyPython_Test.h

    """
    @classmethod
    def my_script_func_default(cls) -> None:
        r"""
        X.my_script_func_default() -> None
        My Script Func Default
        """
        ...
    @classmethod
    def my_script_func(cls) -> None:
        r"""
        X.my_script_func() -> None
        My Script Func Script Name
        """
        ...

```

## Principle:

When retrieving the name of each type, the ScriptName is checked first. If it is present, that name is used. Otherwise, the name is Pythonized in GetFieldPythonNameImpl.

```cpp
\Engine\Plugins\Experimental\PythonScriptPlugin\Source\PythonScriptPlugin\Private\PyGenUtil.cpp
const FName ScriptNameMetaDataKey = TEXT("ScriptName");

FString GetClassPythonName(const UClass* InClass)
{
	return GetFieldPythonNameImpl(InClass, ScriptNameMetaDataKey);
}

TArray<FString> GetDeprecatedClassPythonNames(const UClass* InClass)
{
	return GetDeprecatedFieldPythonNamesImpl(InClass, ScriptNameMetaDataKey);
}

FString GetStructPythonName(const UScriptStruct* InStruct)
{
	return GetFieldPythonNameImpl(InStruct, ScriptNameMetaDataKey);
}

TArray<FString> GetDeprecatedStructPythonNames(const UScriptStruct* InStruct)
{
	return GetDeprecatedFieldPythonNamesImpl(InStruct, ScriptNameMetaDataKey);
}

FString GetEnumPythonName(const UEnum* InEnum)
{
	return GetFieldPythonNameImpl(InEnum, ScriptNameMetaDataKey);
}

TArray<FString> GetDeprecatedEnumPythonNames(const UEnum* InEnum)
{
	return GetDeprecatedFieldPythonNamesImpl(InEnum, ScriptNameMetaDataKey);
}

FString GetFieldPythonNameImpl(const FFieldVariant& InField, const FName InMetaDataKey)
{
	FString FieldName;

	// First see if we have a name override in the meta-data
	if (GetFieldPythonNameFromMetaDataImpl(InField, InMetaDataKey, FieldName))
	{
		return FieldName;
	}

	//...
}
```