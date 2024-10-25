# ScriptConstant

- **Function Description:** Packages the return value of a static function into a constant value.
- **Usage Location:** UFUNCTION
- **Engine Module:** Script
- **Metadata Type:** string="abc"
- **Associated Items:** [ScriptConstantHost](ScriptConstantHost.md)
- **Commonality:** ★★★

Wraps the return value of a static function into a constant value.

- The function's name serves as the default name for the constant, but ScriptConstant can also specify a custom name.
- The constant's scope is, by default, within the outer class of the static function, but it can also be directed to another type using ScriptConstantHost.

## Test Code:

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

## Generated Py Code:

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

## Result of Execution:

As seen, the corresponding constants are generated within the class. MyStringConst is generated in a different class due to the specification of ScriptConstantHost.

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

## Principle:

The logic for generating constants is encapsulated within the GenerateWrappedConstant function.

```cpp
auto GenerateWrappedConstant = [this, &GeneratedWrappedType, &OutGeneratedWrappedTypeReferences, &OutDirtyModules](const UFunction* InFunc)
{}
```