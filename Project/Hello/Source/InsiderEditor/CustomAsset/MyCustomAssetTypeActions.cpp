#include "MyCustomAssetTypeActions.h"
#include "CustomAsset/MyCustomAsset.h"
#include "MyCustomAssetEditorToolkit.h"

UClass* FMyCustomAssetTypeActions::GetSupportedClass() const
{
    return UMyCustomAsset::StaticClass();
}

FText FMyCustomAssetTypeActions::GetName() const
{
    return INVTEXT("MyCustomAsset");
}

FColor FMyCustomAssetTypeActions::GetTypeColor() const
{
    return FColor::Cyan;
}

uint32 FMyCustomAssetTypeActions::GetCategories()
{
    return EAssetTypeCategories::Misc;
}


void FMyCustomAssetTypeActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor)
{
    MakeShared<FMyCustomAssetEditorToolkit>()->InitEditor(InObjects);
}