# ScriptNoExport

Description: 不导出该函数或属性到脚本。
Usage: UFUNCTION, UPROPERTY
Feature: Script
Group: Script
Type: bool
Status: Done

不导出该函数或属性到脚本。

测试代码：

```cpp
UCLASS(Blueprintable, BlueprintType, meta = (ScriptName = "MyPythonLib"))
class INSIDER_API UMyPythonTestLibary :public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	static void MyScriptFunc_None();

	UFUNCTION(BlueprintCallable, meta = (ScriptNoExport))
	static void MyScriptFunc_NoExport();
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MyFloat = 123.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ScriptNoExport))
	float MyFloat_NoExport = 123.f;
};
```

测试效果py代码：

可见默认的函数和属性都会导出到脚本里。而MyScriptFunc_NoExport和MyFloat_NoExport在py里并没有。

```cpp
class MyPythonLib(BlueprintFunctionLibrary):
    r"""
    My Python Test Libary
    
    **C++ Source:**
    
    - **Module**: Insider
    - **File**: MyPythonTest.h
    
    """
     @property
    def my_float(self) -> float:
        r"""
        (float):  [Read-Write]
        """
        ...
    @my_float.setter
    def my_float(self, value: float) -> None:
        ...
    @classmethod
    def my_script_func_none(cls) -> None:
        r"""
        X.my_script_func_none() -> None
        My Script Func None
        """
        ...
```

原理：

根据这个ScriptNoExport来判断一个属性或函数是否导出。

```cpp
bool IsScriptExposedProperty(const FProperty* InProp)
{
	return !InProp->HasMetaData(ScriptNoExportMetaDataKey) 
		&& InProp->HasAnyPropertyFlags(CPF_BlueprintVisible | CPF_BlueprintAssignable);
}

bool IsScriptExposedFunction(const UFunction* InFunc)
{
	return !InFunc->HasMetaData(ScriptNoExportMetaDataKey)
		&& InFunc->HasAnyFunctionFlags(FUNC_BlueprintCallable | FUNC_BlueprintEvent)
		&& !InFunc->HasMetaData(BlueprintGetterMetaDataKey)
		&& !InFunc->HasMetaData(BlueprintSetterMetaDataKey)
		&& !InFunc->HasMetaData(BlueprintInternalUseOnlyMetaDataKey)
		&& !InFunc->HasMetaData(CustomThunkMetaDataKey)
		&& !InFunc->HasMetaData(NativeBreakFuncMetaDataKey)
		&& !InFunc->HasMetaData(NativeMakeFuncMetaDataKey);
}
```