#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TemplateActor.generated.h"

UCLASS(Blueprintable, BlueprintType)
class ATemplateActor :public AActor
{
	GENERATED_BODY()
		ATemplateActor();
public:
	virtual void BeginPlay()override;
	virtual void Tick(float DeltaSeconds)override;
};
