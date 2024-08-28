#include "CoreMinimal.h"
#include "CustomAsset/MyCustomAsset.h"
#include "Toolkits/AssetEditorToolkit.h"

class FMyCustomAssetEditorToolkit : public FAssetEditorToolkit
{
public:
	void InitEditor(const TArray<UObject*>& InObjects);

	void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;
	void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;

	FName GetToolkitFName() const override { return "MyCustomAssetEditor"; }
	FText GetBaseToolkitName() const override { return INVTEXT("MyCustomAssetEditor"); }
	FString GetWorldCentricTabPrefix() const override { return "NMyCustomAsset"; }
	FLinearColor GetWorldCentricTabColorScale() const override { return {}; }

private:
	UMyCustomAsset* MyCustomAsset;
};
