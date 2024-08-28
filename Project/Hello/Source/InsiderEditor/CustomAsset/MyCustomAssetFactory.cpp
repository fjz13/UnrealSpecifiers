#include "MyCustomAssetFactory.h"
#include "CustomAsset/MyCustomAsset.h"

UMyCustomAssetFactory::UMyCustomAssetFactory()
{
    SupportedClass = UMyCustomAsset::StaticClass();
    bCreateNew = true;
}

UObject* UMyCustomAssetFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
    return NewObject<UMyCustomAsset>(InParent, Class, Name, Flags, Context);
}
