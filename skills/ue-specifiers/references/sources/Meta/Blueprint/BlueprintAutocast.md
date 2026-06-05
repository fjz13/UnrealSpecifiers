---
title: "BlueprintAutocast"
id: "meta.BlueprintAutocast"
kind: "meta"
symbol: "BlueprintAutocast"
category: "Blueprint"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "告诉蓝图系统这个函数是用来支持从A类型到B类型的自动转换"
usage: "UFUNCTION"
---

# BlueprintAutocast

## Decision Summary

- **Use when:** `BlueprintAutocast` metadata 的 `UFUNCTION` 场景需要：告诉蓝图系统这个函数是用来支持从A类型到B类型的自动转换。
- **Do not use when:** 目标声明不属于 `UFUNCTION`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** 函数应是 `BlueprintPure` 的转换函数；输入和返回类型应表达清晰、低成本、无副作用的 Blueprint 自动转换。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 告诉蓝图系统这个函数是用来支持从A类型到B类型的自动转换。
- **使用位置：** UFUNCTION
- **引擎模块：** Blueprint
- **元数据类型：** bool
- **常用程度：** ★

告诉蓝图系统这个函数是用来支持从A类型到B类型的自动转换。

所谓自动转换指的是从A类型的Pin拖拉到B类型的Pin时，蓝图会在其中自动的生成类型转换节点。

这种转换函数必须是BlueprintPure，因为其实是被动调用的，不带主动执行节点。

## 测试代码：

```cpp
USTRUCT(BlueprintType)
struct FAutoCastFrom
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 X = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Y = 0;
};

USTRUCT(BlueprintType)
struct FAutoCastTo
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Sum = 0;
};

USTRUCT(BlueprintType)
struct FNoAutoCastTo
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Sum = 0;
};

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyFunction_AutoCast :public UBlueprintFunctionLibrary
{
public:
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, meta = (BlueprintAutocast))
	static FAutoCastTo Conv_MyTestAutoCast(const FAutoCastFrom& InValue);
};

//转换函数也经常配合CompactNodeTitle使用。
UFUNCTION(BlueprintPure, Category="Widget", meta = (CompactNodeTitle = "->", BlueprintAutocast))
static UMG_API FInputEvent GetInputEventFromKeyEvent(const FKeyEvent& Event);
```

## 示例效果：

支持自动转换的FAutoCastTo就在拖拉连线的时候就会自动生成节点，而没有自动转换函数的FNoAutoCastTo就会产生报错。


## 原理代码：

从这可以看出，该函数必须是static，C++中的Public函数，标上BlueprintPure，拥有返回值，且有一个输入参数。引擎里类型的自动转换关系是靠FAutocastFunctionMap来维护的。

```cpp
static bool IsAutocastFunction(const UFunction* Function)
{
	const FName BlueprintAutocast(TEXT("BlueprintAutocast"));
	return Function
		&& Function->HasMetaData(BlueprintAutocast)
		&& Function->HasAllFunctionFlags(FUNC_Static | FUNC_Native | FUNC_Public | FUNC_BlueprintPure)
		&& Function->GetReturnProperty()
		&& GetFirstInputProperty(Function);
}
```

## 行为

UE5.8 function metadata；BlueprintGraph 定义为 Blueprint library 自动 cast 节点标记。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `ObjectMacros.h` metadata declaration/comment
  - UE5.8 `BlueprintGraph` metadata constants or node usage

## 常见误用

参数名、属性名或目标宏写错导致 metadata 被保留但没有对应编辑器/Blueprint 行为。
