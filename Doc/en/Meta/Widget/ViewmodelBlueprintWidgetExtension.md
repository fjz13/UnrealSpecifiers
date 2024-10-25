# ViewmodelBlueprintWidgetExtension

- **Function Description:** This function verifies if the Object type of InListItems matches the ViewModelProperty bound to EntryWidgetClass via MVVM.
- **Usage Location:** UFUNCTION
- **Engine Module:** Widget Property
- **Metadata Type:** string="abc"
- **Frequency of Use:** 0

This function verifies if the Object type of InListItems conforms to the ViewModelProperty bound to EntryWidgetClass in an MVVM context.

Currently, this function is only used within the ListView.

## Principle:

```cpp
UCLASS(meta = (EntryInterface = "/Script/UMG.UserObjectListEntry"), MinimalAPI)
class UListView : public UListViewBase, public ITypedUMGListView<UObject*>
{
	UFUNCTION(BlueprintCallable, Category = ListView, meta = (AllowPrivateAccess = true, DisplayName = "Set List Items", ViewmodelBlueprintWidgetExtension = "EntryViewModel"))
	UMG_API void BP_SetListItems(const TArray<UObject*>& InListItems);
}

void UMVVMViewBlueprintListViewBaseExtension::Precompile(UE::MVVM::Compiler::IMVVMBlueprintViewPrecompile* Compiler, UWidgetBlueprintGeneratedClass* Class)
{
}
```