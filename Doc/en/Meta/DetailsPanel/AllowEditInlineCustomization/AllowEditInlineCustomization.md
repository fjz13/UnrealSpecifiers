# AllowEditInlineCustomization

- **Function Description:** Allows the customization of the property details panel for EditInline object properties to edit the data within the object.
- **Usage Location:** UPROPERTY
- **Metadata Type:** string="abc"
- **Associated Items:** [EditInline](../EditInline/EditInline.md)
- **Commonality:** ★

Enables the customization of the property details panel for EditInline object properties to edit the data within the object.

## Test Code:

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyCommonObject :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MyInt = 123;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString MyString;
};

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyCustomAsset :public UObject
{
	GENERATED_BODY()
public:
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditInline))
	UMyCommonObject* MyCommonObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditInline,AllowEditInlineCustomization))
	UMyCommonObject* MyCommonObject_Customization;
};

```

## Effect:

![Untitled](Untitled.png)

To achieve the custom EditInline effect, using a custom IPropertyTypeCustomization and RegisterCustomPropertyTypeLayout can also be done. The difference is, as in the code example with UMyCustomAsset, which contains two UMyCommonObject* objects of the same type, using the IPropertyTypeCustomization approach would result in both variables being converted to a custom UI mode. However, with AllowEditInlineCustomization, you can customize the desired object while leaving the others unchanged.

In usage, AllowEditInlineCustomization must be used in conjunction with a custom FAssetEditorToolkit to define a DetailView (not just customizing the display of a specific type within the engine's unified DetailView), then customize IDetailCustomization to provide specific Widgets, and finally, use RegisterInstancedCustomPropertyLayout to establish the association.

```cpp
DetailsView->RegisterInstancedCustomPropertyLayout(UMyCommonObject::StaticClass(),FOnGetDetailCustomizationInstance::CreateStatic(&FMyCommonObjectDetailsCustomization::MakeInstance));
```

(Refer to the relevant implementation in MyCustomAsset for this code section)

## Source Code:

```cpp
FDetailPropertyRow::FDetailPropertyRow(TSharedPtr<FPropertyNode> InPropertyNode, TSharedRef<FDetailCategoryImpl> InParentCategory, TSharedPtr<FComplexPropertyNode> InExternalRootNode)
{
		static FName InlineCustomizationKeyMeta("AllowEditInlineCustomization");
		if (PropertyNode->AsComplexNode() && ExternalRootNode.IsValid()) // AsComplexNode works both for objects and structs
		{
			// We are showing an entirely different object inline.  Generate a layout for it now.
			if (IDetailsViewPrivate* DetailsView = InParentCategory->GetDetailsView())
			{
				ExternalObjectLayout = MakeShared<FDetailLayoutData>();
				DetailsView->UpdateSinglePropertyMap(InExternalRootNode, *ExternalObjectLayout, true);
			}
		}
		else if (PropertyNode->HasNodeFlags(EPropertyNodeFlags::EditInlineNew) && PropertyNode->GetProperty()->HasMetaData(InlineCustomizationKeyMeta))
		{
			// Allow customization of 'edit inline new' objects if the metadata key has been specified.
			// The child of this node, if set, will be an object node that we will want to treat as an 'external object layout'
			TSharedPtr<FPropertyNode> ChildNode = PropertyNode->GetNumChildNodes() > 0 ? PropertyNode->GetChildNode(0) : nullptr;
			TSharedPtr<FComplexPropertyNode> ComplexChildNode = StaticCastSharedPtr<FComplexPropertyNode>(ChildNode);
			if (ComplexChildNode.IsValid())
			{
				// We are showing an entirely different object inline.  Generate a layout for it now.
				if (IDetailsViewPrivate* DetailsView = InParentCategory->GetDetailsView())
				{
					ExternalObjectLayout = MakeShared<FDetailLayoutData>();
					DetailsView->UpdateSinglePropertyMap(ComplexChildNode, *ExternalObjectLayout, true);
				}
			}
		}

}
```

The principle of operation is that when creating an FDetailPropertyRow, which is a row for a property in the details panel, if AllowEditInlineCustomization is present, an ExternalObjectLayout is created. Subsequently, when creating children for FDetailPropertyRow, it checks for the presence of an ExternalObjectLayout. If present, our previous Customization is applied; if not, the default settings are used. The following is the code using ExternalObjectLayout:

```cpp
void FDetailPropertyRow::GenerateChildrenForPropertyNode( TSharedPtr<FPropertyNode>& RootPropertyNode, FDetailNodeList& OutChildren )
{
	// Children should be disabled if we are disabled
	TAttribute<bool> ParentEnabledState = TAttribute<bool>::CreateSP(this, &FDetailPropertyRow::GetEnabledState);

	if( PropertyTypeLayoutBuilder.IsValid() && bShowCustomPropertyChildren )
	{
		const TArray< FDetailLayoutCustomization >& ChildRows = PropertyTypeLayoutBuilder->GetChildCustomizations();

		for( int32 ChildIndex = 0; ChildIndex < ChildRows.Num(); ++ChildIndex )
		{
			TSharedRef<FDetailItemNode> ChildNodeItem = MakeShared<FDetailItemNode>(ChildRows[ChildIndex], ParentCategory.Pin().ToSharedRef(), ParentEnabledState);
			ChildNodeItem->Initialize();
			OutChildren.Add( ChildNodeItem );
		}
	}
	else if (ExternalObjectLayout.IsValid() && ExternalObjectLayout->DetailLayout->HasDetails())
	{
		OutChildren.Append(ExternalObjectLayout->DetailLayout->GetAllRootTreeNodes());
		//Custom Panel
	}
	else if ((bShowCustomPropertyChildren || !CustomPropertyWidget.IsValid()) && RootPropertyNode->GetNumChildNodes() > 0)
{
	//Normal Default Child Creation
}
```

An example used in the source code is the details panel for the Binding Property on the Bind Actor in LevelSequence.

If we remove some code

```cpp
USTRUCT()
struct FMovieSceneBindingPropertyInfo
{
	GENERATED_BODY()

	// Locator for the entry
	UPROPERTY(EditAnywhere, Category = "Default", meta=(AllowedLocators="Actor", DisplayName="Actor"))
	FUniversalObjectLocator Locator;

	// Flags for how to resolve the locator
	UPROPERTY()
	ELocatorResolveFlags ResolveFlags = ELocatorResolveFlags::None;

	UPROPERTY(Instanced, VisibleAnywhere, Category = "Default", meta=(EditInline, AllowEditInlineCustomization, DisplayName="Custom Binding Type"))
	UMovieSceneCustomBinding* CustomBinding = nullptr;
};

//Hack the code yourself
UObject* obj = UInsiderLibrary::FindObjectWithNameSmart(TEXT("MovieSceneBindingPropertyInfo"));
UScriptStruct* ss = Cast<UScriptStruct>(obj);
FProperty* prop = ss->FindPropertyByName(TEXT("CustomBinding"));
prop->RemoveMetaData(TEXT("AllowEditInlineCustomization"));
```

The effect will change from left to right:

![Untitled](AllowEditInlineCustomization/Untitled%201.png)

Registration methods also differ:

```cpp
void ULevelSequenceEditorSubsystem::AddBindingDetailCustomizations(TSharedRef<IDetailsView> DetailsView, TSharedPtr<ISequencer> ActiveSequencer, FGuid BindingGuid)
{
	// TODO: Do we want to create a generalized way for folks to add instanced property layouts for other custom binding types so they can have access to sequencer context?
	if (ActiveSequencer.IsValid())
	{
		UMovieSceneSequence* Sequence = ActiveSequencer->GetFocusedMovieSceneSequence();
		UMovieScene* MovieScene = Sequence ? Sequence->GetMovieScene() : nullptr;
		if (MovieScene)
		{
			FPropertyEditorModule& PropertyEditor = FModuleManager::Get().LoadModuleChecked<FPropertyEditorModule>(TEXT("PropertyEditor"));
			DetailsView->RegisterInstancedCustomPropertyTypeLayout(FMovieSceneBindingPropertyInfo::StaticStruct()->GetFName(), FOnGetPropertyTypeCustomizationInstance::CreateLambda([](TWeakPtr<ISequencer> InSequencer, UMovieScene* InMovieScene, FGuid InBindingGuid, ULevelSequenceEditorSubsystem* LevelSequenceEditorSubsystem)
				{
					return MakeShared<FMovieSceneBindingPropertyInfoDetailCustomization>(InSequencer, InMovieScene, InBindingGuid, LevelSequenceEditorSubsystem);
				}, ActiveSequencer.ToWeakPtr(), MovieScene, BindingGuid, this));

			DetailsView->RegisterInstancedCustomPropertyLayout(UMovieSceneSpawnableActorBinding::StaticClass(), FOnGetDetailCustomizationInstance::CreateStatic(&FMovieSceneSpawnableActorBindingBaseCustomization::MakeInstance, ActiveSequencer.ToWeakPtr(), MovieScene, BindingGuid));
		}
	}
}
```