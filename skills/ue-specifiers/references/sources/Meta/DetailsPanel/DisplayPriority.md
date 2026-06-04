---
title: "DisplayPriority"
id: "meta.DisplayPriority"
kind: "meta"
symbol: "DisplayPriority"
category: "DetailsPanel"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定本属性在细节面板的显示顺序优先级，越小的优先级越高"
usage: "UPROPERTY"
---

# DisplayPriority

- **功能描述：** 指定本属性在细节面板的显示顺序优先级，越小的优先级越高。
- **使用位置：** UPROPERTY
- **引擎模块：** DetailsPanel
- **元数据类型：** int32
- **常用程度：** ★★★

指定本属性在细节面板的显示顺序优先级，越小的优先级越高。

- 如果有DisplayAfter的设置，则DisplayAfter的优先级更高。
- 同样的限制得是在同Category里。

## 测试代码：

```cpp
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PriorityTest, meta = (DisplayPriority = 3))
	int32 MyInt_P3 = 123;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PriorityTest, meta = (DisplayPriority = 1))
	int32 MyInt_P1 = 123;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PriorityTest, meta = (DisplayPriority = 2))
	int32 MyInt_P2 = 123;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PriorityTest, meta = (DisplayPriority = 4,DisplayAfter="MyInt_P1"))
	int32 MyInt_P4 = 123;
```

## 测试结果：

P4即使优先级比较低，但因为DisplayAfter也仍然排在了P1之后。


## 原理：

排序的逻辑在这个函数内，自行查看就好。一个简单的插入排序算法。

```cpp
void PropertyEditorHelpers::OrderPropertiesFromMetadata(TArray<FProperty*>& Properties)
{}
```

## 行为

UE5.8 property metadata；ObjectMacros 标注为 Details 中同分类/DisplayAfter 下排序优先级。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `ObjectMacros.h` property/class metadata declaration/comment
  - UE5.8 `PropertyEditor` Details metadata usage

## 常见误用

参数名、属性名或目标宏写错导致 metadata 被保留但没有对应编辑器/Blueprint 行为。
