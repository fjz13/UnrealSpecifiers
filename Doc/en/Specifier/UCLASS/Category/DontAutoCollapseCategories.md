# DontAutoCollapseCategories

- **Function description:**  Makes the AutoCollapseCategories specifier for the listed categories inherited from the parent class ineffective.
- **Engine module:** Category
- **Metadata type:** strings = "a, b, c"
- **Mechanism of action:** Remove [AutoCollapseCategories](../../../Meta/DetailsPanel/AutoCollapseCategories.md) from the Meta data
- **Related Items:** [AutoCollapseCategories](AutoCollapseCategories/AutoCollapseCategories.md)
- **Commonly used:** ★

The code simply removes AutoCollapseCategories. Unlike AutoExpandCategories, it does not automatically add an expansion.  A search of the source code did not reveal its usage. Furthermore, the current source code implementation has bugs that prevent its removal.

```cpp
case EClassMetadataSpecifier::AutoExpandCategories:

	FHeaderParser::RequireSpecifierValue(*this, PropSpecifier);

	for (FString& Value : PropSpecifier.Values)
	{
		AutoCollapseCategories.RemoveSwap(Value);
		AutoExpandCategories.AddUnique(MoveTemp(Value));
	}
	break;

case EClassMetadataSpecifier::AutoCollapseCategories:

	FHeaderParser::RequireSpecifierValue(*this, PropSpecifier);

	for (FString& Value : PropSpecifier.Values)
	{
		AutoExpandCategories.RemoveSwap(Value);
		AutoCollapseCategories.AddUnique(MoveTemp(Value));
	}
	break;
case EClassMetadataSpecifier::DontAutoCollapseCategories:

	FHeaderParser::RequireSpecifierValue(*this, PropSpecifier);

	for (const FString& Value : PropSpecifier.Values)
	{
			AutoCollapseCategories.RemoveSwap(Value);//The current value of AutoCollapseCategories is empty. Removing it is pointless
	}
	break;

改动：
FUnrealClassDefinitionInfo::MergeClassCategories()放最后：
// Merge DontAutoCollapseCategories and AutoCollapseCategories
	for (const FString& Value : DontAutoCollapseCategories)
	{
		AutoCollapseCategories.RemoveSwap(Value);
	}
	DontAutoCollapseCategories.Empty();

改为：
case EClassMetadataSpecifier::DontAutoCollapseCategories:

			FHeaderParser::RequireSpecifierValue(*this, PropSpecifier);

			for (FString& Value : PropSpecifier.Values)
			{
				DontAutoCollapseCategories.AddUnique(MoveTemp(Value));
				//AutoCollapseCategories.RemoveSwap(Value);
			}
			break;
```