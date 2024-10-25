# StructTypeConst

- **Function Description:** Specifies that the type of the FInstancedStruct attribute cannot be selected within the editor.
- **Usage Location:** UPROPERTY
- **Engine Module:** TypePicker
- **Metadata Type:** bool
- **Restricted Type:** FInstancedStruct
- **Associated Item:** [BaseStruct](BaseStruct/BaseStruct.md)
- **Commonality:** ★

The type specified for the FInstancedStruct attribute cannot be selected in the editor.

Its use is often for subsequent initialization by the user within the code.

## Principle:

If this attribute is marked, the editing control is disabled.

```cpp
void FInstancedStructDetails::CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
		static const FName NAME_StructTypeConst = "StructTypeConst";
		const bool bEnableStructSelection = !StructProperty->HasMetaData(NAME_StructTypeConst);


			.IsEnabled(bEnableStructSelection)

}
```