#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "MyCustomAssetFactory.generated.h"

UCLASS()
class UMyCustomAssetFactory : public UFactory
{
    GENERATED_BODY()
public:
    UMyCustomAssetFactory();
    UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn);
};
