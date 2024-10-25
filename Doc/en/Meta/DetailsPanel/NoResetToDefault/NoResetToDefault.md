# NoResetToDefault

- **Function Description:** Disables and hides the "Reset" feature for properties in the details panel.
- **Usage Location:** UPROPERTY
- **Engine Module:** DetailsPanel
- **Metadata Type:** bool
- **Commonly Used:** ★★★

Disables and hides the "Reset" feature for properties in the details panel.

## Test Code:

```cpp
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category=ResetToDefaultTest)
	int32 MyInt_Default = 123;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category=ResetToDefaultTest, meta = (NoResetToDefault))
	int32 MyInt_NoResetToDefault = 123;
```

## Test Effects:

You can observe that by default, after changing the value of a property, a reset button appears on the right, allowing the property to be reset to its default value. The purpose of NoResetToDefault is to eliminate this functionality.

![ResetToDefaultTest](ResetToDefaultTest.gif)

## Principle:

The editor checks for this metadata; if it is not present, it creates an SResetToDefaultPropertyEditor.

```cpp
bool SSingleProperty::GeneratePropertyCustomization()
{
		if (!PropertyEditor->GetPropertyHandle()->HasMetaData(TEXT("NoResetToDefault")) && !bShouldHideResetToDefault)
		{
			HorizontalBox->AddSlot()
			.Padding( 2.0f )
			.AutoWidth()
			.VAlign( VAlign_Center )
			[
				SNew( SResetToDefaultPropertyEditor,  PropertyEditor->GetPropertyHandle() )
			];
		}
}
```