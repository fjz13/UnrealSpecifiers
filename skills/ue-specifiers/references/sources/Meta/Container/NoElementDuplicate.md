---
title: "NoElementDuplicate"
id: "meta.NoElementDuplicate"
kind: "meta"
symbol: "NoElementDuplicate"
category: "Container"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "去除TArray属性里数据项的Duplicate菜单项按钮"
usage: "UPROPERTY"
---

# NoElementDuplicate

## Decision Summary

- **Use when:** `NoElementDuplicate` metadata 的 `UPROPERTY` 场景需要：去除TArray属性里数据项的Duplicate菜单项按钮。
- **Do not use when:** 目标声明不属于 `UPROPERTY`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 去除TArray属性里数据项的Duplicate菜单项按钮。
- **使用位置：** UPROPERTY
- **引擎模块：** Container Property
- **元数据类型：** bool
- **限制类型：** TArray
- **常用程度：** ★

去除TArray属性里数据项的Duplicate菜单项按钮。

用于TArray属性，值可以是任何类型，可以是数值，结构，也可以是Object*。
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。

## 测试代码：

```cpp
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = IntArray)
	TArray<int32> MyIntArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = IntArray, meta = (NoElementDuplicate))
	TArray<int32> MyIntArray_NoElementDuplicate;
```

## 效果：

可以看到带有NoElementDuplicate的数组，在值的右侧下拉箭头的菜单项里只有两项。


## 原理：

判断如有NoElementDuplicate，则只生成Insert_Delete 菜单，否则是默认的Insert_Delete_Duplicate 。当然要求当前属性是数组属性，且不是EditFixedSize固定大小的。

```cpp
void GetRequiredPropertyButtons( TSharedRef<FPropertyNode> PropertyNode, TArray<EPropertyButton::Type>& OutRequiredButtons, bool bUsingAssetPicker )
{
		const FArrayProperty* OuterArrayProp = NodeProperty->GetOwner<FArrayProperty>();

		if( OuterArrayProp )
		{
			if( PropertyNode->HasNodeFlags(EPropertyNodeFlags::SingleSelectOnly) && !(OuterArrayProp->PropertyFlags & CPF_EditFixedSize) )
			{
				if (OuterArrayProp->HasMetaData(TEXT("NoElementDuplicate")))
				{
					OutRequiredButtons.Add( EPropertyButton::Insert_Delete );
				}
				else
				{
					OutRequiredButtons.Add( EPropertyButton::Insert_Delete_Duplicate );
				}
			}
		}
}
```
