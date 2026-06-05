---
title: "ScriptMethodMutable"
id: "meta.ScriptMethodMutable"
kind: "meta"
symbol: "ScriptMethodMutable"
category: "Script"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "把ScriptMethod的第一个const结构参数在调用上改成引用参数，函数内修改的值会保存下来"
usage: "UFUNCTION"
---

# ScriptMethodMutable

## Decision Summary

- **Use when:** `ScriptMethodMutable` metadata 的 `UFUNCTION` 场景需要：把ScriptMethod的第一个const结构参数在调用上改成引用参数，函数内修改的值会保存下来。
- **Do not use when:** 目标声明不属于 `UFUNCTION`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 把ScriptMethod的第一个const结构参数在调用上改成引用参数，函数内修改的值会保存下来。
- **使用位置：** UFUNCTION
- **引擎模块：** Script
- **元数据类型：** bool
- **限制类型：** 第一个参数是结构类型
- **关联项：** [ScriptMethod](ScriptMethod.md)
- **常用程度：** ★★

把ScriptMethod的第一个const结构参数在调用上改成引用参数，函数内修改的值会保存下来。

- 在const参数上如果想改变值，依然要标记c++里的mutable。
- 虽然py生成的代码一模一样，但实际调用上ScriptMethodMutable会真正改变参数的值，而没有ScriptMethodMutable的函数并不会改变参数的原始值。
- ScriptMethodMutable和UPARAM(ref) 在调用效果上，都可以改变参数的值。但区别是UPARAM(ref) 生成的py代码会返回第一个参数作为返回值。

```cpp
USTRUCT(BlueprintType)
struct INSIDER_API FMyPythonStruct_ScriptMethod
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	mutable FString MyString;

};

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyPython_ScriptMethod_Test :public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, meta = (ScriptMethod))
	static void SetStringOnStruct(const FMyPythonStruct_ScriptMethod& myStruct, FString val);

	UFUNCTION(BlueprintCallable, meta = (ScriptMethod, ScriptMethodMutable))
	static void SetStringOnStructMutable(const FMyPythonStruct_ScriptMethod& myStruct, FString val);

	UFUNCTION(BlueprintCallable, meta = (ScriptMethod, ScriptMethodMutable))
	static void SetStringOnStructViaRef(UPARAM(ref) FMyPythonStruct_ScriptMethod& myStruct, FString val);
};
```
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。

## 测试效果：

看py里生成的代码是一致的，如果用UPARAM(ref)，则在MyPython_ScriptMethod_Test里面生成的my_func_on_struct_via_ref会返回结构MyPythonStruct_ScriptMethod来达成引用的效果。

然而my_func_on_struct_mutable返回的是None，同不加ScriptMethodMutable的my_func_on_struct并没有区别。但是实际上在真正调用的时候会真正有区别。

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
    def my_func_on_struct_via_ref(self, val: str) -> None:
        r"""
        x.my_func_on_struct_via_ref(val) -> None
        My Func on Struct Via Ref

        Args:
            val (str):
        """
        ...
    def my_func_on_struct_mutable(self, val: str) -> None:
        r"""
        x.my_func_on_struct_mutable(val) -> None
        My Func on Struct Mutable

        Args:
            val (str):
        """
        ...
    def my_func_on_struct(self, val: str) -> None:
        r"""
        x.my_func_on_struct(val) -> None
        My Func on Struct

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
    def my_func_on_struct_via_ref(cls, my_struct: MyPythonStruct_ScriptMethod, val: str) -> MyPythonStruct_ScriptMethod:
        r"""
        X.my_func_on_struct_via_ref(my_struct, val) -> MyPythonStruct_ScriptMethod
        My Func on Struct Via Ref

        Args:
            my_struct (MyPythonStruct_ScriptMethod):
            val (str):

        Returns:
            MyPythonStruct_ScriptMethod:

            my_struct (MyPythonStruct_ScriptMethod):
        """
        ...
    @classmethod
    def my_func_on_struct_mutable(cls, my_struct: MyPythonStruct_ScriptMethod, val: str) -> None:
        r"""
        X.my_func_on_struct_mutable(my_struct, val) -> None
        My Func on Struct Mutable

        Args:
            my_struct (MyPythonStruct_ScriptMethod):
            val (str):
        """
        ...
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
```

在UE Python控制台里调用的记录，分析调用顺序：

- 一开始调用set_string_on_struct_mutable，再print(a)，可以打印出Hello，说明值真正的设置到了a结构里。
- 再尝试set_string_on_struct，再print(a)，无法打印出FFF，说明值并没有设置到a结构里。说明py在调用的时候很可能构造了一个临时值来当作调对象，调用完成的新值并没有设置到a对象上。
- 再尝试set_string_on_struct_via_ref，再print(a)，可以打印出First，说明用UPARAM(ref)可以也达成改变参数的效果。

```cpp
LogPython: a=unreal.MyPythonStruct_ScriptMethod()
LogPython: print(a)
LogPython: <Struct 'MyPythonStruct_ScriptMethod' (0x0000092D08CD6ED0) {my_string: ""}>
LogPython: a.set_string_on_struct_mutable("Hello")
LogBlueprintUserMessages: [None] UMyPython_ScriptMethod_Test::SetStringOnStructMutable
LogPython: print(a)
LogPython: <Struct 'MyPythonStruct_ScriptMethod' (0x0000092D08CD6ED0) {my_string: "Hello"}>
LogPython: a.set_string_on_struct("FFF")
LogBlueprintUserMessages: [None] UMyPython_ScriptMethod_Test::SetStringOnStruct
LogPython: print(a)
LogPython: <Struct 'MyPythonStruct_ScriptMethod' (0x0000092D08CD6ED0) {my_string: "Hello"}>
LogPython: a.set_string_on_struct_via_ref("First")
LogBlueprintUserMessages: [None] UMyPython_ScriptMethod_Test::SetStringOnStructViaRef
LogPython: print(a)
LogPython: <Struct 'MyPythonStruct_ScriptMethod' (0x0000092D08CD6ED0) {my_string: "First"}>
```

## 原理：

判断如果有ScriptMethodMutable，会设置SelfReturn，从而再最后把函数调用中的临时值复制给原本的参数值，达成可变引用调用的效果。

```cpp
// The function may have been flagged as mutable, in which case we always consider it to need a 'self' return
if (!GeneratedWrappedDynamicMethod.SelfReturn.ParamProp && InFunc->HasMetaData(PyGenUtil::ScriptMethodMutableMetaDataKey))
{
	if (!SelfParam.ParamProp->IsA<FStructProperty>())
	{
		REPORT_PYTHON_GENERATION_ISSUE(Error, TEXT("Function '%s.%s' is marked as 'ScriptMethodMutable' but the 'self' argument is not a struct."), *InFunc->GetOwnerClass()->GetName(), *InFunc->GetName());
		return;
	}
	GeneratedWrappedDynamicMethod.SelfReturn = SelfParam;
}
```
