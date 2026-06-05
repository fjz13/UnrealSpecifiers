---
title: "InlineColorPicker"
id: "meta.InlineColorPicker"
kind: "meta"
symbol: "InlineColorPicker"
category: "Numeric"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "使FColor或FLinearColor属性在编辑的时候直接内联一个颜色选择器"
usage: "UPROPERTY"
---

# InlineColorPicker

## Decision Summary

- **Use when:** `InlineColorPicker` metadata 的 `UPROPERTY` 场景需要：使FColor或FLinearColor属性在编辑的时候直接内联一个颜色选择器。
- **Do not use when:** 目标声明不属于 `UPROPERTY`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 使FColor或FLinearColor属性在编辑的时候直接内联一个颜色选择器。
- **使用位置：** UPROPERTY
- **引擎模块：** Numeric Property
- **元数据类型：** bool
- **限制类型：** FColor , FLinearColor
- **常用程度：** ★★

使FColor或FLinearColor属性在编辑的时候直接内联一个颜色选择器。

## 测试代码：

```cpp
public:
	UPROPERTY(EditAnywhere, Category = ColorPicker, meta = (InlineColorPicker))
	FColor MyColor_InlineColorPicker;
	UPROPERTY(EditAnywhere, Category = ColorPicker, meta = (InlineColorPicker))
	FLinearColor MyLinearColor_InlineColorPicker;
```

## 测试结果：


## 原理：

根据不同的标记创建不同的的ColorWidget 。

```cpp

void FColorStructCustomization::MakeHeaderRow(TSharedRef<class IPropertyHandle>& InStructPropertyHandle, FDetailWidgetRow& Row)
{
	if (InStructPropertyHandle->HasMetaData("InlineColorPicker"))
	{
		ColorWidget = CreateInlineColorPicker(StructWeakHandlePtr);
		ContentWidth = 384.0f;
	}
	else
	{
		ColorWidget = CreateColorWidget(StructWeakHandlePtr);
	}
}
```

## 行为

UE5.8 color metadata；Details color customization 用于 inline color picker。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `ObjectMacros.h` numeric property metadata declaration/comment
  - UE5.8 Details numeric/color customization metadata usage

## 常见误用

参数名、属性名或目标宏写错导致 metadata 被保留但没有对应编辑器/Blueprint 行为。
