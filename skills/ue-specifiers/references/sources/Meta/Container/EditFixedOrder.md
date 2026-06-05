---
title: "EditFixedOrder"
id: "meta.EditFixedOrder"
kind: "meta"
symbol: "EditFixedOrder"
category: "Container"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "使数组的元素无法通过拖拽来重新排序"
usage: "UPROPERTY"
---

# EditFixedOrder

## Decision Summary

- **Use when:** `EditFixedOrder` metadata 的 `UPROPERTY` 场景需要：使数组的元素无法通过拖拽来重新排序。
- **Do not use when:** 目标声明不属于 `UPROPERTY`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 使数组的元素无法通过拖拽来重新排序。
- **使用位置：** UPROPERTY
- **引擎模块：** Container Property
- **元数据类型：** bool
- **限制类型：** TArray
- **常用程度：** ★★
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。

## 测试代码：

```cpp
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditFixedOrderTest)
	TArray<int32> MyIntArray_NoEditFixedOrder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditFixedOrderTest, meta = (EditFixedOrder))
	TArray<int32> MyIntArray_EditFixedOrder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditFixedOrderTest)
	TSet<int32> MyIntSet_NoEditFixedOrder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditFixedOrderTest, meta = (EditFixedOrder))
	TSet<int32> MyIntSet_EditFixedOrder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditFixedOrderTest)
	TMap<int32,FString> MyIntMap_NoEditFixedOrder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditFixedOrderTest, meta = (EditFixedOrder))
	TMap<int32,FString> MyIntMap_EditFixedOrder;
```

## 测试效果：

- 可见只有第一个MyIntArray_NoEditFixedOrder，在数组元素上出现可拖拽的标记，然后可以改变顺序。
- 加上EditFixedOrder的TArray就无法改变顺序了。
- 其他TSet，TMap是不支持该meta的，因为其内部本身顺序也无关。


## 原理：

可以看见，细节面板里一个属性行是否可重排序的判断是外部是个数组，且没有EditFixedOrder和ArraySizeEnum（固定数组）。当然本身这个属性也要在可编辑状态（比如被禁用灰掉就显然不可编辑了）

```cpp
bool FPropertyNode::IsReorderable()
{
	FProperty* NodeProperty = GetProperty();
	if (NodeProperty == nullptr)
	{
		return false;
	}
	// It is reorderable if the parent is an array and metadata doesn't prohibit it
	const FArrayProperty* OuterArrayProp = NodeProperty->GetOwner<FArrayProperty>();

	static const FName Name_DisableReordering("EditFixedOrder");
	static const FName NAME_ArraySizeEnum("ArraySizeEnum");
	return OuterArrayProp != nullptr
		&& !OuterArrayProp->HasMetaData(Name_DisableReordering)
		&& !IsEditConst()
		&& !OuterArrayProp->HasMetaData(NAME_ArraySizeEnum)
		&& !FApp::IsGame();
}
```
