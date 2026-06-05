---
title: "EditFixedSize"
id: "UPROPERTY.EditFixedSize"
kind: "specifier"
symbol: "EditFixedSize"
scope: "UPROPERTY"
category: "DetailsPanel"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "在细节面板上不允许改变该容器的元素个数"
usage: "UPROPERTY / DetailsPanel"
---

# EditFixedSize

## Decision Summary

- **Use when:** `EditFixedSize` specifier 的 `UPROPERTY / DetailsPanel` 场景需要：在细节面板上不允许改变该容器的元素个数。
- **Do not use when:** 声明宏、目标类型或代码契约不属于 `UPROPERTY / DetailsPanel`。
- **Requires:** specifier 必须放在 UE5.8 UHT 支持的宏和声明位置，并满足正文 caveat。
- **Conflicts:** 不要和同类互斥 specifier 或语义相反的暴露/持久化/网络规则混用。
- **Prefer instead:** 能用更窄暴露范围或更明确 metadata 表达时，优先选择更窄方案。

- **功能描述：** 在细节面板上不允许改变该容器的元素个数。

- **元数据类型：** bool
- **引擎模块：** DetailsPanel, Editor
- **限制类型：** TArray<T>，TSet<T>，TMap<T>
- **作用机制：** 在PropertyFlags中加入CPF_EditFixedSize
- **常用程度：** ★★★

在细节面板上不允许改变该容器的元素个数。

只适用于容器。这能防止用户通过虚幻编辑器属性窗口修改容器的元素个数。

但在C++代码和蓝图中依然是可以修改的。

## 示例代码：

以TArray为例，其他同理。

```cpp
UPROPERTY(EditAnywhere, Category = Array)
		TArray<int32> MyIntArray_Normal{1,2,3};

	UPROPERTY(EditAnywhere, EditFixedSize,Category = Array)
		TArray<int32> MyIntArray_FixedSize{1,2,3};
```

## 示例效果：

蓝图中的表现，前者可以动态再添加元素。后者不可。


## 原理：

如果有CPF_EditFixedSize，则不会添加+和清空的按钮。

```cpp
void PropertyEditorHelpers::GetRequiredPropertyButtons( TSharedRef<FPropertyNode> PropertyNode, TArray<EPropertyButton::Type>& OutRequiredButtons, bool bUsingAssetPicker )
{
	// Handle a container property.
	if( NodeProperty->IsA(FArrayProperty::StaticClass()) || NodeProperty->IsA(FSetProperty::StaticClass()) || NodeProperty->IsA(FMapProperty::StaticClass()) )
	{
		if( !(NodeProperty->PropertyFlags & CPF_EditFixedSize) )
		{
			OutRequiredButtons.Add( EPropertyButton::Add );
			OutRequiredButtons.Add( EPropertyButton::Empty );
		}
	}
}
```

## 行为

在 UE5.8 UHT 中写入 `CPF_EditFixedSize`，用于限制编辑器中容器大小编辑。它不改变 C++ 运行时容器本身的可变性。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `UhtPropertyMemberSpecifiers.cs` 对应 specifier 分支

## 常见误用

以为运行时代码不能 Add/Remove；或用于非容器属性期待有尺寸按钮变化。
