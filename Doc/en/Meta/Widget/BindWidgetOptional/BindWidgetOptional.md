# BindWidgetOptional

- **Function Description:** Specifies that a Widget attribute in a C++ class can optionally be bound to a corresponding control in UMG with the same name, or it may remain unbound.
- **Usage Location:** UPROPERTY
- **Engine Module:** Widget Property
- **Metadata Type:** bool
- **Restriction Type:** Attributes of UWidget subclasses
- **Related Items:** [BindWidget](../BindWidget/BindWidget.md)
- **Commonality:** ★★★

Specifies that the Widget attribute in the C++ class can optionally be bound to a control with the same name in UMG, or it can be left unbound.

Its function is similar to BindWidget, with the distinction being:

- As the name implies, BindWidgetOptional is optional, meaning that if the control is not defined in UMG, the compilation will not result in an error. However, a warning will be issued regarding the missing control.
-
- The difference compared to an attribute of a control without BindWidgetOptional is that the former will not produce an error when a control with the same name is defined in UMG, whereas the latter will trigger an error due to a name conflict.

There are two ways to express BindWidgetOptional:
BindWidgetOptional can be considered a combined version of BindWidget and OptionalWidget.

```cpp
UCLASS(BlueprintType)
class INSIDER_API UMyProperty_BindWidget :public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTextBlock* MyTextBlock_SameName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional))
	class UTextBlock* MyTextBlock_Optional1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, OptionalWidget))
	class UTextBlock* MyTextBlock_Optional2;
};
```

## Test Results:

![Untitled](Untitled.png)

## Principle:

```cpp

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