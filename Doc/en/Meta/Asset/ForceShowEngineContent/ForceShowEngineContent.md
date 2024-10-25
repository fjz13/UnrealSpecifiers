# ForceShowEngineContent

- **Function Description:** Forces the built-in engine resources to be optionally selectable in the resource selection list for a UObject* attribute
- **Usage Location:** UPROPERTY
- **Engine Module:** Asset Property
- **Metadata Type:** bool
- **Restriction Type:** UObject*
- **Associated Items:** [ForceShowPluginContent](ForceShowPluginContent.md)
- **Commonliness:** ★★

Enforces the option to select the built-in resources of the engine in the resource selection list for the specified UObject* attribute.

## Test Code:

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyProperty_ShowContent :public UDataAsset
{
public:
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Object)
	TObjectPtr<UObject> MyAsset_Default;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Object, meta = (ForceShowEngineContent))
	TObjectPtr<UObject> MyAsset_ForceShowEngineContent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Object, meta = (ForceShowPluginContent))
	TObjectPtr<UObject> MyAsset_ForceShowPluginContent;
};
```

## Test Results:

By default, MyAsset_Default is visible, containing only the resources of the current project.

The function of MyAsset_ForceShowEngineContent is essentially to check the "ShowEngineContent" option in the tab, which results in a significantly larger number of optional resources being displayed.

The function of MyAsset_ForceShowPluginContent is similarly to check the "ShowPluginContent" option in the tab, allowing selection of resources from other plugins.

![Untitled](Untitled.png)

## Principle:

In the resource selector for the property, the system will look for ForceShowEngineContent and ForceShowPluginContent, and then set them in AssetPickerConfig to alter the type of resources that can be optionally selected.

```cpp
void SPropertyMenuAssetPicker::Construct( const FArguments& InArgs )
{
		const bool bForceShowEngineContent = PropertyHandle ? PropertyHandle->HasMetaData(TEXT("ForceShowEngineContent")) : false;
		const bool bForceShowPluginContent = PropertyHandle ? PropertyHandle->HasMetaData(TEXT("ForceShowPluginContent")) : false;

		FAssetPickerConfig AssetPickerConfig;
		// Force show engine content if meta data says so
		AssetPickerConfig.bForceShowEngineContent = bForceShowEngineContent;
		// Force show plugin content if meta data says so
		AssetPickerConfig.bForceShowPluginContent = bForceShowPluginContent;
}
```