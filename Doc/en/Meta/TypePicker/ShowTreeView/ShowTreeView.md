# ShowTreeView

- **Function description:** Used to select attributes of Class or Struct so that they are displayed as a tree rather than a list in the class selector.
- **Use location:** UPROPERTY
- **Engine module:** TypePicker
- **Metadata type:** bool
- **Limit types:** TSubClassOf, FSoftClassPath, UClass*, UScriptStruct*, FInstancedStruct
- **Frequency of use:** ★★

Applied to Class or Struct attributes to display them as a tree rather than a list in the class selector.

Applies to attribute types such as TSubClassOf, FSoftClassPath, UClass*, UScriptStruct*, FInstancedStruct, which are used for type selection. It does not function with TSoftObjectPtr or FSoftObjectPath, which are used for object selection.

## Test Code:

```cpp
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShowTreeViewTest|TSubclassOf")
	TSubclassOf<UObject> MyClass_NotShowTreeView;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShowTreeViewTest|TSubclassOf", meta = (ShowTreeView))
	TSubclassOf<UObject> MyClass_ShowTreeView;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShowTreeViewTest|UClass*")
	UClass* MyClassPtr_NotShowTreeView;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShowTreeViewTest|UClass*", meta = (ShowTreeView))
	UClass* MyClassPtr_ShowTreeView;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShowTreeViewTest|FSoftClassPath")
	FSoftClassPath MySoftClass_NotShowTreeView;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShowTreeViewTest|FSoftClassPath", meta = (ShowTreeView))
	FSoftClassPath MySoftClass_ShowTreeView;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShowTreeViewTest|UScriptStruct*")
	UScriptStruct* MyStructPtr_NotShowTreeView;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShowTreeViewTest|UScriptStruct*", meta = (ShowTreeView))
	UScriptStruct* MyStructPtr_ShowTreeView;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShowTreeViewTest|FInstancedStruct")
	FInstancedStruct MyInstancedStruct_NotShowTreeView;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShowTreeViewTest|FInstancedStruct", meta = (ShowTreeView))
	FInstancedStruct MyInstancedStruct_ShowTreeView;
```

## Test Results:

It is evident that properties with the ShowTreeView attribute are displayed as a tree in the pop-up selection box, rather than as a list.

![ShowTreeView](ShowTreeView.jpg)

## Principle:

In the source code, SPropertyEditorClass is used for TSubClassOf and UClass*, FSoftClassPathCustomization for FSoftClassPath, SPropertyEditorStruct for UScriptStruct*, and FInstancedStructDetails for FInstancedStruct to customize the UI.

```cpp
void FSoftClassPathCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
		const bool bShowTreeView = PropertyHandle->HasMetaData("ShowTreeView");
		const bool bHideViewOptions = PropertyHandle->HasMetaData("HideViewOptions");

	SNew(SClassPropertyEntryBox)
		.ShowTreeView(bShowTreeView)
		.HideViewOptions(bHideViewOptions)
		.ShowDisplayNames(bShowDisplayNames)
}

void SPropertyEditorClass::Construct(const FArguments& InArgs, const TSharedPtr< FPropertyEditor >& InPropertyEditor)
{
		bShowViewOptions = Property->GetOwnerProperty()->HasMetaData(TEXT("HideViewOptions")) ? false : true;
		bShowTree = Property->GetOwnerProperty()->HasMetaData(TEXT("ShowTreeView"));
		bShowDisplayNames = Property->GetOwnerProperty()->HasMetaData(TEXT("ShowDisplayNames"));
}
void SPropertyEditorStruct::Construct(const FArguments& InArgs, const TSharedPtr< class FPropertyEditor >& InPropertyEditor)
{
		bShowViewOptions = Property->GetOwnerProperty()->HasMetaData(TEXT("HideViewOptions")) ? false : true;
		bShowTree = Property->GetOwnerProperty()->HasMetaData(TEXT("ShowTreeView"));
		bShowDisplayNames = Property->GetOwnerProperty()->HasMetaData(TEXT("ShowDisplayNames"));
}
TSharedRef<SWidget> FInstancedStructDetails::GenerateStructPicker()
{
		const bool bExcludeBaseStruct = StructProperty->HasMetaData(NAME_ExcludeBaseStruct);
		const bool bAllowNone = !(StructProperty->GetMetaDataProperty()->PropertyFlags & CPF_NoClear);
		const bool bHideViewOptions = StructProperty->HasMetaData(NAME_HideViewOptions);
		const bool bShowTreeView = StructProperty->HasMetaData(NAME_ShowTreeView);
}
```