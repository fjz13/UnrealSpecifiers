// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MySpawnActor.generated.h"


UCLASS(Blueprintable)
class LEARN_API AMySpawnActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMySpawnActor();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	UFUNCTION(BlueprintCallable)
	AActor* Spawn(FVector Location, FRotator Rotation, FVector Scale);

	UFUNCTION(BlueprintCallable, Category = "MyTestActor", meta = (WorldContext = "WorldContextObject"))
	static AActor* MyStaticSpawn(const UObject* WorldContextObject, TSubclassOf<AActor> ActorClass, FVector Location, FRotator Rotation, FVector Scale);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> SpawnClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move", meta = (ExposeOnSpawn))
	FVector PositionMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move", meta = (ExposeOnSpawn))
	FVector PositionMax;
};
