# AllowEditInlineCustomization

功能描述: 允许EditInline的对象属性可以自定义属性细节面板来编辑该对象内的数据。
使用位置: UPROPERTY
Feature: Editor
元数据类型: string="abc"
Status: Done
Parent item: EditInline (EditInline.md)
常用程度: 1

允许EditInline的对象属性可以自定义属性细节面板来编辑该对象内的数据。

测试代码：

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

效果：

![Untitled](AllowEditInlineCustomization/Untitled.png)

要做到自定义EditInline的效果，采用自定义的IPropertyTypeCustomization和RegisterCustomPropertyTypeLayout也能做到。区别是，正如上面代码里的UMyCustomAsset里面有两个同类型的UMyCommonObject*对象，假如用IPropertyTypeCustomization的方式，就会导致两个变量都变成自定义的UI模式。而用AllowEditInlineCustomization就可以使得其中你想要的那个变成自定义方式，而其他的不做改变。

在用法上，AllowEditInlineCustomization必须配合自定义的FAssetEditorToolkit来自己定义一个DetailView（而不是只自定义某个类型在引擎统一的DetailView的显示），然后再自定义IDetailCustomization来提供具体的Widget，最后用RegisterInstancedCustomPropertyLayout来关联起来。

```cpp
DetailsView->RegisterInstancedCustomPropertyLayout(UMyCommonObject::StaticClass(),FOnGetDetailCustomizationInstance::CreateStatic(&FMyCommonObjectDetailsCustomization::MakeInstance));
```

（这部分代码可参考MyCustomAsset的相关实现）

## 源码：

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

作用的原理是在创建FDetailPropertyRow的时候，即一个属性的在细节面板里的一行，如果有AllowEditInlineCustomization，就会创建ExternalObjectLayout ，之后在FDetailPropertyRow的创建孩子的时候，就会判断是否有ExternalObjectLayout，如果有就可以应用上我们之前的Customization，如果没有就会应用默认的设置。如下是使用ExternalObjectLayout的代码：

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
		//自定义的面板
	}
	else if ((bShowCustomPropertyChildren || !CustomPropertyWidget.IsValid()) && RootPropertyNode->GetNumChildNodes() > 0)
{
	//正常的默认创建孩子
}
```

源码里使用的一个例子是LevelSequence上Bind Actor上的Binding Property的细节面板。

假如我们采用一些代码去掉

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

//自己Hack 代码
UObject* obj = UInsiderLibrary::FindObjectWithNameSmart(TEXT("MovieSceneBindingPropertyInfo"));
UScriptStruct* ss = Cast<UScriptStruct>(obj);
FProperty* prop = ss->FindPropertyByName(TEXT("CustomBinding"));
prop->RemoveMetaData(TEXT("AllowEditInlineCustomization"));
```

效果就会从左变到右边：

![Untitled](AllowEditInlineCustomization/Untitled%201.png)

注册的方式也不同：

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