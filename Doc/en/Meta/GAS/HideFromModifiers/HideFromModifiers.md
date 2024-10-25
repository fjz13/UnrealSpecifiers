# HideFromModifiers

- **Function Description:** Specifies that a particular attribute within an AttributeSet should not be included in the Attribute selection for Modifiers within a GameplayEffect.
- **Usage Location:** UPROPERTY
- **Engine Module:** GAS
- **Metadata Type:** bool
- **Restriction Type:** Attributes within UAttributeSet
- **Related Items:** [HideInDetailsView](../HideInDetailsView/HideInDetailsView.md)
- **Commonality:** ★★★

Specifies that a particular attribute within an AttributeSet should not be included in the Attribute selection for Modifiers within a GameplayEffect.

## Test Code:

```cpp
UCLASS()
class UMyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core")
	float HP = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core", meta = (HideInDetailsView))
	float HP_HideInDetailsView = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core", meta = (HideFromModifiers))
	float HP_HideFromModifiers = 100.f;
};
UCLASS()
class UMyAttributeSetTest : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GAS")
	FGameplayAttribute MyAttribute;
};
```

## Test Results:

Create a GameplayEffect in the Blueprint and observe the Attribute selection within its Modifiers.

Notice that HP_HideFromModifiers can appear in the standard FGameplayAttribute tab, but it will not appear in the Attribute selection tab under Modifiers. This is the intended effect here.

![Untitled](Untitled.png)

## Principle:

In the FGameplayModifierInfo class, there is a FilterMetaTag metadata on the Attribute property. The value within this metadata is retrieved and ultimately passed to GetAllAttributeProperties as FilterMetaStr for filtering purposes. Hence, an attribute marked with HideFromModifiers will not be displayed.

```cpp
USTRUCT(BlueprintType)
struct GAMEPLAYABILITIES_API FGameplayModifierInfo
{
	GENERATED_USTRUCT_BODY()

	/** The Attribute we modify or the GE we modify modifies. */
	UPROPERTY(EditDefaultsOnly, Category=GameplayModifier, meta=(FilterMetaTag="HideFromModifiers"))
	FGameplayAttribute Attribute;
};

void FAttributePropertyDetails::CustomizeHeader( TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils )
{
		const FString& FilterMetaStr = StructPropertyHandle->GetProperty()->GetMetaData(TEXT("FilterMetaTag"));
	SNew(SGameplayAttributeWidget)
	.OnAttributeChanged(this, &FAttributePropertyDetails::OnAttributeChanged)
	.DefaultProperty(PropertyValue)
	.FilterMetaData(FilterMetaStr)
}
void FGameplayAttribute::GetAllAttributeProperties(TArray<FProperty*>& OutProperties, FString FilterMetaStr, bool UseEditorOnlyData)
{}
```