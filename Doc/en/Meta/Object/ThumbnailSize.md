# ThumbnailSize

- **Function Description:** Modify the thumbnail size.
- **Usage Locations:** UCLASS, UPROPERTY
- **Engine Module:** Object Property
- **Metadata Type:** boolean
- **Associated Items:** [DisplayThumbnail](DisplayThumbnail/DisplayThumbnail.md)

Modifying the thumbnail size does not appear to have any effect.

## Principle:

```cpp
void SObjectPropertyEntryBox::Construct( const FArguments& InArgs )
{
	// check if the property metadata wants us to display a thumbnail
const FString& DisplayThumbnailString = PropertyHandle->GetProperty()->GetMetaData(TEXT("DisplayThumbnail"));
if(DisplayThumbnailString.Len() > 0)
{
	bDisplayThumbnail = DisplayThumbnailString == TEXT("true");
}

// check if the property metadata has an override to the thumbnail size
const FString& ThumbnailSizeString = PropertyHandle->GetProperty()->GetMetaData(TEXT("ThumbnailSize"));
if ( ThumbnailSizeString.Len() > 0 )
{
	FVector2D ParsedVector;
	if ( ParsedVector.InitFromString(ThumbnailSizeString) )
	{
		ThumbnailSize.X = (int32)ParsedVector.X;
		ThumbnailSize.Y = (int32)ParsedVector.Y;
	}
}
}
```