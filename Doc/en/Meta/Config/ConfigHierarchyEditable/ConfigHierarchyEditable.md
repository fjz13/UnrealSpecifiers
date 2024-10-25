# ConfigHierarchyEditable

- **Function description:** Allows an attribute to be configured at various levels within the Config system.
- **Use location:** UPROPERTY
- **Engine module:** Config
- **Metadata type:** bool
- **Commonly used:** ★★★

Enables a property to be configured at different levels of the Config system.

- What is meant by the "levels of Config" refers to the hierarchy where Base, ProjectDefault, EnginePlatform, and ProjectPlatform are progressively overridden by higher-priority settings. For more information on this topic, you can refer to other detailed articles about config settings available online.
- Usually, properties with Config have their configuration values specified only in the config file indicated by the config specifier on UCLASS. However, if a property is marked with ConfigHierarchyEditable, it permits different configurations at each level. This type of property typically requires different values based on platform-specific needs, such as platform-related performance parameters.

## Test Example:

```cpp
UCLASS(config = InsiderSettings, defaultconfig)
class UMyProperty_InsiderSettings :public UDeveloperSettings
{
	GENERATED_BODY()
public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = ConfigHierarchy)
	FString MyString;

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = ConfigHierarchy, meta = (ConfigHierarchyEditable))
	FString MyString_ConfigHierarchyEditable;
};
```

## Test Results:

You can observe that a hierarchy button has appeared on the right side of the MyString_ConfigHierarchyEditable input field, which can be used to open a dedicated ConfigEditor, facilitating the configuration of different values across various platforms and levels.

![Untitled](Untitled.png)

## Source Code Example:

```cpp

UCLASS(config = Game, defaultconfig)
class COMMONUI_API UCommonUISettings : public UObject
{
		/** The set of traits defined per-platform (e.g., the default input mode, whether or not you can exit the application, etc...) */
		UPROPERTY(config, EditAnywhere, Category = "Visibility", meta=(Categories="Platform.Trait", ConfigHierarchyEditable))
		TArray<FGameplayTag> PlatformTraits;
}
```

## Principle:

The logic is straightforward: when generating the ValueWidget in the details panel, an additional button for hierarchical configuration is created based on the ConfigHierarchyEditable setting.

```cpp
void FDetailPropertyRow::MakeValueWidget( FDetailWidgetRow& Row, const TSharedPtr<FDetailWidgetRow> InCustomRow, bool bAddWidgetDecoration ) const
{
	// Don't add config hierarchy to container children, can't edit child properties at the hiearchy's per file level
	TSharedPtr<IPropertyHandle> ParentHandle = PropertyHandle->GetParentHandle();
	bool bIsChildProperty = ParentHandle && (ParentHandle->AsArray() || ParentHandle->AsMap() || ParentHandle->AsSet());

	if (!bIsChildProperty && PropertyHandle->HasMetaData(TEXT("ConfigHierarchyEditable")))
	{
		ValueWidget->AddSlot()
		.AutoWidth()
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Left)
		.Padding(4.0f, 0.0f, 4.0f, 0.0f)
		[
			PropertyCustomizationHelpers::MakeEditConfigHierarchyButton(FSimpleDelegate::CreateSP(PropertyEditor.ToSharedRef(), &FPropertyEditor::EditConfigHierarchy))
		];
	}
}
```