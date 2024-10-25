# DisplayThumbnail

- **Function Description:** Specifies whether to display a thumbnail on the left side of this attribute.
- **Usage Location:** UPROPERTY
- **Engine Module:** Object Property
- **Metadata Type:** bool
- **Restriction Type:** UObject*
- **Associated Items:** [ThumbnailSize](../ThumbnailSize.md)
- **Commonliness:** ★★★

Specifies whether to display a thumbnail on the left side of this property.

## Test Code:

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyActor_Thumbnail_Test :public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayThumbnail = "false"))
	UObject* MyObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayThumbnail = "true"))
	UObject* MyObject_DisplayThumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* MyActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayThumbnail = "true"))
	AActor* MyActor_DisplayThumbnail;
};

```

## Test Code:

Visible that a thumbnail of the selected asset is displayed to the left of MyObject_DisplayThumbnail, while MyObject does not have one because it is set to false. If DisplayThumbnail is not set to false, a thumbnail will be displayed by default.

MyActor_DisplayThumbnail shows a thumbnail icon, but it has been noticed that the correct image is not displayed. AActor does not display a thumbnail by default.

![Untitled](Untitled.png)

## 测试效果:

The function determines whether to display a thumbnail.

By default, non-Actor types are displayed. Moreover, SPropertyEditorAsset is used for asset type properties, which essentially refers to the Object property.

```cpp
bool SPropertyEditorAsset::ShouldDisplayThumbnail(const FArguments& InArgs, const UClass* InObjectClass) const
{
	if (!InArgs._DisplayThumbnail || !InArgs._ThumbnailPool.IsValid())
	{
		return false;
	}

	bool bShowThumbnail = InObjectClass == nullptr || !InObjectClass->IsChildOf(AActor::StaticClass());

	// also check metadata for thumbnail & text display
	const FProperty* PropertyToCheck = nullptr;
	if (PropertyEditor.IsValid())
	{
		PropertyToCheck = PropertyEditor->GetProperty();
	}
	else if (PropertyHandle.IsValid())
	{
		PropertyToCheck = PropertyHandle->GetProperty();
	}

	if (PropertyToCheck != nullptr)
	{
		PropertyToCheck = GetActualMetadataProperty(PropertyToCheck);

		return GetTagOrBoolMetadata(PropertyToCheck, TEXT("DisplayThumbnail"), bShowThumbnail);
	}

	return bShowThumbnail;
}
```