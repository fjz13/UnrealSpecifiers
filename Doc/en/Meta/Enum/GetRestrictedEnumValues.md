# GetRestrictedEnumValues

- **Function Description:** Specifies a function to determine which enum options are disabled for an enum attribute value
- **Usage Location:** UPROPERTY
- **Engine Module:** Enum Property
- **Metadata Type:** string="abc"
- **Restriction Type:** TArray<FString> FuncName() const;
- **Associated Items:** [ValidEnumValues](ValidEnumValues/ValidEnumValues.md)
- **Commonality:** ★★★

The distinction between "Restricted" and "Invalid" lies in:

'Invalid' will hide the option value

'Restricted' will still display the option value, but it will appear grayed out and cannot be selected.

The specified function name must be a UFUNCTION, allowing the function to be located by name.