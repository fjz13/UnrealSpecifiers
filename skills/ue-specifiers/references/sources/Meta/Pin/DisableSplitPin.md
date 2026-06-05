---
title: "DisableSplitPin"
id: "meta.DisableSplitPin"
kind: "meta"
symbol: "DisableSplitPin"
category: "Pin"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "禁用Struct的split功能"
usage: "USTRUCT"
---

# DisableSplitPin

## Decision Summary

- **Use when:** `DisableSplitPin` metadata 的 `USTRUCT` 场景需要：禁用Struct的split功能。
- **Do not use when:** 目标声明不属于 `USTRUCT`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 禁用Struct的split功能
- **使用位置：** USTRUCT
- **引擎模块：** Pin
- **元数据类型：** bool
- **常用程度：** ★★

对于某些Struct，特别是只有一个成员变量的结构，有时候如果按照默认的展开则会显得很怪。这个时候就希望能够禁用掉这个功能。但是注意依然可以手动在蓝图里Break来访问成员变量。如果在蓝图里也不想暴露成员变量访问，那应该在UPROPERTY上不能加BlueprintReadWrite/BlueprintReadOnly

在源码里搜索，如FGameplayTag，FPostProcessSettings，FSlatePostSettings

## 测试代码：

```cpp
USTRUCT(BlueprintType, meta = (DisableSplitPin))
struct INSIDER_API FMyStruct_DisableSplitPin
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MyFloat;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString MyString;
};

USTRUCT(BlueprintType)
struct INSIDER_API FMyStruct_WithSplitPin
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MyFloat;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString MyString;
};
```


允许的对比


## 行为

UE5.8 struct/pin metadata；BlueprintGraph `MD_NativeDisableSplitPin`，禁止 struct pin split。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `ObjectMacros.h` metadata declaration/comment
  - UE5.8 `BlueprintGraph` metadata constants or node usage

## 常见误用

参数名、属性名或目标宏写错导致 metadata 被保留但没有对应编辑器/Blueprint 行为。
