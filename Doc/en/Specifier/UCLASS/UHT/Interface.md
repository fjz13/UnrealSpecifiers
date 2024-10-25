# Interface

- **Function Description:** Indicates that this class is an interface.
- **Engine Module:** UHT
- **Metadata Type:** bool
- **Mechanism of Action:** Add [CLASS_Interface](../../../Flags/EClassFlags/CLASS_Interface.md) to ClassFlags
- **Usage Frequency:** 0

Indicates that this class is an interface.

This setting is only applied in NoExportTypes.h. Our self-defined UInterfaces do not require manual configuration.

This is automatically handled by UHT when generating the .generated.h file for UInterfaces.

## Source Code Example:

```cpp
UCLASS(abstract, noexport, intrinsic, interface, Config = Engine)
class UInterface : public UObject
{}
```

## Principle:

```cpp
bool FKismetEditorUtilities::IsClassABlueprintInterface(const UClass* Class)
{
	if (Class->HasAnyClassFlags(CLASS_Interface) && !Class->HasAnyClassFlags(CLASS_NewerVersionExists))
	{
		return true;
	}
	return false;
}
```