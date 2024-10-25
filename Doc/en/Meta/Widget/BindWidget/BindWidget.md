# BindWidget

- **Function Description:** Specifies that a Widget attribute in a C++ class must be bound to a corresponding control with the same name in UMG.
- **Usage Location:** UPROPERTY
- **Engine Module:** Widget Property
- **Metadata Type:** bool
- **Restriction Type:** Attributes of UUserWidget subclasses
- **Related Items:** [BindWidgetOptional](../BindWidgetOptional/BindWidgetOptional.md), [OptionalWidget](../OptionalWidget.md)
- **Commonality:** ★★★★★

Specifies that the Widget attribute in the C++ class must be bound to a control with the same name in UMG.

A common programming practice is to define a UUserWidget subclass in C++, and then inherit from this C++ class in UMG. This allows for the implementation of some logic in C++ while arranging controls in UMG. Often, there is a need to reference specific controls defined in UMG using attributes in C++.

- The usual approach in C++ is to use WidgetTree->FindWidget to search for a control by name. However, if there are dozens of controls defined in the class, this process can be very tedious.
- Therefore, a more convenient method is to define control properties with the same name in C++. This will automatically establish the association, and after the UMG blueprint object is created, the engine will automatically assign the C++ Widget property to the control with the same name.
- It is important to note that BindWidget serves only as an editing and compilation hint for the UMG editor, reminding you to ensure that the names are properly associated. For the property defined in C++, remember to also create a control with the same name in UMG. When creating or modifying a control name in UMG, if you know there is a corresponding property in C++ to bind to, no error will be reported. Otherwise, an error indicating a name conflict will be prompted.
- To summarize, BindWidget serves two purposes: First, it reminds you to create a corresponding control with the same name in UMG to avoid compilation errors. Second, it prevents errors in UMG when defining a control with the same name as a C++ property.
- The recommended practice is to explicitly add BindWidget to all properties you wish to bind with the same name, rather than relying on the ambiguous default automatic binding mechanism with the same name.

## Testing Code:

```cpp
UCLASS(BlueprintType)
class INSIDER_API UMyProperty_BindWidget :public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTextBlock* MyTextBlock_NotFound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTextBlock* MyTextBlock_SameName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* MyTextBlock_Bind;
};

void UMyProperty_BindWidget::RunTest()
{
	//Locating Widgets in C++: A Comprehensive Guide
	UTextBlock* bindWidget= WidgetTree->FindWidget(TEXT("MyTextBlock_Bind"));
	check(bindWidget==MyTextBlock_Bind);
}
```

## Test Outcomes:

The test involves defining a UUserWidget base class in C++ and then creating a blueprint subclass in UMG. The list of controls is shown in the figure below.

- For comparative verification, three controls are defined in both C++ and Blueprint, with some having the same name and others not. After creating the widget, these three attribute values are then inspected in C++ during debugging.
- It can be observed that both MyTextBlock_Bind and MyTextBlock_SameName are automatically associated with values. The logic for associating attribute values does not depend on whether BindWidget is marked. However, if the variable is checked in MyTextBlock_SameName, a name conflict error is reported. This is because checking the variable creates an attribute in the Blueprint, which conflicts with the one in C++. When the variable is not checked, MyTextBlock_SameName is essentially just an object under the WidgetTree. The editor can either prompt for a name conflict (first defined in C++, then in UMG) or choose not to prompt (the actual effect of BindWidget). However, if a variable named MyTextBlock_SameName is also created in the Blueprint, the conflict is inevitable. Without BindWidget, the engine will consider these as two separate and distinct properties (if you did not explicitly write BindWidget in C++, but the engine automatically adds it, this could lead to more inexplicable errors). Only by explicitly adding BindWidget will the engine know that a C++ property already exists, eliminating the need to create another Blueprint attribute (which would not appear in the BP panel).
- MyTextBlock_NotFound has no value, which is logical since we did not define the control in UMG. However, it is worth noting that if we attempt to define a control with this name in UMG, an error will be reported indicating that the name is already taken. This is normal, as it is similar to defining a member variable in a subclass of a C++ class; conflicts are not allowed. However, if we define MyTextBlock_Bind, no "name occupied" error will be reported because the engine knows that a property with the same name is intended to reference the control. This is the precise meaning of BindWidget, serving only as a hint. At this point, someone might ask how MyTextBlock_SameName was created in UMG without causing an error. The answer is to define it in UMG first, and then in C++, so no error will be reported.
- If MyTextBlock_Bind is not defined in UMG at the end, the UMG compiler will report an error stating that the control you want to bind cannot be found, reminding you that you intended to bind a widget but did not create it.

![Untitled](Untitled.png)

## Operational Principle:

The function used to determine whether a property is a BindWidget is IsBindWidgetProperty.

The operation used to determine whether to generate an error prompt when the control is renamed or compiled is in FinishCompilingClass. The general logic is to determine whether the control wants to be bound based on IsBindWidgetProperty and then generate a prompt based on the current situation.

The logic for automatically associating values due to the same name is in UWidgetBlueprintGeneratedClass::InitializeWidgetStatic. The logic essentially involves traversing the controls under WidgetTree, searching for them by name in C++, and automatically assigning values if found.

```cpp
void UWidgetBlueprintGeneratedClass::InitializeWidgetStatic()
{
	// Find property with the same name as the template and assign the new widget to it.
	if (FObjectPropertyBase** PropPtr = ObjectPropertiesMap.Find(Widget->GetFName()))
	{
		FObjectPropertyBase* Prop = *PropPtr;
		check(Prop);
		Prop->SetObjectPropertyValue_InContainer(UserWidget, Widget);
		UObject* Value = Prop->GetObjectPropertyValue_InContainer(UserWidget);
		check(Value == Widget);
	}

}

void FWidgetBlueprintCompilerContext::FinishCompilingClass(UClass* Class)
{
	// Check that all BindWidget properties are present and of the appropriate type
	for (TFObjectPropertyBase<UWidget*>* WidgetProperty : TFieldRange<TFObjectPropertyBase<UWidget*>>(ParentClass))
	{
		bool bIsOptional = false;

		if (FWidgetBlueprintEditorUtils::IsBindWidgetProperty(WidgetProperty, bIsOptional))
		{}
	}

}

bool FWidgetBlueprintEditorUtils::IsBindWidgetProperty(const FProperty* InProperty, bool& bIsOptional)
{
	if ( InProperty )
	{
		bool bIsBindWidget = InProperty->HasMetaData("BindWidget") || InProperty->HasMetaData("BindWidgetOptional");
		bIsOptional = InProperty->HasMetaData("BindWidgetOptional") || ( InProperty->HasMetaData("OptionalWidget") || InProperty->GetBoolMetaData("OptionalWidget") );

		return bIsBindWidget;
	}

	return false;
}
```