---
title: "HideDropDown"
id: "UCLASS.HideDropDown"
kind: "specifier"
symbol: "HideDropDown"
scope: "UCLASS"
category: "TypePicker"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "在类选择器中隐藏此类"
usage: "UCLASS / TypePicker"
---

# HideDropDown

- **功能描述：**  在类选择器中隐藏此类
- **引擎模块：** TypePicker
- **元数据类型：** bool
- **作用机制：** 在ClassFlags中添加CLASS_HideDropDown
- **常用程度：★★**

在类选择器中隐藏此类，通常是TSubClassOf触发，或者Class变量触发的类选择窗口。这个时候，这个标识符可以阻止其出现。在源码里的使用，通常是一些旧的废弃的类或者Test类，Abstract类和基类。

## 示例代码：

```cpp
UCLASS(Blueprintable)
class INSIDER_API UMyClass_HideDropDownBase :public UObject
{
	GENERATED_BODY()
public:
};

UCLASS(Blueprintable, hidedropdown)
class INSIDER_API UMyClass_HideDropDown :public UMyClass_HideDropDownBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyProperty;
};

UCLASS(Blueprintable, hidedropdown)
class INSIDER_API UMyClass_NoHideDropDown :public UMyClass_HideDropDownBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyProperty;
};

UCLASS(Blueprintable)
class INSIDER_API UMyClass_HideDropDown_Test :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UMyClass_HideDropDownBase> DropDownClass;
};
```

## 示例结果：

![Untitled](Untitled.png)

## 原理：

HideDropDown会造成CLASS_HideDropDown标记，从而在类型UI定制化的列表里把该类剔除出去。

```cpp
template <typename TClass>
bool FPropertyEditorClassFilter::IsClassAllowedHelper(TClass InClass)
{
	bool bMatchesFlags = !InClass->HasAnyClassFlags(CLASS_Hidden | CLASS_HideDropDown | CLASS_Deprecated) &&
		(bAllowAbstract || !InClass->HasAnyClassFlags(CLASS_Abstract));

	if (bMatchesFlags && InClass->IsChildOf(ClassPropertyMetaClass)
		&& (!InterfaceThatMustBeImplemented || InClass->ImplementsInterface(InterfaceThatMustBeImplemented)))
	{
		auto PredicateFn = [InClass](const UClass* Class)
		{
			return InClass->IsChildOf(Class);
		};

		if (DisallowedClassFilters.FindByPredicate(PredicateFn) == nullptr &&
			(AllowedClassFilters.Num() == 0 || AllowedClassFilters.FindByPredicate(PredicateFn) != nullptr))
		{
			return true;
		}
	}

	return false;
}
```

## 行为

UE5.8 UHT 写入 `CLASS_HideDropDown`，用于类选择/下拉列表隐藏。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtClassSpecifiers.cs` class specifier branch
  - UE5.8 `UhtClass.cs` class flag/metadata resolution and validation

## 常见误用

把 class specifier 的 metadata/flag 结果和 property/function specifier 混淆；或忽略继承/撤销类 specifier 的相互作用。
