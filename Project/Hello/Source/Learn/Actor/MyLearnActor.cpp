// Fill out your copyright notice in the Description page of Project Settings.

#include "MyLearnActor.h"
#include "Components/StaticMeshComponent.h"
#include "AssetRegistry/IAssetRegistry.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Components/LightComponent.h"
#include "Components/SpotLightComponent.h"


AMyLearnActor::AMyLearnActor(const FObjectInitializer& ObjectInitializer/*= FObjectInitializer::Get()*/)
	:Super(ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MyRoot");
	RootComponent = StaticMeshComponent;

	SubMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("SubMesh");
	SubMeshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMyLearnActor::BeginPlay()
{
	Super::BeginPlay();

	//AssetRegistry& assetRegistry= FModuleManager::Get().LoadModuleChecked<FAssetRegistryModule>("AssetRegistry").Get();
}

// Called every frame
void AMyLearnActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AMyLearnActor::PostInitProperties()
{
	Super::PostInitProperties();
}

void AMyLearnActor::PostCDOContruct()
{
	Super::PostCDOContruct();

}

void AMyLearnActor::PostLoad()
{
	Super::PostLoad();

}

void AMyLearnActor::PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph)
{
	Super::PostLoadSubobjects(OuterInstanceGraph);

}
