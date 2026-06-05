---
title: "SetParam"
id: "meta.SetParam"
kind: "meta"
symbol: "SetParam"
category: "Blueprint"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定一个函数为使用Set<TItem>的函数，元素类型为通配符的泛型"
usage: "UFUNCTION"
---

# SetParam

## Decision Summary

- **Use when:** `SetParam` metadata 的 `UFUNCTION` 场景需要：指定一个函数为使用Set<TItem>的函数，元素类型为通配符的泛型。
- **Do not use when:** 目标声明不属于 `UFUNCTION`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 指定一个函数为使用Set<TItem>的函数，元素类型为通配符的泛型。
- **使用位置：** UFUNCTION
- **引擎模块：** Blueprint
- **元数据类型：** string="A | B | C"
- **限制类型：** TSet
- **常用程度：** ★★★

源码在UBlueprintSetLibrary。

SetParam支持多个Set和元素参数，以‘,’分隔开，然后Pin的引脚可以通过‘|’继续分隔，形成”SetA | ItemA, SetB | ItemB”的多组数据。

## 测试代码：

```cpp
	UFUNCTION(BlueprintCallable, CustomThunk, meta = (SetParam = "SetA|ItemA,SetB|ItemB"))
	static void MySet_Add2(const TSet<int32>& SetA, const int32& ItemA, const TSet<int32>& SetB, const int32& ItemB);
	static void GenericMySet_Add2(const void* TargetSet, const FSetProperty* SetA, const void* ItemA, const FSetProperty* SetB, const void* ItemB);
	DECLARE_FUNCTION(execMySet_Add2);
```

## 蓝图里效果：


## 原理：

用‘,’分隔的是组，组内用’|’分隔的参数Pin都是同一种类型的。

```cpp
void UK2Node_CallFunction::ConformContainerPins()
{
		// find any pins marked as SetParam
		const FString& SetPinMetaData = TargetFunction->GetMetaData(FBlueprintMetadata::MD_SetParam);

		// useless copies/allocates in this code, could be an optimization target...
		TArray<FString> SetParamPinGroups;
		{
			SetPinMetaData.ParseIntoArray(SetParamPinGroups, TEXT(","), true);
		}

		for (FString& Entry : SetParamPinGroups)
		{
			// split the group:
			TArray<FString> GroupEntries;
			Entry.ParseIntoArray(GroupEntries, TEXT("|"), true);
			// resolve pins
			TArray<UEdGraphPin*> ResolvedPins;
			for(UEdGraphPin* Pin : Pins)
			{
				if (GroupEntries.Contains(Pin->GetName()))
				{
					ResolvedPins.Add(Pin);
				}
			}

			// if nothing is connected (or non-default), reset to wildcard
			// else, find the first type and propagate to everyone else::
			bool bReadyToPropagatSetType = false;
			FEdGraphTerminalType TypeToPropagate;
			for (UEdGraphPin* Pin : ResolvedPins)
			{
				TryReadTypeToPropagate(Pin, bReadyToPropagatSetType, TypeToPropagate);
				if(bReadyToPropagatSetType)
				{
					break;
				}
			}

			for (UEdGraphPin* Pin : ResolvedPins)
			{
				TryPropagateType( Pin, TypeToPropagate, bReadyToPropagatSetType );
			}
		}
	}
```

## 行为

UE5.8 function/interface metadata；TSet wildcard 参数。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `ObjectMacros.h` metadata declaration/comment
  - UE5.8 `BlueprintGraph` metadata constants or node usage

## 常见误用

参数名、属性名或目标宏写错导致 metadata 被保留但没有对应编辑器/Blueprint 行为。
