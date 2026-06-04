---
title: "HideThen"
id: "meta.HideThen"
kind: "meta"
symbol: "HideThen"
category: "Blueprint"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "隐藏异步蓝图节点的Then引脚"
usage: "UCLASS"
---

# HideThen

- **功能描述：** 隐藏异步蓝图节点的Then引脚
- **使用位置：** UCLASS
- **元数据类型：** bool
- **限制类型：** 蓝图异步节点
- **关联项：** [ExposedAsyncProxy](ExposedAsyncProxy.md)

在源码中HideThen只在UK2Node_BaseAsyncTask中判断，因此这个标签只作用于蓝图异步节点。

## 测试代码：

```cpp
UCLASS(Blueprintable, BlueprintType,meta = (ExposedAsyncProxy = MyAsyncObject))
class INSIDER_API UMyFunction_Async :public UCancellableAsyncAction
{}

UCLASS(Blueprintable, BlueprintType,meta = (ExposedAsyncProxy = MyAsyncObject,HideThen))
class INSIDER_API UMyFunction_Async :public UCancellableAsyncAction
{}
```

## 使用HideThen前后对比：


## 源码位置：

```cpp
void UK2Node_BaseAsyncTask::AllocateDefaultPins()
{
	bool bExposeProxy = false;
	bool bHideThen = false;
	FText ExposeProxyDisplayName;
	for (const UStruct* TestStruct = ProxyClass; TestStruct; TestStruct = TestStruct->GetSuperStruct())
	{
		bExposeProxy |= TestStruct->HasMetaData(TEXT("ExposedAsyncProxy"));
		bHideThen |= TestStruct->HasMetaData(TEXT("HideThen"));
		if (ExposeProxyDisplayName.IsEmpty())
		{
			ExposeProxyDisplayName = TestStruct->GetMetaDataText(TEXT("ExposedAsyncProxy"));
		}
	}

	if (!bHideThen)
	{
		CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);
	}

}
```

## 行为

UE5.8 Blueprint node metadata；用于隐藏 async/then 类执行 pin 的显示。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `ObjectMacros.h` metadata declaration/comment
  - UE5.8 `BlueprintGraph` metadata constants or node usage

## 常见误用

参数名、属性名或目标宏写错导致 metadata 被保留但没有对应编辑器/Blueprint 行为。
