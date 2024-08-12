# FieldNotifyInterfaceParam

Usage: UFUNCTION
Feature: Blueprint
Type: string="abc"
Description: Function /Script/Engine.FieldNotificationLibrary:BroadcastFieldsValueChanged
LimitedType: 函数里有其他FFieldNotificationId 参数
Status: OnlyInternal
Group: FieldNotify

指定函数的某个参数提供FieldNotify的ViewModel信息。

该参数为之后的FFieldNotificationId参数的提供上下文信息，这样FieldId的选项框才知道有哪些可选值。

源码例子：

```cpp
	/** Broadcast that the Field value changed. */
	UFUNCTION(BlueprintCallable, Category = "FieldNotification", meta = (FieldNotifyInterfaceParam="Object", DisplayName = "Broadcast Field Value Changed"))
	static void BroadcastFieldValueChanged(UObject* Object, FFieldNotificationId FieldId);

```

蓝图效果：

在UserWidget里测试，可见没有连接到参数的Target默认为当前的UserWidget，则FieldId是3个值。而连接到我们自定义的ViewModel后，则改变为我们下面定义的值。

![Untitled](FieldNotifyInterfaceParam/Untitled.png)

原理：

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