---
title: "ScriptNoExport"
id: "meta.ScriptNoExport"
kind: "meta"
symbol: "ScriptNoExport"
category: "Script"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "不导出该函数或属性到脚本"
usage: "UFUNCTION, UPROPERTY"
---

# ScriptNoExport

## Decision Summary

- **Use when:** `ScriptNoExport` metadata 的 `UFUNCTION, UPROPERTY` 场景需要：不导出该函数或属性到脚本。
- **Do not use when:** 目标声明不属于 `UFUNCTION, UPROPERTY`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 不导出该函数或属性到脚本。
- **使用位置：** UFUNCTION, UPROPERTY
- **引擎模块：** Script
- **元数据类型：** bool
- **常用程度：** ★★★

不导出该函数或属性到脚本。
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。

## 测试代码：

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

## 测试效果py代码：

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

## 原理：

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
