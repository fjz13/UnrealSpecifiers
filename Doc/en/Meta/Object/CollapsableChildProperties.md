# CollapsableChildProperties

- **Function Description:** A newly added meta in the TextureGraph module, utilized for collapsing the internal properties of a structure.
- **Usage Location:** UPROPERTY
- **Metadata Type:** bool
- **Restriction Type:** For use within the TextureGraph plugin only
- **Associated Items:** [ShowInnerProperties](ShowInnerProperties/ShowInnerProperties.md)
- **Commonality:** 0

Added as a new meta in the TextureGraph module, this is used to collapse the internal properties of a structure.

## Source Code:

```cpp
bool STG_GraphPinOutputSettings::CollapsibleChildProperties() const
{
	FProperty* Property = GetPinProperty();
	bool Collapsible = false;
	// check if there is a display name defined for the property, we use that as the Pin Name
	if (Property && Property->HasMetaData("CollapsableChildProperties"))
	{
		Collapsible = true;
	}
	return Collapsible;
}

	UPROPERTY(EditAnywhere, Category = NoCategory, meta = (TGType = "TG_Input", CollapsableChildProperties,ShowOnlyInnerProperties, FullyExpand, NoResetToDefault, PinDisplayName = "Settings") )
	FTG_OutputSettings OutputSettings;
```