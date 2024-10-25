# ValidEnumValues

- **Function description:** Specifies the optional enumeration values for an enumeration attribute
- **Use location:** UPROPERTY
- **Engine module:** Enum Property
- **Metadata type:** strings = "a, b, c"
- **Restriction type:** Enumeration attribute value
- **Related items:** [InvalidEnumValues](../InvalidEnumValues.md), [GetRestrictedEnumValues](../GetRestrictedEnumValues.md), [EnumValueDisplayNameOverrides](../EnumValueDisplayNameOverrides/EnumValueDisplayNameOverrides.md), [Enum](../Enum.md)
- **Frequency:** ★★★

ValidEnumValues specifies the optional enumeration value options on enumeration attribute values. By default, enumeration properties in the details panel can be set to all enumeration values, but we can restrict the display to only these values using ValidEnumValues.

There are three ways to write enumeration attributes, namely enum class, TEnumAsByte and FString superimposed on enum meta. These three ways of writing will be regarded as an enumeration attribute and then try to generate a combo list to allow users to select attribute values.

## Sample Code:

```cpp
UENUM(BlueprintType)
enum class EMyPropertyTestEnum : uint8
{
	First,
	Second,
	Third,
	Forth,
	Fifth,
};

UENUM(BlueprintType)
namespace EMyPropertyTestEnum2
{
	enum Type : int
	{
		First,
		Second,
		Third,
		Forth,
		Fifth,
	};
}

UCLASS(BlueprintType)
class INSIDER_API UMyProperty_Enum :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMyPropertyTestEnum MyEnum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ValidEnumValues = "First,Second,Third"))
	EMyPropertyTestEnum MyEnumWithValid;	// Type 1

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ValidEnumValues = "First,Second,Third"))
	TEnumAsByte<EMyPropertyTestEnum2::Type> MyAnotherEnumWithValid;	//Type 2

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (enum = "EMyPropertyTestEnum"))
	FString MyStringWithEnum;	//Type 3

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (InvalidEnumValues = "First,Second,Third"))
	EMyPropertyTestEnum MyEnumWithInvalid = EMyPropertyTestEnum::Forth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (GetRestrictedEnumValues = "MyGetRestrictedEnumValues"))
	EMyPropertyTestEnum MyEnumWithRestricted;

public:
	UFUNCTION(BlueprintInternalUseOnly)
	TArray<FString> MyGetRestrictedEnumValues() const{	return TArray<FString>{"Second","Third"};}
};
```

## Blueprint Effect:

It can be observed that, by default, the enumeration attribute displays all five enumeration values, but the optional lists for the other three enumeration attributes are restricted to three values.

![Untitled](Untitled.png)

## Principle:

The following code snippet,

```cpp
bool FPropertyHandleBase::GeneratePossibleValues(TArray< TSharedPtr<FString> >& OutOptionStrings, TArray< FText >& OutToolTips, TArray<bool>& OutRestrictedItems)
{
	TArray<UObject*> OuterObjects;
	GetOuterObjects(OuterObjects);

	const TArray<FName> ValidEnumValues = PropertyEditorHelpers::GetValidEnumsFromPropertyOverride(Property, Enum);
	const TArray<FName> InvalidEnumValues = PropertyEditorHelpers::GetInvalidEnumsFromPropertyOverride(Property, Enum);
	const TArray<FName> RestrictedEnumValues = PropertyEditorHelpers::GetRestrictedEnumsFromPropertyOverride(OuterObjects, Property, Enum);

	const TMap<FName, FText> EnumValueDisplayNameOverrides = PropertyEditorHelpers::GetEnumValueDisplayNamesFromPropertyOverride(Property, Enum);

	//NumEnums() - 1, because the last item in an enum is the _MAX item
	for( int32 EnumIndex = 0; EnumIndex < Enum->NumEnums() - 1; ++EnumIndex )
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

		if (!bShouldBeHidden)
		{
			bShouldBeHidden = IsHidden(Enum->GetNameStringByIndex(EnumIndex));
		}

		if( !bShouldBeHidden )
		{
			// See if we specified an alternate name for this value using metadata
			FString EnumName = Enum->GetNameStringByIndex(EnumIndex);
			FString EnumDisplayName = EnumValueDisplayNameOverrides.FindRef(Enum->GetNameByIndex(EnumIndex)).ToString();
			if (EnumDisplayName.IsEmpty())
			{
				EnumDisplayName = Enum->GetDisplayNameTextByIndex(EnumIndex).ToString();
			}

			FText RestrictionTooltip;
			const bool bIsRestricted = GenerateRestrictionToolTip(EnumName, RestrictionTooltip) || RestrictedEnumValues.Contains(Enum->GetNameByIndex(EnumIndex));
			OutRestrictedItems.Add(bIsRestricted);

			if (EnumDisplayName.Len() == 0)
			{
				EnumDisplayName = MoveTemp(EnumName);
			}
			else
			{
				bUsesAlternateDisplayValues = true;
			}

			TSharedPtr< FString > EnumStr(new FString(EnumDisplayName));
			OutOptionStrings.Add(EnumStr);

			FText EnumValueToolTip = bIsRestricted ? RestrictionTooltip : Enum->GetToolTipTextByIndex(EnumIndex);
			OutToolTips.Add(MoveTemp(EnumValueToolTip));
		}
		else
		{
			OutToolTips.Add(FText());
		}
	}
}
```