# DisallowedStructs

- **Function Description:** Exclusive to the SmartObject module, this is used to exclude a specific class and its subclasses from the class selector.
- **Usage Location:** UPROPERTY
- **Engine Module:** TypePicker
- **Metadata Type:** string="abc"
- **Commonality:** ★

Applied solely within the SmartObject module to exclude a particular class and its subclasses from the class selector.

## Source Code:

```cpp
UPROPERTY(EditDefaultsOnly, Category = "SmartObject", meta=(DisallowedStructs="/Script/SmartObjectsModule.SmartObjectSlotAnnotation"))
TArray<FSmartObjectDefinitionDataProxy> DefinitionData;
```