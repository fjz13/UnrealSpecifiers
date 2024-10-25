# ShowNormalize

- **Function Description:** Adds a normalization button for FVector variables in the details panel.
- **Usage Location:** UPROPERTY
- **Engine Module:** Numeric Property
- **Metadata Type:** bool
- **Restricted Type:** FVector
- **Commonality:** ★★★

Enables a normalization button for FVector variables in the details panel.

## Test Code:

```cpp
	UPROPERTY(EditAnywhere, Category = VectorTest)
	FVector MyVector_Default;

	UPROPERTY(EditAnywhere, Category = VectorTest, meta = (AllowPreserveRatio))
	FVector MyVector_AllowPreserveRatio;

	UPROPERTY(EditAnywhere, Category = VectorTest, meta = (ShowNormalize))
	FVector MyVector_ShowNormalize;
```

## Test Results:

The button to the right of MyVector_ShowNormalize normalizes the value.

![AllowPreserveRatio](AllowPreserveRatio.gif)

## Principle:

What actually happens is that during UI customization, the presence of ShowNormalize triggers the creation of a dedicated UI element.

```cpp
if (StructPropertyHandle->HasMetaData("ShowNormalize") && MathStructCustomization::IsFloatVector(StructPropertyHandle))
{
	HorizontalBox->AddSlot()
		.AutoWidth()
		.MaxWidth(18.0f)
		.VAlign(VAlign_Center)
		[
			// Add a button to scale the vector uniformly to achieve a unit vector
			SNew(SButton)
				.OnClicked(this, &FMathStructCustomization::OnNormalizeClicked, StructWeakHandlePtr)
				.ButtonStyle(FAppStyle::Get(), "NoBorder")
				.ToolTipText(LOCTEXT("NormalizeToolTip", "When clicked, if the vector is large enough, it scales the vector uniformly to achieve a unit vector (vector with a length of 1)"))
				[
					SNew(SImage)
						.ColorAndOpacity(FSlateColor::UseForeground())
						.Image(FAppStyle::GetBrush(TEXT("Icons.Normalize")))
				]
		];
}
```