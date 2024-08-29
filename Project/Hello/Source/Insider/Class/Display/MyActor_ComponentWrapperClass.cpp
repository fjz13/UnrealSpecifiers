#include "MyActor_ComponentWrapperClass.h"
#include "Components/PointLightComponent.h"

AMyActor_ComponentWrapperClass::AMyActor_ComponentWrapperClass(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/)
	: Super(ObjectInitializer)
{
	PointLightComponent = CreateDefaultSubobject<UPointLightComponent>("LightComponent0");
	PointLightComponent->Mobility = EComponentMobility::Stationary;

	RootComponent = PointLightComponent;
}


AMyActor_NoComponentWrapperClass::AMyActor_NoComponentWrapperClass(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/)
	: Super(ObjectInitializer)
{
	PointLightComponent = CreateDefaultSubobject<UPointLightComponent>("LightComponent0");
	PointLightComponent->Mobility = EComponentMobility::Stationary;

	RootComponent = PointLightComponent;
}