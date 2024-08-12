# CustomizeProperty

Description: 使用在FAnimNode的成员属性上，告诉编辑器不要为它生成默认Details面板控件，后续会在DetailsCustomization里自定义创建相应的编辑控件。
Usage: UPROPERTY
Feature: Editor
Group: AnimationGraph
Type: bool
LimitedType: FAnimNode里的属性
Status: Done

使用在FAnimNode的成员属性上，告诉编辑器不要为它生成默认Details面板控件，后续会在DetailsCustomization里自定义创建相应的编辑控件。

和AllowEditInlineCustomization的作用有点像，都只是做个标记提示编辑器会在别的地方进行自定义，不用为它生成默认Details面板控件。

## 源码中例子：

在源码里能见到挺多例子，常见的就是在AnimBP中的节点上的属性，其在细节面板需要专门的定制化编辑。最常见的例子是Slot这个节点，其SlotName只是个FString类型，但是在细节面板里显示的却是个ComboString。这是因为它标上了CustomizeProperty，告知默认的动画节点细节面板生成器*（FAnimGraphNodeDetails）先不要为这个属性创建编辑控件，之后会在自己的定制化（FAnimGraphNodeSlotDetails）里为SlotName再创建自定义UI。

```cpp
struct FAnimNode_Slot : public FAnimNode_Base
{
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Settings, meta=(CustomizeProperty))
	FName SlotName;
}

void FPersonaModule::CustomizeBlueprintEditorDetails(const TSharedRef<class IDetailsView>& InDetailsView, FOnInvokeTab InOnInvokeTab)
{
	InDetailsView->RegisterInstancedCustomPropertyLayout(UAnimGraphNode_Slot::StaticClass(),
		FOnGetDetailCustomizationInstance::CreateStatic(&FAnimGraphNodeSlotDetails::MakeInstance, InOnInvokeTab));

	InDetailsView->SetExtensionHandler(MakeShared<FAnimGraphNodeBindingExtension>());
}

```

## 测试代码：

```cpp
USTRUCT(BlueprintInternalUseOnly)
struct INSIDER_API FAnimNode_MyCustomProperty : public FAnimNode_Base
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CustomProperty)
	FString MyString_Default;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CustomProperty, meta = (CustomizeProperty))
	FString MyString_CustomizeProperty;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CustomProperty, meta = (CustomizeProperty))
	FString MyString_CustomizeProperty_Other;
};

UCLASS()
class INSIDEREDITOR_API UAnimGraphNode_MyCustomProperty : public UAnimGraphNode_Base
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, Category = Settings)
	FAnimNode_MyCustomProperty Node;
};

//再创建一个定制化，生成自定义UI
void FMyAnimNode_MyCustomPropertyCustomization::CustomizeDetails(class IDetailLayoutBuilder& DetailBuilder)
{
	TSharedPtr<IPropertyHandle> PropertyHandle = DetailBuilder.GetProperty(TEXT("Node.MyString_CustomProperty"));
	
	//Just for test
	ComboListItems.Empty();
	ComboListItems.Add(MakeShareable(new FString(TEXT("First"))));
	ComboListItems.Add(MakeShareable(new FString(TEXT("Second"))));
	ComboListItems.Add(MakeShareable(new FString(TEXT("Third"))));
	const TSharedPtr<FString> ComboBoxSelectedItem = ComboListItems[0];

	IDetailCategoryBuilder& Group = DetailBuilder.EditCategory(TEXT("CustomProperty"));
	Group.AddCustomRow(INVTEXT("CustomProperty"))
		.NameContent()
		[
			PropertyHandle->CreatePropertyNameWidget()
		]
		.ValueContent()
		[
			SNew(STextComboBox)
				.OptionsSource(&ComboListItems)
				.InitiallySelectedItem(ComboBoxSelectedItem)
				.ContentPadding(2.f)
				.ToolTipText(FText::FromString(*ComboBoxSelectedItem))
		];
}

//注册定制化
PropertyModule.RegisterCustomClassLayout(TEXT("AnimGraphNode_MyCustomProperty"), FOnGetDetailCustomizationInstance::CreateStatic(&FMyAnimNode_MyCustomPropertyCustomization::MakeInstance));

```

## 测试效果：

SlotName的效果如右侧所示。

我们自己模仿的例子可见MyString_Default依然只是个默认String，而MyString_CustomizeProperty则为它创建了自定义UI。

作为对比，MyString_CustomizeProperty_Other我们标上了CustomizeProperty但是没有为它创建UI，则没有显示出来，说明引擎默认的机制因此就把它的UI默认创建流程给跳过了。

![Untitled](CustomizeProperty/Untitled.png)

## 原理：

CustomizeProperty其实会会改变Pin的bPropertyIsCustomized 属性（GetRecordDefaults中体现），然后在创建流程的过程中不创建默认的widget，这个可见CustomizeDetails中的bPropertyIsCustomized判断得知。

```cpp
void FAnimBlueprintNodeOptionalPinManager::GetRecordDefaults(FProperty* TestProperty, FOptionalPinFromProperty& Record) const
{
	const UAnimationGraphSchema* Schema = GetDefault<UAnimationGraphSchema>();

	// Determine if this is a pose or array of poses
	FArrayProperty* ArrayProp = CastField<FArrayProperty>(TestProperty);
	FStructProperty* StructProp = CastField<FStructProperty>(ArrayProp ? ArrayProp->Inner : TestProperty);
	const bool bIsPoseInput = (StructProp  && StructProp->Struct->IsChildOf(FPoseLinkBase::StaticStruct()));

	//@TODO: Error if they specified two or more of these flags
	const bool bAlwaysShow = TestProperty->HasMetaData(Schema->NAME_AlwaysAsPin) || bIsPoseInput;
	const bool bOptional_ShowByDefault = TestProperty->HasMetaData(Schema->NAME_PinShownByDefault);
	const bool bOptional_HideByDefault = TestProperty->HasMetaData(Schema->NAME_PinHiddenByDefault);
	const bool bNeverShow = TestProperty->HasMetaData(Schema->NAME_NeverAsPin);
	const bool bPropertyIsCustomized = TestProperty->HasMetaData(Schema->NAME_CustomizeProperty);
	const bool bCanTreatPropertyAsOptional = CanTreatPropertyAsOptional(TestProperty);

	Record.bCanToggleVisibility = bCanTreatPropertyAsOptional && (bOptional_ShowByDefault || bOptional_HideByDefault);
	Record.bShowPin = bAlwaysShow || bOptional_ShowByDefault;
	Record.bPropertyIsCustomized = bPropertyIsCustomized;
}

//这个是在AnimBP中选中一个节点然后在右侧细节面板中的属性
void FAnimGraphNodeDetails::CustomizeDetails(class IDetailLayoutBuilder& DetailBuilder)
{
		// sometimes because of order of customization
		// this gets called first for the node you'd like to customize
		// then the above statement won't work
		// so you can mark certain property to have meta data "CustomizeProperty"
		// which will trigger below statement
		if (OptionalPin.bPropertyIsCustomized)
		{
						continue;
		}
		TSharedRef<SWidget> InternalCustomWidget = CreatePropertyWidget(TargetProperty, TargetPropertyHandle.ToSharedRef(), AnimGraphNode->GetClass());
}
```