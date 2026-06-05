---
title: "ShowNormalize"
id: "meta.ShowNormalize"
kind: "meta"
symbol: "ShowNormalize"
category: "Numeric"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "使得FVector变量在细节面板出现一个正规化的按钮"
usage: "UPROPERTY"
---

# ShowNormalize

## Decision Summary

- **Use when:** `ShowNormalize` metadata 的 `UPROPERTY` 场景需要：使得FVector变量在细节面板出现一个正规化的按钮。
- **Do not use when:** 目标声明不属于 `UPROPERTY`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 使得FVector变量在细节面板出现一个正规化的按钮。
- **使用位置：** UPROPERTY
- **引擎模块：** Numeric Property
- **元数据类型：** bool
- **限制类型：** FVector
- **常用程度：** ★★★

使得FVector变量在细节面板出现一个正规化的按钮。

## 测试代码：

```cpp
	UPROPERTY(EditAnywhere, Category = VectorTest)
	FVector MyVector_Default;

	UPROPERTY(EditAnywhere, Category = VectorTest, meta = (AllowPreserveRatio))
	FVector MyVector_AllowPreserveRatio;

	UPROPERTY(EditAnywhere, Category = VectorTest, meta = (ShowNormalize))
	FVector MyVector_ShowNormalize;
```

## 测试结果：

MyVector_ShowNormalize右侧的按钮可以把值正规化。


## 原理：

其实就是UI定制化的时候检测出ShowNormalize就创建单独的UI。

```cpp
if (StructPropertyHandle->HasMetaData("ShowNormalize") && MathStructCustomization::IsFloatVector(StructPropertyHandle))
{
	HorizontalBox->AddSlot()
		.AutoWidth()
		.MaxWidth(18.0f)
		.VAlign(VAlign_Center)
		[
			// Add a button to scale the vector uniformly to achieve a unit vector
			SNew(SButton)
				.OnClicked(this, &FMathStructCustomization::OnNormalizeClicked, StructWeakHandlePtr)
				.ButtonStyle(FAppStyle::Get(), "NoBorder")
				.ToolTipText(LOCTEXT("NormalizeToolTip", "When clicked, if the vector is large enough, it scales the vector uniformly to achieve a unit vector (vector with a length of 1)"))
				[
					SNew(SImage)
						.ColorAndOpacity(FSlateColor::UseForeground())
						.Image(FAppStyle::GetBrush(TEXT("Icons.Normalize")))
				]
		];
}
```

## 行为

UE5.8 numeric/vector metadata；Details vector customization 显示 normalize 操作。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `ObjectMacros.h` numeric property metadata declaration/comment
  - UE5.8 Details numeric/color customization metadata usage

## 常见误用

参数名、属性名或目标宏写错导致 metadata 被保留但没有对应编辑器/Blueprint 行为。
