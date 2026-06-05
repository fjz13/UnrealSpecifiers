---
title: "Keywords"
id: "meta.Blueprint.Keywords"
kind: "meta"
symbol: "Keywords"
category: "Blueprint"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定一系列关键字用于在蓝图内右键找到该函数"
usage: "UFUNCTION"
---

# Keywords

## Decision Summary

- **Use when:** Blueprint 节点需要通过同义词或常用搜索词更容易被找到。
- **Do not use when:** 关键词只是重复节点名或堆砌无关词。
- **Requires:** 关键词应贴近用户会搜索的术语。
- **Conflicts:** 不改变节点行为或分类。
- **Prefer instead:** 节点命名和 Category 已足够清楚时不添加。

- **功能描述：** 指定一系列关键字用于在蓝图内右键找到该函数
- **使用位置：** UFUNCTION
- **引擎模块：** Blueprint
- **元数据类型：** string="abc"
- **常用程度：** ★★★★★

Keywords里的单词可以用空格隔开，也可以逗号隔开。这里面的文本是会被进行字符串匹配搜索。

## 测试代码：

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyFunction_Keywords :public UBlueprintFunctionLibrary
{
public:
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable,meta=(Keywords="This is a SuperFunc,OtherFunc"))
	static void MyFunc_HasKeyworlds();
};
```

## 蓝图效果：


## 原理：

该Keywords的内容，最终会被FEdGraphSchemaAction所应用，用于蓝图内右键菜单的文本搜索。

另外每个K2Node都可以返回一个Keywords。效果应该跟函数上的Keywords一样。

```cpp
FText UEdGraphNode::GetKeywords() const
{
	return GetClass()->GetMetaDataText(TEXT("Keywords"), TEXT("UObjectKeywords"), GetClass()->GetFullGroupName(false));
}
```

## 行为

UE5.8 function metadata；BlueprintGraph `Keywords` 用于节点搜索关键字。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `ObjectMacros.h` metadata declaration/comment
  - UE5.8 `BlueprintGraph` metadata constants or node usage

## 常见误用

参数名、属性名或目标宏写错导致 metadata 被保留但没有对应编辑器/Blueprint 行为。
