# ThumbnailSize

- **功能描述：** 改变缩略图的大小。
- **使用位置：** UCLASS, UPROPERTY
- **引擎模块：** Object Property
- **元数据类型：** bool
- **关联项：** [DisplayThumbnail](DisplayThumbnail/DisplayThumbnail.md)

改变缩略图的大小。但发现并不会起作用。

## 原理：

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