---
title: "NoResetToDefault"
id: "meta.NoResetToDefault"
kind: "meta"
symbol: "NoResetToDefault"
category: "DetailsPanel"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "禁用和隐藏属性在细节面板上的“重置”功能"
usage: "UPROPERTY"
---

# NoResetToDefault

## Decision Summary

- **Use when:** `NoResetToDefault` metadata 的 `UPROPERTY` 场景需要：禁用和隐藏属性在细节面板上的“重置”功能。
- **Do not use when:** 目标声明不属于 `UPROPERTY`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** 只影响 Details Panel 是否显示 reset-to-default 入口，不改变默认值、序列化或 runtime reset 逻辑。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 禁用和隐藏属性在细节面板上的“重置”功能。
- **使用位置：** UPROPERTY
- **引擎模块：** DetailsPanel
- **元数据类型：** bool
- **常用程度：** ★★★

禁用和隐藏属性在细节面板上的“重置”功能。

## 测试代码：

```cpp
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category=ResetToDefaultTest)
	int32 MyInt_Default = 123;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category=ResetToDefaultTest, meta = (NoResetToDefault))
	int32 MyInt_NoResetToDefault = 123;
```

## 测试效果：

可以发现默认的属性在改变值后，右侧会出现一个重置按钮，以便让属性重置回默认值。NoResetToDefault的作用就是去除这个功能。


## 原理：

编辑器里会判断这个meta，如果没有则创建SResetToDefaultPropertyEditor。

```cpp
bool SSingleProperty::GeneratePropertyCustomization()
{
		if (!PropertyEditor->GetPropertyHandle()->HasMetaData(TEXT("NoResetToDefault")) && !bShouldHideResetToDefault)
		{
			HorizontalBox->AddSlot()
			.Padding( 2.0f )
			.AutoWidth()
			.VAlign( VAlign_Center )
			[
				SNew( SResetToDefaultPropertyEditor,  PropertyEditor->GetPropertyHandle() )
			];
		}
}
```

## 行为

UE5.8 property metadata；ObjectMacros 标注为隐藏 reset-to-default 按钮。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `ObjectMacros.h` property/class metadata declaration/comment
  - UE5.8 `PropertyEditor` Details metadata usage

## 常见误用

参数名、属性名或目标宏写错导致 metadata 被保留但没有对应编辑器/Blueprint 行为。
