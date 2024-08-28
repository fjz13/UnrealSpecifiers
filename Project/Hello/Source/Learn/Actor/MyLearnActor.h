// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyLearnActor.generated.h"


UCLASS()
class LEARN_API AMyLearnActor : public AActor
{
	GENERATED_UCLASS_BODY()

public:
	// Sets default values for this actor's properties
	AMyLearnActor();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	virtual void PostInitProperties()override;
	virtual void PostCDOContruct()override;
	virtual void PostLoad()override;
	virtual void PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pickup, DisplayName = "MyRoot", meta = (AllowPrivateAccess = true))
		class UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pickup, DisplayName = "SubMesh", meta = (AllowPrivateAccess = true))
		class UStaticMeshComponent* SubMeshComponent;

	
};
