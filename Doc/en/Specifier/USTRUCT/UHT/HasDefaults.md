# HasDefaults

- **Function Description:** Indicates that the fields within this structure possess default values. Consequently, if this structure is passed as a function parameter or returned as a value, the function can assign default values to it.
- **Metadata Type:** bool
- **Engine Module:** UHT
- **Restriction Type:** Used exclusively by UHT in NoExportTypes.h
- **Mechanism:** Adds [FUNC_HasDefaults](../../../Flags/EFunctionFlags/FUNC_HasDefaults.md) to the FunctionFlags
- **Commonality:** 0

The structure's fields have default values specified.

This does not refer to whether there are default values declared in NoExportTypes.h but rather to the actual declaration location, where its internal attributes are initialized with default values. This allows the function to provide default values when the structure is used as a function parameter or return value.

Most structures in NoExportTypes.h have this structure (88/135), and none are like FPackedXXX.

## Principle:

If a function within a class uses a structure as a parameter, and if that structure has the HasDefaults attribute, it results in EFunctionFlags having the HasDefaults flag set

```cpp
// The following code is only performed on functions in a class.
if (Outer is UhtClass)
{
	foreach (UhtType type in Children)
	{
		if (type is UhtProperty property)
		{
			if (property.PropertyFlags.HasExactFlags(EPropertyFlags.OutParm | EPropertyFlags.ReturnParm, EPropertyFlags.OutParm))
			{
				FunctionFlags |= EFunctionFlags.HasOutParms;
			}
			if (property is UhtStructProperty structProperty)
			{
				if (structProperty.ScriptStruct.HasDefaults)
				{
					FunctionFlags |= EFunctionFlags.HasDefaults;
				}
			}
		}
	}
}
```