---
title: "PrioritizeCategories"
id: "UCLASS.PrioritizeCategories"
kind: "specifier"
symbol: "PrioritizeCategories"
scope: "UCLASS"
category: "Category"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "把指定的属性目录优先显示在细节面板的前面"
usage: "UCLASS / Category"
---

# PrioritizeCategories

## Decision Summary

- **Use when:** `PrioritizeCategories` specifier 的 `UCLASS / Category` 场景需要：把指定的属性目录优先显示在细节面板的前面。
- **Do not use when:** 声明宏、目标类型或代码契约不属于 `UCLASS / Category`。
- **Requires:** specifier 必须放在 UE5.8 UHT 支持的宏和声明位置，并满足正文 caveat。
- **Conflicts:** 不要和同类互斥 specifier 或语义相反的暴露/持久化/网络规则混用。
- **Prefer instead:** 能用更窄暴露范围或更明确 metadata 表达时，优先选择更窄方案。

- **功能描述：**  把指定的属性目录优先显示在细节面板的前面。
- **引擎模块：** Category
- **元数据类型：** strings=(abc，"d|e"，"x|y|z")
- **作用机制：** 在Meta中增加[PrioritizeCategories](../../../Meta/DetailsPanel/PrioritizeCategories.md)
- **常用程度：★★★**

把指定的属性目录优先显示在细节面板的前面。

## 示例代码：

```cpp
UCLASS(Blueprintable, PrioritizeCategories= ("MyGroup3|MyGroup33|MyGroup333","MyGroup1"))
class INSIDER_API UMyClass_PrioritizeCategories :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Property_NotInGroup;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyGroup1")
		int Property_Group1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyGroup2|MyGroup22")
		int Property_Group22;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyGroup3|MyGroup33|MyGroup333")
		int Property_Group333;
};
```

## 示例结果：

可见Property_Group333排到了最前面。


## 原理：

在UClass::GetPrioritizeCategories(TArray<FString>& OutPrioritizedCategories)中获取优先级目录。原理是按照指定的顺序放到SortedCategories里，所以就会被首先创建出属性目录来。

```cpp
TArray<FString> ClassPrioritizeCategories;
Class->GetPrioritizeCategories(ClassPrioritizeCategories);
for (const FString& ClassPrioritizeCategory : ClassPrioritizeCategories)
{
	FName PrioritizeCategoryName = FName(ClassPrioritizeCategory);
	SortedCategories.AddUnique(PrioritizeCategoryName);
	PrioritizeCategories.AddUnique(PrioritizeCategoryName);
}

```

## 行为

UE5.8 UHT 把分类加入 `PrioritizeCategories` 列表，影响 Details 分类显示优先级。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtClassSpecifiers.cs` class specifier branch
  - UE5.8 `UhtClass.cs` class flag/metadata resolution and validation

## 常见误用

把 class specifier 的 metadata/flag 结果和 property/function specifier 混淆；或忽略继承/撤销类 specifier 的相互作用。
