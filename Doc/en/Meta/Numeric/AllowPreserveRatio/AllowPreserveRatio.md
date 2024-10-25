# AllowPreserveRatio

- **Function Description:** Adds a ratio lock feature for the FVector attribute within the details panel.
- **Usage Location:** UPROPERTY
- **Engine Module:** Numeric Property
- **Metadata Type:** bool
- **Restricted Type:** FVector
- **Commonality:** ★★★

Adds a ratio lock to the FVector property in the details panel.

## Test Code:

```cpp
public:
	UPROPERTY(EditAnywhere, Category = VectorTest)
	FVector MyVector_Default;

	UPROPERTY(EditAnywhere, Category = VectorTest, meta = (AllowPreserveRatio))
	FVector MyVector_AllowPreserveRatio;

	UPROPERTY(EditAnywhere, Category = VectorTest, meta = (ShowNormalize))
	FVector MyVector_ShowNormalize;
```

## Test Results:

It is evident that the value of MyVector_AllowPreserveRatio maintains a fixed ratio after being locked.

![AllowPreserveRatio](AllowPreserveRatio.gif)

## Principle:

The mechanism involves detecting the AllowPreserveRatio during UI customization and creating a dedicated UI element for it.

```cpp
void FMathStructCustomization::MakeHeaderRow(TSharedRef<class IPropertyHandle>& StructPropertyHandle, FDetailWidgetRow& Row)
{
		if (StructPropertyHandle->HasMetaData("AllowPreserveRatio"))
		{
			if (!GConfig->GetBool(TEXT("SelectionDetails"), *(StructPropertyHandle->GetProperty()->GetName() + TEXT("_PreserveScaleRatio")), bPreserveScaleRatio, GEditorPerProjectIni))
			{
				bPreserveScaleRatio = true;
			}

			HorizontalBox->AddSlot()
			.AutoWidth()
			.MaxWidth(18.0f)
			.VAlign(VAlign_Center)
			[
				// Add a checkbox to toggle between preserving the ratio of x,y,z components of scale when a value is entered
				SNew(SCheckBox)
				.IsChecked(this, &FMathStructCustomization::IsPreserveScaleRatioChecked)
				.OnCheckStateChanged(this, &FMathStructCustomization::OnPreserveScaleRatioToggled, StructWeakHandlePtr)
				.Style(FAppStyle::Get(), "TransparentCheckBox")
				.ToolTipText(LOCTEXT("PreserveScaleToolTip", "When locked, scales uniformly based on the current xyz scale values so the object maintains its shape in each direction when scaled"))
				[
					SNew(SImage)
					.Image(this, &FMathStructCustomization::GetPreserveScaleRatioImage)
					.ColorAndOpacity(FSlateColor::UseForeground())
				]
			];
		}

}
```