# BaseClass

- **Function Description:** Used exclusively within the StateTree module to restrict the base class type for selection in FStateTreeEditorNode.
- **Usage Location:** UPROPERTY
- **Engine Module:** TypePicker
- **Metadata Type:** bool
- **Restriction Type:** FStateTreeEditorNode attribute
- **Commonality:** ★

Only utilized in the StateTree module to limit the base class type that can be selected by FStateTreeEditorNode.

## Source Code Example:

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

## Test Results:

It is evident that although both Conditions and Tasks are of type FStateTreeEditorNode, the content in the option list differs. This discrepancy is due to the differing BaseStruct and BaseClass specifications above, which define the base class types for the structure and blueprint class, respectively.

![Untitled](Untitled.png)

## Principle:

This property is retrieved in the UI customization of FStateTreeEditorNode and then employed to filter the available node types.

```cpp
void FStateTreeEditorNodeDetails::CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
		static const FName BaseClassMetaName(TEXT("BaseClass")); // TODO: move these names into one central place.
		const FString BaseClassName = StructProperty->GetMetaData(BaseClassMetaName);
		BaseClass = UClass::TryFindTypeSlow<UClass>(BaseClassName);
}

```