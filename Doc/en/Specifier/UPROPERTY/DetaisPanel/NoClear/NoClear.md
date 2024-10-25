# NoClear

- **Function Description:** Specifies that the Clear button should not appear in the editing options for this attribute, and setting it to null is not permitted.

- **Metadata Type:** bool
- **Engine Module:** DetailsPanel, Editor
- **Restriction Type:** Reference type
- **Action Mechanism:** Include [CPF_NoClear](../../../../Flags/EPropertyFlags/CPF_NoClear.md) in PropertyFlags
- **Common Usage:** ★★★

The Clear button will not appear in the editing options for this property.

It prevents users from setting this Object reference to null within the editor panel. However, it can also be applied to other structures representing a reference type, such as FPrimaryAssetId, FInstancedStruct, FDataRegistryType, etc.

## Sample Code:

```cpp
UPROPERTY(EditAnywhere, Category = Object)
class UMyClass_Default* MyObject_Normal;
//PropertyFlags:	CPF_Edit | CPF_ZeroConstructor | CPF_NoClear | CPF_NoDestructor | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
UPROPERTY(EditAnywhere, NoClear, Category = Object)
class UMyClass_Default* MyObject_NoClear;

//Constructor Assignment:
MyObject_Normal = CreateDefaultSubobject<UMyClass_Default>("MyObject_Normal");
MyObject_NoClear = CreateDefaultSubobject<UMyClass_Default>("MyObject_NoClear");
```

## Example Effect:

![Untitled](Untitled.png)

## Principle:

CPF_NoClear is extensively utilized within the engine.

```cpp
	const bool bAllowClear = !StructPropertyHandle->GetMetaDataProperty()->HasAnyPropertyFlags(CPF_NoClear);

```