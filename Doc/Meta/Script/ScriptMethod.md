# ScriptMethod

- **功能描述：** 把静态函数导出变成第一个参数的成员函数。
- **使用位置：** UFUNCTION
- **引擎模块：** Script
- **元数据类型：** string="a;b;c"
- **限制类型：** static function
- **关联项：** [ScriptMethodMutable](ScriptMethodMutable.md), [ScriptMethodSelfReturn](ScriptMethodSelfReturn.md)
- **常用程度：** ★★★

把静态函数导出变成第一个参数的成员函数。

- 把func(A，B)变成A.func(B)，这样就可以给A对象添加成员函数方法。有点像C#里的扩展方法。
- 也可以直接再提供一个名字来改变包装后的成员函数的名称。注意与ScriptName区分，ScriptName改变的是本身导出到脚本的名字，而ScriptMethod改变的是结果成员函数的名字。把func(A，B)改成A.OtherFunc(B)。

## 测试代码：

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

## 测试效果：

可见在MyPythonStruct_ScriptMethod里增加了my_func_on_struct的方法，而MyPython_ScriptMethod里增加了my_func_on_object的方法。因此如果在py里你就可以把这两个函数当作成员函数一样调用。

另外MyFuncOnObject2上面设置了两个ScriptMethod 别称，也可以在MyPython_ScriptMethod里见到。

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

## 原理：

在GenerateWrappedDynamicMethod中有详细的如何把静态函数包装成成员函数的过程。感兴趣的可以去细看。

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
