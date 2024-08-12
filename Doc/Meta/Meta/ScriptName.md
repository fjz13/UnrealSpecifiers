# ScriptName

Usage: Any
Feature: Script
Type: string="abc"
Description: 在导出到脚本里时使用的名字
Status: Done
Group: Script

指定导出到脚本中的名字。

- 可以使用在UCLASS，USTRUCT，UENUM，UFUNCTION，UPROPERTY上使用，改变其导出到脚本的名字。
- 如果没有使用ScriptName自定义名字，则导出的名字未默认的python化的名字。如MyFunc()变成my_func()。

在测试Python的时候，记得打开python插件。

可在\UnrealEngine\Engine\Plugins\Experimental\PythonScriptPlugin\Source\PythonScriptPlugin\Private\PyTest.h里见到大量写好的测试用例。

测试代码：

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

测试效果：

开启编辑器后，引擎会自动根据类型数据信息反射生成向相应的导出到py的胶水代码，我们在C++中定义的类就可以在\Intermediate\PythonStub\[unreal.py](http://unreal.py/)里查看其导出的脚本代码。

如上的类，在unreal.py生成的py代码如下：

- 可见UMyPythonTestLibary2 没有加ScriptName就是默认的名字，而UMyPythonTestLibary 的名字变成了MyPythonLib。
- MyScriptFuncDefault的导出脚本名字是my_script_func_default，而MyScriptFunc_ScriptName因为写了ScriptName变成了MyScriptFunc

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

原理：

在获取各个类型名字的时候，会先判断ScriptName，如果获得，就使用该名字。否则在GetFieldPythonNameImpl里会对名字进行python化处理。

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
	
	//。。。	
}
```