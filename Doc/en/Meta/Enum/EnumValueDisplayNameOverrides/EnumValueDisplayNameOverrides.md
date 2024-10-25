# EnumValueDisplayNameOverrides

- **Function Description:** Modify the display names of enumeration property values
- **Usage Location:** UPROPERTY
- **Engine Module:** Enum Property
- **Metadata Type:** string="abc"
- **Associated Items:** [ValidEnumValues](../ValidEnumValues/ValidEnumValues.md)
- **Commonality:** ★★

Rename the enumeration values on the enumeration attributes. You can change multiple names. Simply list them in the format of "A=B; C=D". The collected information is in the TMap<FName, FText> mapping format, so both the original enumeration value names and their corresponding new display names must be provided.

## Test Code:

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

UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EnumValueDisplayNameOverrides = "First=Cat;Second=Dog"))
EMyPropertyTestEnum MyEnumWithDisplayNameOverrides;
```

## Blueprint Effect:

It is evident that the display names for "First" and "Second" have been altered.

![Untitled](Untitled.png)

For the code implementation of the principle, please refer to the code on ValidEnumValues