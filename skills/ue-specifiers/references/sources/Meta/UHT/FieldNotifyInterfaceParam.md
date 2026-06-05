---
title: "FieldNotifyInterfaceParam"
id: "meta.FieldNotifyInterfaceParam"
kind: "meta"
symbol: "FieldNotifyInterfaceParam"
category: "UHT"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定函数的某个参数提供FieldNotify的ViewModel信息"
usage: "UFUNCTION"
---

# FieldNotifyInterfaceParam

## Decision Summary

- **Use when:** `FieldNotifyInterfaceParam` metadata 的 `UFUNCTION` 场景需要：指定函数的某个参数提供FieldNotify的ViewModel信息。
- **Do not use when:** 目标声明不属于 `UFUNCTION`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 指定函数的某个参数提供FieldNotify的ViewModel信息。
- **使用位置：** UFUNCTION
- **引擎模块：** FieldNotify
- **元数据类型：** string="abc"
- **限制类型：** 函数里有其他FFieldNotificationId 参数
- **常用程度：** ★★★

指定函数的某个参数提供FieldNotify的ViewModel信息。

该参数为之后的FFieldNotificationId参数的提供上下文信息，这样FieldId的选项框才知道有哪些可选值。
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。

## 源码例子：

```cpp
	/** Broadcast that the Field value changed. */
	UFUNCTION(BlueprintCallable, Category = "FieldNotification", meta = (FieldNotifyInterfaceParam="Object", DisplayName = "Broadcast Field Value Changed"))
	static void BroadcastFieldValueChanged(UObject* Object, FFieldNotificationId FieldId);

```

## 蓝图效果：

在UserWidget里测试，可见没有连接到参数的Target默认为当前的UserWidget，则FieldId是3个值。而连接到我们自定义的ViewModel后，则改变为我们下面定义的值。


## 原理：

```cpp
TSharedRef<SWidget> SFieldNotificationGraphPin::GetDefaultValueWidget()
{
	UEdGraphPin* SelfPin = GraphPinObj->GetOwningNode()->FindPin(UEdGraphSchema_K2::PSC_Self);
	if (UK2Node_CallFunction* CallFunction = Cast<UK2Node_CallFunction>(GraphPinObj->GetOwningNode()))
	{
		if (UFunction* Function = CallFunction->GetTargetFunction())
		{
			const FString& PinName = Function->GetMetaData("FieldNotifyInterfaceParam");
			if (PinName.Len() != 0)
			{
				SelfPin = GraphPinObj->GetOwningNode()->FindPin(*PinName);
			}
		}
	}

	return SNew(SFieldNotificationPicker)
		.Value(this, &SFieldNotificationGraphPin::GetValue)
		.OnValueChanged(this, &SFieldNotificationGraphPin::SetValue)
		.FromClass_Static(Private::GetPinClass, SelfPin)
		.Visibility(this, &SGraphPin::GetDefaultValueVisibility);
}
```
