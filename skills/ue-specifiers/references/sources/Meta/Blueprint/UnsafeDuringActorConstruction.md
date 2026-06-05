---
title: "UnsafeDuringActorConstruction"
id: "meta.UnsafeDuringActorConstruction"
kind: "meta"
symbol: "UnsafeDuringActorConstruction"
category: "Blueprint"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "标明该函数不能在Actor的构造函数里调用"
usage: "UFUNCTION"
---

# UnsafeDuringActorConstruction

## Decision Summary

- **Use when:** `UnsafeDuringActorConstruction` metadata 的 `UFUNCTION` 场景需要：标明该函数不能在Actor的构造函数里调用。
- **Do not use when:** 目标声明不属于 `UFUNCTION`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 标明该函数不能在Actor的构造函数里调用
- **使用位置：** UFUNCTION
- **引擎模块：** Blueprint
- **元数据类型：** bool
- **常用程度：** ★★

标明该函数不能在Actor的构造函数里调用。一般是涉及渲染及物理的函数，在Actor的构造期间不允许被调用。

## 测试代码：

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyFunction_Unsafe :public UBlueprintFunctionLibrary
{
public:
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	static void MySafeFunction();
	UFUNCTION(BlueprintCallable, meta=(UnsafeDuringActorConstruction = "true"))
	static void MyUnsafeFunction();
};
```

在蓝图里函数的细节面板上也可以设置该Meta：UnsafeDuringActorConstruction，和在C++里设置是一样的效果。

可以发现MyUnsafeFunction函数不能在Actor构造函数里被调用出来，而蓝图里自定义的函数加上UnsafeDuringActorConstruction 标志后也会生成相应的警告和编译错误信息。


## 原理：

在蓝图中有该系列的判断，一目了然。

```cpp
bool UEdGraphSchema_K2::CanFunctionBeUsedInGraph(const UClass* InClass, const UFunction* InFunction, const UEdGraph* InDestGraph, uint32 InAllowedFunctionTypes, bool bInCalledForEach, FText* OutReason) const
{
const bool bIsUnsafeForConstruction = InFunction->GetBoolMetaData(FBlueprintMetadata::MD_UnsafeForConstructionScripts);
if (bIsUnsafeForConstruction && bIsConstructionScript)
{
	if(OutReason != nullptr)
	{
		*OutReason = LOCTEXT("FunctionUnsafeForConstructionScript", "Function cannot be used in a Construction Script.");
	}

	return false;
}
}
```

## 行为

UE5.8 function metadata；BlueprintGraph 定义为 Construction Script 中不允许调用。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `ObjectMacros.h` metadata declaration/comment
  - UE5.8 `BlueprintGraph` metadata constants or node usage

## 常见误用

参数名、属性名或目标宏写错导致 metadata 被保留但没有对应编辑器/Blueprint 行为。
