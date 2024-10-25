# ShowOnlyInnerProperties

- **Function Description:** Promotes the internal properties of a struct attribute to the immediate parent level for direct display, rather than grouping them under an expandable parent structure as is the default behavior
- **Usage Location:** UPROPERTY
- **Metadata Type:** bool
- **Restriction Type:** FStruct attribute
- **Related Items:** [ShowInnerProperties](../ShowInnerProperties/ShowInnerProperties.md)
- **Commonality:** ★★★

The internal properties of struct attributes are directly elevated one level to be displayed, rather than being nested under a collapsible parent structure by default.

## Test Code:

```cpp
UPROPERTY(EditAnywhere, BlueprintReadWrite)
FMyPropertyInner InnerStruct;

UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ShowOnlyInnerProperties))
FMyPropertyInner InnerStruct_ShowOnlyInnerProperties;
```

## Effect Comparison:

![Untitled](Untitled.png)

You can observe that the internal properties of InnerStruct_ShowOnlyInnerProperties are directly shown at the object's current level, whereas the properties of InnerStruct are categorized under a structure name that can be expanded.

## Principle:

When encountering an FStructProperty, the system will check ShowOnlyInnerProperties to determine whether to create an expandable Category or to display the internal properties directly. With ShowOnlyInnerProperties set, it will recursively iterate through its internal properties.

```cpp
void DetailLayoutHelpers::UpdateSinglePropertyMapRecursive(FPropertyNode& InNode, FName CurCategory, FComplexPropertyNode* CurObjectNode, FUpdatePropertyMapArgs& InUpdateArgs)
{
		static FName ShowOnlyInners("ShowOnlyInnerProperties");
		// Whether or not to push out struct properties to their own categories or show them inside an expandable struct
		// This recursively applies for any nested structs that have the ShowOnlyInners metadata
		const bool bPushOutStructProps = bIsStruct && !bIsCustomizedStruct && Property->HasMetaData(ShowOnlyInners);

		if (bRecurseIntoChildren || LocalUpdateFavoriteSystemOnly)
		{
						// Built in struct properties or children of arras
						UpdateSinglePropertyMapRecursive(ChildNode, CurCategory, CurObjectNode, ChildArgs);
		}

}

void FObjectPropertyNode::GetCategoryProperties(const TSet<UClass*>& ClassesToConsider, const FProperty* CurrentProperty, bool bShouldShowDisableEditOnInstance, bool bShouldShowHiddenProperties,
	const TSet<FName>& CategoriesFromBlueprints, TSet<FName>& CategoriesFromProperties, TArray<FName>& SortedCategories)
	{
			if (CurrentProperty->HasMetaData(Name_ShowOnlyInnerProperties))
			{
				const FStructProperty* StructProperty = CastField<const FStructProperty>(CurrentProperty);
				if (StructProperty)
				{
					for (TFieldIterator<FProperty> It(StructProperty->Struct); It; ++It)
					{
						GetCategoryProperties(ClassesToConsider, *It, bShouldShowDisableEditOnInstance, bShouldShowHiddenProperties, CategoriesFromBlueprints, CategoriesFromProperties, SortedCategories);
					}
				}
			}

}
```