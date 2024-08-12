# ScriptConstant

Usage: UFUNCTION
Feature: Script
Type: string="abc"
Description: 把一个静态函数的返回值包装成为一个常量值。
Status: Done
Group: Script
Sub-item: ScriptConstantHost (ScriptConstantHost.md)

把一个静态函数的返回值包装成为一个常量值。

- 函数的名字即为常量的默认名称，但ScriptConstant也可以额外提供一个自定义名称。
- 常量作用域默认存在于该静态函数的外部类中，但也可以通过ScriptConstantHost来指定到另外一个类型中。

测试代码：

```cpp
USTRUCT(BlueprintType)
struct INSIDER_API FMyPythonConstantStruct
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString MyString;
};

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyPython_ConstantOwner :public UObject
{
	GENERATED_BODY()
public:
};

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyPython_Constant_Test :public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, meta = (ScriptConstant))
	static int32 MyIntConst() { return 123; }

	UFUNCTION(BlueprintPure, meta = (ScriptConstant = "MyOtherIntConst"))
	static int32 MyIntConst2() { return 456; }

	UFUNCTION(BlueprintPure, meta = (ScriptConstant))
	static FMyPythonConstantStruct MyStructConst() { return FMyPythonConstantStruct{ TEXT("Hello") }; }

	UFUNCTION(BlueprintPure, meta = (ScriptConstant = "MyOtherStructConst"))
	static FMyPythonConstantStruct MyStructConst2() { return FMyPythonConstantStruct{ TEXT("World") }; }

public:
	UFUNCTION(BlueprintPure, meta = (ScriptConstant="FirstString", ScriptConstantHost = "/Script/Insider.MyPython_ConstantOwner"))
	static FString MyStringConst() { return TEXT("First"); }
****};

```

生成的Py代码：

```cpp
class MyPython_Constant_Test(Object):
    r"""
    My Python Constant Test
    
    **C++ Source:**
    
    - **Module**: Insider
    - **File**: MyPython_ScriptConstant.h
    
    """
    MY_OTHER_STRUCT_CONST: MyPythonConstantStruct #: (MyPythonConstantStruct): My Struct Const 2
    MY_STRUCT_CONST: MyPythonConstantStruct #: (MyPythonConstantStruct): My Struct Const
    MY_OTHER_INT_CONST: int #: (int32): My Int Const 2
    MY_INT_CONST: int #: (int32): My Int Const
    
class MyPython_ConstantOwner(Object):
    r"""
    **My Python Constant Owner
    
    **C++ Source:**
    
    - **Module**: Insider
    - **File**: MyPython_ScriptConstant.h
    
    """
    FIRST_STRING: str #: (str): My String Const
```

运行的结果：

可见在类中生成了相应的常量。而MyStringConst因为指定了ScriptConstantHost 而生成在别的类中。

```cpp
LogPython: print(unreal.MyPython_Constant_Test.MY_INT_CONST)
LogPython: 123
LogPython: print(unreal.MyPython_Constant_Test.MY_OTHER_INT_CONST)
LogPython: 456
LogPython: print(unreal.MyPython_Constant_Test.MY_OTHER_STRUCT_CONST)
LogPython: <Struct 'MyPythonConstantStruct' (0x00000A0FC4051F00) {my_string: "World"}>
LogPython: print(unreal.MyPython_Constant_Test.MY_STRUCT_CONST)
LogPython: <Struct 'MyPythonConstantStruct' (0x00000A0FC4051EA0) {my_string: "Hello"}>
LogPython: print(unreal.MyPython_ConstantOwner.FIRST_STRING)
LogPython: First
```

原理：

生成的逻辑在这个GenerateWrappedConstant 函数里。

```cpp
auto GenerateWrappedConstant = [this, &GeneratedWrappedType, &OutGeneratedWrappedTypeReferences, &OutDirtyModules](const UFunction* InFunc)
{}
```