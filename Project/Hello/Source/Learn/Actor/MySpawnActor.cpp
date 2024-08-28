// Fill out your copyright notice in the Description page of Project Settings.

#include "MySpawnActor.h"
#include "Engine/World.h"


// Sets default values
AMySpawnActor::AMySpawnActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AMySpawnActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMySpawnActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AActor* AMySpawnActor::Spawn(FVector Location, FRotator Rotation, FVector Scale)
{
	if (SpawnClass==nullptr)
	{
		return nullptr;
	}

	UWorld* world = GetWorld();
	FTransform transform(Rotation, Location, Scale);
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	AActor* actor= world->SpawnActor(SpawnClass.Get(),&transform, spawnParams);
	return actor;

}

AActor* AMySpawnActor::MyStaticSpawn(const UObject* WorldContextObject, TSubclassOf<AActor> ActorClass, FVector Location, FRotator Rotation, FVector Scale)
{
	if (ActorClass == nullptr)
	{
		return nullptr;
	}

	UWorld* world =GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
	FTransform transform(Rotation, Location, Scale);
	FActorSpawnParameters spawnParams;
	AActor* actor = world->SpawnActor(ActorClass, &transform, spawnParams);
	return actor;
}
