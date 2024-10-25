# Hidden

- **Function Description:** Hide a specific value within a UENUM
- **Usage Location:** UENUM::UMETA
- **Engine Module:** Enum Property
- **Metadata Type:** bool
- **Restriction Type:** UENUM Value
- **Commonliness:** ★★★★★

Hide a specific value in UENUM.

## Test Code:

```cpp

UENUM(Blueprintable,BlueprintType)
enum class EMyEnum_Spacer_Hidden :uint8
{
	MyNormal,
	MySpacer UMETA(Spacer),
	MyHidden UMETA(Hidden),
};

UCLASS(BlueprintType)
class INSIDER_API UMyEnum_Test :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	EMyEnum_Spacer_Hidden MyEnum_Spacer_Hidden;
};
```

## Test Effects:

![Untitled](5b4de771-be09-4342-8955-dc0f824ef97d.png)

However, when accessed in Blueprint:

![Untitled](Untitled.png)

## Principle:

In the attribute details panel, when generating the possible values of an enumeration, the Hidden and Spacer options are evaluated to determine what to hide.

Yet, in elements like SEnumComboBox and SGraphPinEnum that are displayed within Blueprints, only the Hidden option is considered, and Spacer is not (perhaps overlooked?) evaluated, thus MySpacer will still be visible.

```cpp
bool FPropertyHandleBase::GeneratePossibleValues(TArray<FString>& OutOptionStrings, TArray< FText >& OutToolTips, TArray<bool>& OutRestrictedItems, TArray<FText>* OutDisplayNames)
{
		// Ignore hidden enums
	bool bShouldBeHidden = Enum->HasMetaData(TEXT("Hidden"), EnumIndex ) || Enum->HasMetaData(TEXT("Spacer"), EnumIndex );
	if (!bShouldBeHidden)
	{
		if(ValidEnumValues.Num() > 0)
		{
			bShouldBeHidden = !ValidEnumValues.Contains(Enum->GetNameByIndex(EnumIndex));
		}
		// If both are specified, InvalidEnumValues takes precedence
		else if(InvalidEnumValues.Num() > 0)
		{
			bShouldBeHidden = InvalidEnumValues.Contains(Enum->GetNameByIndex(EnumIndex));
		}
	}
}

void SEnumComboBox::Construct(const FArguments& InArgs, const UEnum* InEnum)
{
		if (Enum->HasMetaData(TEXT("Hidden"), Index) == false)
		{
			VisibleEnums.Emplace(Index, Enum->GetValueByIndex(Index), Enum->GetDisplayNameTextByIndex(Index), Enum->GetToolTipTextByIndex(Index));
		}
}

void SGraphPinEnum::GenerateComboBoxIndexes( TArray< TSharedPtr<int32> >& OutComboBoxIndexes )
{
	// Ignore hidden enum values
	if( !EnumPtr->HasMetaData(TEXT("Hidden"), EnumIndex ) )
	{
		TSharedPtr<int32> EnumIdxPtr(new int32(EnumIndex));
		OutComboBoxIndexes.Add(EnumIdxPtr);
	}
}
```