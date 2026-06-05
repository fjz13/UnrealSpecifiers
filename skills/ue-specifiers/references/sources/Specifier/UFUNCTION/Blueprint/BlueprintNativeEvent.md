---
title: "BlueprintNativeEvent"
id: "UFUNCTION.BlueprintNativeEvent"
kind: "specifier"
symbol: "BlueprintNativeEvent"
scope: "UFUNCTION"
category: "Blueprint"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "可以在蓝图总覆盖实现，但是也在C++中提供一个默认实现"
usage: "UFUNCTION / Blueprint"
---

# BlueprintNativeEvent

## Decision Summary

- **Use when:** C++ 需要提供默认实现，同时允许 Blueprint 覆写事件。
- **Do not use when:** 实现必须完全由 Blueprint 提供，或函数只是普通可调用 API。
- **Requires:** C++ 侧实现对应的 `_Implementation` 函数。
- **Conflicts:** 不要把它当成普通 `BlueprintCallable` 的替代。
- **Prefer instead:** 纯 Blueprint 实现入口用 `BlueprintImplementableEvent`；普通调用节点用 `BlueprintCallable`。

- **功能描述：** 可以在蓝图总覆盖实现，但是也在C++中提供一个默认实现。

- **元数据类型：** bool
- **引擎模块：** Blueprint
- **作用机制：** 在FunctionFlags中增加FUNC_Event、FUNC_BlueprintEvent
- **常用程度：** ★★★★★

可以在蓝图总覆盖实现，但是也在C++中提供一个默认实现。

需要在CPP中声明名称与主函数相同的附加函数，但是末尾添加了_Implementation。如果未找到任何蓝图覆盖，该自动生成的代码将调用“ [FunctionName]_Implementation”方法。一般用在OnXXX之类的函数上，在C++提供实现，这样如果蓝图中没有覆盖的时候，就可以默认调用C++中默认实现版本。
BlueprintNativeEvent，没加BlueprintCallable的话就只能在CPP里调用，因此一般也要配合加上BlueprintCallable。

## 测试代码：

```cpp
//FunctionFlags:	FUNC_Native | FUNC_Event | FUNC_Public | FUNC_BlueprintCallable | FUNC_BlueprintEvent
UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
void MyFunc_NativeEvent();

void AMyFunction_Default::MyFunc_NativeEvent_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "MyFunc_NativeEvent_Implementation");
}
```

## 效果展示：


## 原理：

在调用MyFunc_NativeEvent的时候，内部FindFunctionChecked会根据名字查找，如果在蓝图中有定义，则会找到蓝图中的实现版本。否则的话，则会找到execMyFunc_NativeEvent这个实现版本，从而调用MyFunc_NativeEvent_Implementation。

```cpp
DEFINE_FUNCTION(AMyFunction_Default::execMyFunc_NativeEvent)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->MyFunc_NativeEvent_Implementation();
	P_NATIVE_END;
}

void AMyFunction_Default::MyFunc_NativeEvent()
{
	ProcessEvent(FindFunctionChecked(NAME_AMyFunction_Default_MyFunc_NativeEvent),NULL);
}
```

## 行为

在 UE5.8 UHT 中设置 `Event | BlueprintEvent | Native`。UHT 拒绝 replicated/private/accessor 组合以及和 `BlueprintImplementableEvent` 混用。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtFunctionSpecifiers.cs` 对应 specifier 分支
  - UE5.8 `UhtFunction.cs` replicated/event 校验

## 常见误用

声明后不实现 `_Implementation`；或以为它可以直接和 RPC specifier 叠加。
