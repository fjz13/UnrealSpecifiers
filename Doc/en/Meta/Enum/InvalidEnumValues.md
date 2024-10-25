# InvalidEnumValues

- **Function Description:** Specifies the disallowed enumeration values for an enumeration attribute, used to exclude certain options
- **Usage Location:** UPROPERTY
- **Engine Module:** Enum Property
- **Metadata Type:** strings = "a, b, c"
- **Restriction Type:** Enumeration Attribute Value
- **Associated Items:** [ValidEnumValues](ValidEnumValues/ValidEnumValues.md)
- **Commonly Used:** ★★★

If InvalidEnumValues and ValidEnumValues are specified at the same time, and the values therein overlap, InvalidEnumValues shall prevail: this enumeration value is illegal.