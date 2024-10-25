# IsCoreType

- **Functional Description:** Indicates that this structure is a core class, and no forward declaration is necessary when UHT uses it.
- **Metadata Type:** bool
- **Engine Module:** UHT
- **Restriction Type:** Used exclusively by UHT in NoExportTypes.h
- **Commonality:** 0

Indicates that this structure is a core class, and UHT does not require a forward declaration when utilizing it.

## Principle:

Examining the UHT source code reveals the use of the 'struct' keyword in instances where parameters or attributes are being referenced.

```cpp
public override string? UhtStructProperty::GetForwardDeclarations()
		{
			if (ScriptStruct.IsCoreType)
			{
				return null;
			}

			if (TemplateWrapper != null)
			{
				StringBuilder builder = new();
				TemplateWrapper.AppendForwardDeclarations(builder);
				return builder.ToString();
			}

			return $"struct {ScriptStruct.SourceName};";
		}
```