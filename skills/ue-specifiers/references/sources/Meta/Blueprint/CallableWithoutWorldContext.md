---
title: "CallableWithoutWorldContext"
id: "meta.CallableWithoutWorldContext"
kind: "meta"
symbol: "CallableWithoutWorldContext"
category: "Blueprint"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "让函数也可以脱离WorldContextObject而使用"
usage: "UFUNCTION"
---

# CallableWithoutWorldContext

## Decision Summary

- **Use when:** 带 `WorldContext` 的函数仍允许没有 world context 的 Blueprint 类调用。
- **Do not use when:** 函数执行必须依赖有效 world，或普通调用点都能提供上下文。
- **Requires:** 通常与 `WorldContext` metadata 一起评估，不是独立的 world 获取机制。
- **Conflicts:** 语义上不要用它绕过真正必需的 world 校验。
- **Prefer instead:** 需要调用方明确传入时显示 world/context 参数，或保留默认 `WorldContext` 行为。

- **功能描述：** 让函数也可以脱离WorldContextObject而使用
- **使用位置：** UFUNCTION
- **元数据类型：** bool
- **关联项：** [WorldContext](WorldContext.md)

让函数也可以脱离WorldContextObject而使用。

CallableWithoutWorldContext 是配合WorldContext或DefaultToSelf来使用，这二者会使得一个函数会要求外部传入一个WorldContext对象才能调用。因此这种函数在没有实现GetWorld的Object子类里就不能调用。但有时某些函数又不一定必须得有WorldContextObject才能工作，比如PrintString或VisualLogger里的函数。

## 测试代码：

```cpp
UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
static FString MyFunc_HasWorldContextMeta(const UObject* WorldContextObject, FString name, FString value);

UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject",CallableWithoutWorldContext))
static FString MyFunc_CallableWithoutWorldContext(const UObject* WorldContextObject, FString name, FString value);

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyObject_NoGetWorld :public UObject
{
	GENERATED_BODY()
};
```

## 蓝图测试效果：

在UMyObject_NoGetWorld 的子类内，MyFunc_HasWorldContextMeta不能调用，因为其外部类必须提供WorldContextObject。而MyFunc_CallableWithoutWorldContext可以调用，可以接受不提供WorldContextObject。


## 源码里典型的应用是：

```cpp
UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject", CallableWithoutWorldContext, Keywords = "log print", AdvancedDisplay = "2", DevelopmentOnly), Category="Development")
static ENGINE_API void PrintString(const UObject* WorldContextObject, const FString& InString = FString(TEXT("Hello")), bool bPrintToScreen = true, bool bPrintToLog = true, FLinearColor TextColor = FLinearColor(0.0f, 0.66f, 1.0f), float Duration = 2.f, const FName Key = NAME_None);
```

## 行为

UE5.8 function metadata；有 world context 但允许无 GetWorld 上下文调用的例外。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `ObjectMacros.h` metadata declaration/comment
  - UE5.8 `BlueprintGraph` metadata constants or node usage

## 常见误用

参数名、属性名或目标宏写错导致 metadata 被保留但没有对应编辑器/Blueprint 行为。
