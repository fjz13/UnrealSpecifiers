#include "TemplateActor.h"

ATemplateActor::ATemplateActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATemplateActor::BeginPlay()
{
	Super::BeginPlay();
}

void ATemplateActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}
