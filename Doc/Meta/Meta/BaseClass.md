# BaseClass

Usage: UPROPERTY
Feature: Blueprint
Type: bool
Description: 只在StateTree模块中使用，限制FStateTreeEditorNode选择的基类类型。
LimitedType: FStateTreeEditorNode属性
Status: Done
Group: TypePicker

只在StateTree模块中使用，限制FStateTreeEditorNode选择的基类类型。

源码例子：

```cpp

USTRUCT()
struct STATETREEEDITORMODULE_API FStateTreeTransition
{
	/** Conditions that must pass so that the transition can be triggered. */
	UPROPERTY(EditDefaultsOnly, Category = "Transition", meta = (BaseStruct = "/Script/StateTreeModule.StateTreeConditionBase", BaseClass = "/Script/StateTreeModule.StateTreeConditionBlueprintBase"))
	TArray<FStateTreeEditorNode> Conditions;
	
	UPROPERTY(EditDefaultsOnly, Category = "Tasks", meta = (BaseStruct = "/Script/StateTreeModule.StateTreeTaskBase", BaseClass = "/Script/StateTreeModule.StateTreeTaskBlueprintBase"))
	TArray<FStateTreeEditorNode> Tasks;
}
```

测试结果：

可见，虽然Conditions和Tasks的类型都是FStateTreeEditorNode，但是选项列表里的内容是不同的。这是由于其上面的BaseStruct和BaseClass 不同，分别限定了结构的基类类型以及蓝图类的基类。

![Untitled](BaseClass/Untitled.png)

原理：

在FStateTreeEditorNode的UI定制化上获取该属性，然后用来过滤可用的节点类型。

```cpp
void FStateTreeEditorNodeDetails::CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
		static const FName BaseClassMetaName(TEXT("BaseClass")); // TODO: move these names into one central place.
		const FString BaseClassName = StructProperty->GetMetaData(BaseClassMetaName);
		BaseClass = UClass::TryFindTypeSlow<UClass>(BaseClassName);
}

```