// Fill out your copyright notice in the Description page of Project Settings.

#include "MyComponentTestActor.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AMyComponentTestActor::AMyComponentTestActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MyRoot");
	RootComponent = StaticMeshComponent;

	SubMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("SubMesh");
	SubMeshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMyComponentTestActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyComponentTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
